/**
  ******************************************************************************
  * @file    GPIO_Toggle\main.c
  * @author  MCD Application Team
  * @version  V2.2.0
  * @date     30-September-2014
  * @brief   This file contains the main function for GPIO Toggle example.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm8s.h"

/**
  * @addtogroup GPIO_Toggle
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static void Delay (uint16_t nCount);

/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
void USGPIOToggle(void)
{

  /* Initialize I/Os in Output Mode */
  GPIO_Init(GPIOB, (GPIO_Pin_TypeDef)GPIO_PIN_0, GPIO_MODE_OUT_PP_LOW_FAST);

  while (1)
  {
    /* Toggles LEDs */
    GPIO_WriteReverse(GPIOB, (GPIO_Pin_TypeDef)GPIO_PIN_0);
  }

}

/**
  * @brief Delay
  * @param nCount
  * @retval None
  */
static void Delay(uint16_t nCount)
{
  /* Decrement nCount value */
  while (nCount != 0)
  {
    nCount--;
  }
}


/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
