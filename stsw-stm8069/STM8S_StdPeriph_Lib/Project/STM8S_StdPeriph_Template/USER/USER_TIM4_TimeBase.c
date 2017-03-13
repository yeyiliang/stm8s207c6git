/**
  ******************************************************************************
  * @file     TIM4_TimeBase\main.c
  * @author   MCD Application Team
  * @version  V2.2.0
  * @date     30-September-2014
  * @brief    This file contains the main function for TIM4 Time Base Configuration example.
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
#include "stm8s_eval.h"

/**
  * @addtogroup TIM4_TimeBase
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define TIM4_PERIOD       124
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint32_t TimingDelay = 0;
/* Public variables ----------------------------------------------------------*/
__IO uint8_t EventTime=0;

/* Private function prototypes -----------------------------------------------*/
void Delay(__IO uint32_t nTime);
void TimingDelay_Decrement(void);
static void CLK_Config(void);
static void TIM4_Config(void);
static void GPIO_Config(void);
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/
/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
void USTIM4_TimeBase(void)
{
  
  
  /* Clock configuration -----------------------------------------*/
  CLK_Config();  
  /* GPIO configuration -----------------------------------------*/
  //GPIO_Config();  
   //CLK_ClockSwitchConfig(CLK_SWITCHMODE_AUTO, CLK_SOURCE_HSE, DISABLE, CLK_CURRENTCLOCKSTATE_DISABLE);
  /* TIM4 configuration -----------------------------------------*/
  TIM4_Config();    
  
}

/**
  * @brief  Configure system clock to run at 16Mhz
  * @param  None
  * @retval None
  */
static void CLK_Config(void)
{
    /* Initialization of the clock */
  CLK_DeInit();
  
  /* Clock divider to HSI/1 */
  CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
  
  /* Output Fcpu on CLK_CCO pin */
  //CLK_CCOConfig(CLK_OUTPUT_MASTER);
   
}

/**
  * @brief  Configure TIM4 to generate an update interrupt each 1ms 
  * @param  None
  * @retval None
  */
static void TIM4_Config(void)
{
  /* TIM4 configuration:
   - TIM4CLK is set to 16 MHz, the TIM4 Prescaler is equal to 128 so the TIM1 counter
   clock used is 16 MHz / 128 = 125 000 Hz
  - With 125 000 Hz we can generate time base:
      max time base is 2.048 ms if TIM4_PERIOD = 255 --> (255 + 1) / 125000 = 2.048 ms
      min time base is 0.016 ms if TIM4_PERIOD = 1   --> (  1 + 1) / 125000 = 0.016 ms
  - In this example we need to generate a time base equal to 1 ms
   so TIM4_PERIOD = (0.001 * 125000 - 1) = 124 */

  /* Time base configuration */
  TIM4_TimeBaseInit(TIM4_PRESCALER_128, TIM4_PERIOD);
  /* Clear TIM4 update flag */
  TIM4_ClearFlag(TIM4_FLAG_UPDATE);
  /* Enable update interrupt */
  TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE);
  

  /* Enable TIM4 */
  TIM4_Cmd(ENABLE);
}

/**
  * @brief  Configure GPIO for LEDs available on the evaluation board
  * @param  None
  * @retval None
  */
static void GPIO_Config(void)
{
    /* Initialize LEDs mounted on STM8-128 EVAL board */
    STM_EVAL_LEDInit(LED1);
    STM_EVAL_LEDInit(LED2);
    STM_EVAL_LEDInit(LED3);
    STM_EVAL_LEDInit(LED4);
    
    /* Switch LED2 & LED4 Off */
    STM_EVAL_LEDOff(LED2);
    STM_EVAL_LEDOff(LED4);
    
    /* Switch LED1 & LED3 On */
    STM_EVAL_LEDOn(LED1);
    STM_EVAL_LEDOn(LED3);
    
}

/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in milliseconds.
  * @retval None
  */
void Delay(__IO uint32_t nTime)
{
  TimingDelay = nTime;

  while (TimingDelay != 0);
}

/**
  * @brief  Decrements the TimingDelay variable.
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  {
    TimingDelay--;
  }
}


/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
