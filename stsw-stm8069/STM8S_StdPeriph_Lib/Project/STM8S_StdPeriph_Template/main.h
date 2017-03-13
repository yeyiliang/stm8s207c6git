/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H
#include "stm8s.h"
/*GPIOB*/
#define ABRPDDPort GPIOB//ANTIRemove BEEPOutpu RESET_X7 PeoInduction Door_DETC Door_LOCK
#define ANTIRemove GPIO_PIN_5  //input
#define BEEPOutpu GPIO_PIN_4          //output  
#define RESET_X7  GPIO_PIN_3     //output
#define PeoInduction GPIO_PIN_2  //input
#define Door_DETC GPIO_PIN_1     //input
#define Door_LOCK GPIO_PIN_0     //output
/*------------------------*/

/*GPIOC*/
#define IDCardPort GPIOC
#define IDCardData0 GPIO_PIN_1
#define IDCardData1 GPIO_PIN_2
/*-----------------------*/

/*GPIOE*/
#define VoltagePort GPIOE
#define VoltageDetect GPIO_PIN_6 //input
/*------------------------*/

/*FLAGS*/
extern bool Door_DetcFlag;
extern bool PeoInductionFlag;
extern bool ANTIRemoveFlag;
extern bool Door_LOCKFlag;


extern bool Door_DetcSendAgainFlag;
extern bool PeoInductionSendAgainFlag;
extern bool ANTIRemoveSendAgainFlag;

extern bool SendCMDOneFlag;
/*-----------------------*/

/*UART PROTOCOL typedef*/
typedef enum{
  SendFrameHead=0x13,
  ACKFrameHead    //0x14
}FrameHead;
typedef enum{
  CMDoor_LOCK=0x10,
  CMKEY,      //0x11           
  CMPeoInduction,//0x12
  CMDoor_DETC,//0x13
  CMANTIRemove,//0x14
  CMICCard,   //0x15
  CMSYSTick=0xAA,  
  CMRESET_X7=0XFF
}Command;

typedef struct{
  FrameHead FH;
  Command CMD;
  uint8_t LEN;
  uint8_t DATA;//note:IC NUMBER
  uint8_t SUM;
}UARTProtocol;
/*-----------------------*/

#endif