/**
  ******************************************************************************
  * @file    ADC2_ContinuousConversion\main.c
  * @author  MCD Application Team
  * @version  V2.2.0
  * @date     30-September-2014
  * @brief   This file contains the main function for the ADC2 Continuous Conversion example.
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
#include "main.h"
/**
  * @addtogroup ADC2_ContinuousConversion
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
    

    
__IO uint16_t Conversion_Value = 0;
/* Private function prototypes -----------------------------------------------*/
static void ADC_Config(void);

/* Private functions ---------------------------------------------------------*/

/**
  * @brief ADC2_ContinuousConversion  main entry point.
  * @param  None
  * @retval None
  */
void USADC2CCVER(void)
{
  

  /* ADC configuration -------------------------------------------*/
  ADC_Config();
     
 
}

/**
  * @brief  Configure ADC2 Continuous Conversion with End Of Conversion interrupt 
  *         enabled .
  * @param  None
  * @retval None
  */
static void ADC_Config()
{
  /*  Init GPIO for ADC2 */
  GPIO_Init(VoltagePort,VoltageDetect, GPIO_MODE_IN_FL_NO_IT);
  
  /* De-Init ADC peripheral*/
  ADC2_DeInit();

  /* Init ADC2 peripheral */
  ADC2_Init(ADC2_CONVERSIONMODE_SINGLE, ADC2_CHANNEL_9, ADC2_PRESSEL_FCPU_D2, \
            ADC2_EXTTRIG_TIM, DISABLE, ADC2_ALIGN_RIGHT, ADC2_SCHMITTTRIG_CHANNEL9,\
            DISABLE);

  /* Enable EOC interrupt */
  ADC2_ITConfig(ENABLE);

  /* Enable general interrupts */  
  //enableInterrupts();
  
  /*Start Conversion */
  //ADC2_StartConversion();
}

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
