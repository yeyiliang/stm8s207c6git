/**
  ******************************************************************************
  * @file    CLK_ClockSelection\main.c
  * @brief   This file contains the main function for the CLK Clock Selection example.
  * @author  MCD Application Team
  * @version  V2.2.0
  * @date     30-September-2014
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
//#include "stm8s_eval.h"
//#include "stm8s_eval_lcd.h"

/**
  * @addtogroup CLK_ClockSelection
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
//#define USHSI
//#define USHSE
//#define USLSI
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
static void CLK_Config(void);

/* Public functions ----------------------------------------------------------*/

/**
  * @brief Example  main entry point.
  * @param  None
  * @retval None
  */
void USCLK_ClockSelection(void)
{
 
  /* Clock configuration -----------------------------------------------------*/
  CLK_Config();   
#ifdef USHSI
      CLK_ClockSwitchConfig(CLK_SWITCHMODE_AUTO, CLK_SOURCE_HSI, DISABLE, CLK_CURRENTCLOCKSTATE_DISABLE);
#endif

#ifdef USHSE
      CLK_ClockSwitchConfig(CLK_SWITCHMODE_AUTO, CLK_SOURCE_HSE, DISABLE, CLK_CURRENTCLOCKSTATE_DISABLE);
#endif
      
#ifdef USLSI
       CLK_ClockSwitchConfig(CLK_SWITCHMODE_AUTO, CLK_SOURCE_LSI, DISABLE, CLK_CURRENTCLOCKSTATE_DISABLE);
#endif 
}

/**
  * @brief  Configure system clock to run at 16Mhz and output the system clock on
  *         CCO pin
  * @param  None
  * @retval None
  */
static void CLK_Config(void)
{
  CLK_DeInit();
  
  /* Clock divider to HSI/1 */
  CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
  
  /* Output Fcpu on CLK_CCO pin */
  CLK_CCOConfig(CLK_OUTPUT_MASTER);
}


/**
  * @}
  */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/