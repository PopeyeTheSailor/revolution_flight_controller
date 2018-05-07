/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2018 STMicroelectronics International N.V. 
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without 
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice, 
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other 
  *    contributors to this software may be used to endorse or promote products 
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this 
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under 
  *    this license is void and will automatically terminate your rights under 
  *    this license. 
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS" 
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT 
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT 
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, 
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

/* USER CODE BEGIN Includes */     
#include "fcm_led.h"
#include "fcm_spi.h"
#include "fcm_i2c.h"
#include "fcm_motors.h"
#include "imu.h"
#include "allan_variance.h"
#include "m25p16_flash.h"
#include "static_detector.h"

/* USER CODE END Includes */

/* Variables -----------------------------------------------------------------*/
osThreadId defaultTaskHandle;
osThreadId gather_inertial_dataHandle;
osThreadId determine_gyroscope_biasHandle;
osTimerId software_timerHandle;

/* USER CODE BEGIN Variables */

Imu imu;
Vector allan_variance_global; // tmp
char error_message[100] = {'\0'};

#define DATA_GATHERING_FREQUENCY 10 // Hz
#define ALLAN_VARIANCE_TIME_SLOT 1000 // ms
#define ALLAN_VARIANCE_SAMPLES_NUMBER ALLAN_VARIANCE_TIME_SLOT / DATA_GATHERING_FREQUENCY
#define ALLAN_VARIANCE_TIME_HORIZON 225

/* USER CODE END Variables */

/* Function prototypes -------------------------------------------------------*/
void StartDefaultTask(void const * argument);
void task_gather_inertial_data(void const * argument);
void task_determine_gyroscope_bias(void const * argument);
void software_timer_callback(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

/* Hook prototypes */

/* Init FreeRTOS */

void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
	statusLedOn();
	warningLedOff();

	fcm_spi_init();
	imu_init(&imu);
	flash_memory_init();

	motors_init();

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* Create the timer(s) */
  /* definition and creation of software_timer */
  osTimerDef(software_timer, software_timer_callback);
  software_timerHandle = osTimerCreate(osTimer(software_timer), osTimerOnce, NULL);

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityLow, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of gather_inertial_data */
  osThreadDef(gather_inertial_data, task_gather_inertial_data, osPriorityAboveNormal, 0, 128);
  gather_inertial_dataHandle = osThreadCreate(osThread(gather_inertial_data), NULL);

  /* definition and creation of determine_gyroscope_bias */
  osThreadDef(determine_gyroscope_bias, task_determine_gyroscope_bias, osPriorityNormal, 0, 2048);
  determine_gyroscope_biasHandle = osThreadCreate(osThread(determine_gyroscope_bias), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
}

/* StartDefaultTask function */
void StartDefaultTask(void const * argument)
{

  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* task_gather_inertial_data function */
void task_gather_inertial_data(void const * argument)
{
  /* USER CODE BEGIN task_gather_inertial_data */
	TickType_t xLastWakeTime = xTaskGetTickCount();
	TickType_t xFrequency = pdMS_TO_TICKS(DATA_GATHERING_FREQUENCY); // data gathered every 10ms
	Status status;
	uint8_t iter = 0;
	vector_int16_t raw_acc_data;
	vector_int16_t raw_gyro_data;

	volatile uint32_t flash_memory_address = 0x00;
	uint8_t vector_size = sizeof(Vector);
	uint32_t vectors_written = 0;
	Vector accelero_signals_sum;
	Vector gyro_signals_sum;
	vector_clear(&accelero_signals_sum);
	vector_clear(&gyro_signals_sum);
  /* Infinite loop */
  for(;;)
  {
    vTaskDelayUntil(&xLastWakeTime, xFrequency);
    status = mpu_6000_read_raw_data(&raw_acc_data, &raw_gyro_data);
    if (status != HAL_OK) {
    	warningLedOn();
    	sprintf(error_message, "Error: task_gather_inertial_data: read_raw_data_status: %d", status);
    } else {
    	imu_set_raw_data(&imu, &raw_acc_data, &raw_gyro_data, NULL);
    	if (vectors_written < 1000){

    		// sum up all signals in init static phase
    		accelero_signals_sum = vector_add(&accelero_signals_sum, &raw_acc_data);
    		gyro_signals_sum = vector_add(&gyro_signals_sum, &raw_gyro_data);

    		// save raw measurements to external flash for post-processing
    		flash_memory_write(flash_memory_address, (uint8_t*)(&raw_acc_data), vector_size);
    		flash_memory_address += vector_size;
    		flash_memory_write(flash_memory_address, (uint8_t*)(&raw_gyro_data), vector_size);
    		flash_memory_address += vector_size;
    		vectors_written++;
    	}

    	if (iter >=50) {
    		iter = 0;
    		statusLedToggle();
    	} else {
    		iter ++;
    	}
    }
    xTaskNotifyGive(determine_gyroscope_biasHandle);
    // TODO add gathering of magnetometer data
  }
  /* USER CODE END task_gather_inertial_data */
}

/* task_determine_gyroscope_bias function */
void task_determine_gyroscope_bias(void const * argument)
{
  /* USER CODE BEGIN task_determine_gyroscope_bias */

	Allan_Variance allan_variance_data;
	allan_variance_init(&allan_variance_data, 100, 1, 100);



	// Static analyzer
	volatile UBaseType_t stack = uxTaskGetStackHighWaterMark(determine_gyroscope_biasHandle);




  /* Infinite loop */
  for(;;)
  {
	  ulTaskNotifyTake(pdTRUE, pdMS_TO_TICKS(2*DATA_GATHERING_FREQUENCY));
    // TODO Handle timeout

	  if (allan_variance_update(&allan_variance_data, &raw_gyro_data)) {
		  allan_variance_global = allan_variance_get_last_computed_allan_variance(&allan_variance_data);
	  }

	  // check stack highest state
	  stack = uxTaskGetStackHighWaterMark(determine_gyroscope_biasHandle);

	  //--------------------------------------------------------
	  // calculate threshold from static phase for static detector



	  flash_memory_read(flash_memory_address, after, vector_size);

  }
  /* USER CODE END task_determine_gyroscope_bias */
}

/* software_timer_callback function */
void software_timer_callback(void const * argument)
{
  /* USER CODE BEGIN software_timer_callback */
  
  /* USER CODE END software_timer_callback */
}

/* USER CODE BEGIN Application */
     
/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
