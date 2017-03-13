/**
  ******************************************************************************
  * @file    Project/main.c 
  * @author  add by dr.ye
  * @version V1.0.0
  * @date    2017.3.7
  * @brief   Main program body
   ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------ */
#include "stm8s.h"
#include "stdio.h"
#include "user_recqueue.h"
#include "user_eventdeal.h"
#include "main.h"
#include "user_sendqueue.h"
/* Private defines -----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/* Public functions ----------------------------------------------------------*/

void delay6_25ms(uint8_t nCount);
void main(void)
{ 
  USTIM4_TimeBase(); 
  USUART1_Printf(); 
  printf("\n\rTIM4_TimeBase complete....\n\r");
  printf("\n\rUART1_Printf complete....\n\r");  
  
  GPIO_DeInit(ABRPDDPort);
  GPIO_Init(ABRPDDPort,Door_LOCK,GPIO_MODE_OUT_PP_HIGH_SLOW);
  GPIO_Init(ABRPDDPort,(GPIO_Pin_TypeDef)(ANTIRemove|PeoInduction|Door_DETC),GPIO_MODE_IN_PU_NO_IT);
  GPIO_ExternalPullUpConfig(ABRPDDPort,(GPIO_Pin_TypeDef)(ANTIRemove|PeoInduction|Door_DETC|Door_LOCK),ENABLE);
  
 
  GPIO_Init(IDCardPort,(GPIO_Pin_TypeDef)(IDCardData0|IDCardData1),GPIO_MODE_IN_PU_IT);
  GPIO_ExternalPullUpConfig(IDCardPort,(GPIO_Pin_TypeDef)(IDCardData0|IDCardData1),ENABLE);
  /*Initialize the Interrupt sensitivity */
  //EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOB, EXTI_SENSITIVITY_FALL_ONLY);
  //EXTI_SetTLISensitivity(EXTI_TLISENSITIVITY_FALL_ONLY);
  
  //printf("\n\rGPIO_Init complete....\n\r");
 
  USADC2CCVER();//Voltage Detect don't work if uncommand
  printf("\n\rUSADC2CCVER complete....\n\r");
  
  UART3_DeInit();
  /* Configure the UART3 */
  UART3_Init((uint32_t)115200, UART3_WORDLENGTH_8D, UART3_STOPBITS_1, UART3_PARITY_NO,
                UART3_MODE_TXRX_ENABLE);
  
  /* Enable UART3 Receive interrupt */
  UART3_ITConfig(UART3_IT_RXNE_OR, ENABLE);
  
  /*Enable UART3 Transmit interrupt*/
  //UART3_ITConfig(UART3_IT_TXE, ENABLE);
   
  /* enable interrupts */
  enableInterrupts(); 
   
  while (1)
  {
    EventDeal();
    
    if(!SENDis_empty())
     {
       UART3_SendData8((uint8_t)SENDfirst());                  
        /* Loop until the end of transmission */
       while (UART3_GetFlagStatus(UART3_FLAG_TC) == RESET);
       SENDdelete();    
     }
  }
}
void delay6_25ms(uint8_t nCount)
{
  uint8_t i;
  uint16_t j;
  for(i=0;i<100;i++)
  {
    for(j=0;j<1000;j++)
    {
      for(;nCount>0;nCount--);
    }
  }
}
#ifdef USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param file: pointer to the source file name
  * @param line: assert_param error line source number
  * @retval : None
  */
void assert_failed(u8* file, u32 line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* Infinite loop */
  while (1)
  {
  }
}
#endif


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
