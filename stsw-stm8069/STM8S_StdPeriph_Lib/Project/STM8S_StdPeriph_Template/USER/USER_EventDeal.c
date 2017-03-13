/********UART Protocol struct*********************
--------------------------------------------------------------------------
FrameHead  |  CMD            | LEN               |    DATA      | SUM   
--------------------------------------------------------------------------  
  0X13     | 0X10(DOORCLOK)  |LEN=sizeof(DATA)   |  0X00&&0X01  | SUM=CMD|LEN|DATA
  0X14     | 0X11(KEY)       |                   |    BCD       | 
           | 0X12(people)    |                   |              |
           | 0x13(magnetism) |                   |              |
           | 0x14(antiremove)|                   |              |
           | 0x15(ICcard)    |                   |   IC number  | 
           | 0xAA(SYSTICK)   |  0                |              |
           | 0XFF(RESET)     |  0                |              |
---------------------------------------------------------------------------
************************************************/



#include "user_eventdeal.h"
#include "user_recqueue.h"
#include "user_sendqueue.h"
#include <stdio.h>
#include "main.h"
#include "user_sendtosqueue.h"
extern __IO uint8_t EventTime;

bool SendDLOCKAckFlag=FALSE;
bool CMSYSTickFlag=FALSE;

bool SendDoor_DETOneFlag=FALSE;
bool SendPeoInductionOneFlag=FALSE;
bool SendANTIRemoveOneFlag=FALSE;

uint16_t CMSYSTickCount=0;
uint16_t CMCount=0;



uint8_t Door_DETCDelay1=0;
#define Door_DETCDelay1Time 10
uint8_t Door_DETCDelay2=0;
#define Door_DETCDelay2Time 10


uint8_t PeoInductionDelay=0;
#define PeoInductionDelayTime 10
uint8_t ANTIRemoveDelay=0;
#define ANTIRemoveDelayTime 10


uint8_t SendSUM=0;
UARTProtocol ProtocolTemp;  
void EventDeal(void)
{
  switch(EventTime)
  { 
  case 1:/*do receive RECQueue*/
     
    /*
    if(!RECis_empty()){
    ProtocolTemp.FH=(FrameHead)RECfirst();
     RECdelete();
    printf("\n\rFrameHead:%d has been receive....\n\r",ProtocolTemp.FH);
    }*/     
      for(;!RECis_empty();RECdelete())//search head
      {
        if(SendFrameHead==RECfirst()||ACKFrameHead==RECfirst())//step out if find the head
          break;
      }
      if(RECis_empty())break;//when RECQueue is empty ,illustrate that the head is not found .break
      
      ProtocolTemp.SUM=0;//    SUM=CMD|LEN|DATA
      ProtocolTemp.FH=(FrameHead)RECfirst();
      RECdelete();
      /*---------------*/
      if(RECis_empty())break;//debug use
      /*---------------*/
      //printf("\n\rFrameHead:%d has been receive....\n\r",ProtocolTemp.FH);
      switch(ProtocolTemp.FH)  //  judge frame head
      {
      case SendFrameHead:       
        ProtocolTemp.CMD=(Command)RECfirst();
        RECdelete();
        /*---------------*/
        if(RECis_empty())break;//debug use
        /*---------------*/
        //printf("\n\rCommand:%d has been receive....\n\r",ProtocolTemp.CMD);
        switch(ProtocolTemp.CMD)//judge CMD 
        {
        case CMDoor_LOCK:
          if(1==(ProtocolTemp.LEN=RECfirst()))
          {
            //printf("\n\rLEN:%d has been receive....\n\r",ProtocolTemp.LEN); 
            RECdelete();
            /*---------------*/
            if(RECis_empty())break;//debug use
            /*---------------*/
            
            ProtocolTemp.DATA=RECfirst();
            RECdelete();            
            /*---------------*/
            if(RECis_empty())break;//debug use
            /*---------------*/           
            ProtocolTemp.SUM=ProtocolTemp.SUM|CMDoor_LOCK|ProtocolTemp.LEN|ProtocolTemp.DATA;//note:opertors type is different.
            //printf("\n\rcalculation of SUM is %d....\n\r",ProtocolTemp.SUM); 
            if(0x01==ProtocolTemp.DATA)
            {               
              if(ProtocolTemp.SUM==RECfirst())
              	{
                  RECdelete();
                  /*---------------*/
                  //if(RECis_empty())break;//
                  /*---------------*/  
              	  GPIO_WriteLow(ABRPDDPort,Door_LOCK); 
              	  SendDLOCKAckFlag=TRUE;                     
                }             	                         
            }
            else //if(0x00==ProtocolTemp.DATA)
            {            
              if(ProtocolTemp.SUM==RECfirst())
              	{
                  RECdelete();
                  /*---------------*/
                  //if(RECis_empty())break;//debug use
                  /*---------------*/  
                  GPIO_WriteHigh(ABRPDDPort,Door_LOCK);
                  SendDLOCKAckFlag=TRUE;                                    
              	}              
            }                            
          }
          break;
        case CMSYSTick:       
        CMSYSTickCount=0;                                         
          break;
        default:
          break;
        }
        break;
      case ACKFrameHead: 
        ProtocolTemp.CMD=(Command)RECfirst();
        RECdelete();
        /*---------------*/
        if(RECis_empty())break;//debug use
        /*---------------*/
        switch(ProtocolTemp.CMD)//judge CMD 
        {
        case CMKEY:
          break;
        case CMPeoInduction:
          break;
        case CMDoor_DETC:
          ProtocolTemp.SUM=SendSUM;
          if(ProtocolTemp.SUM==RECfirst())
            {
              RECdelete();
              /*---------------*/
              //if(RECis_empty())break;//
              /*---------------*/  
              Door_DetcSendAgainFlag=FALSE;                    
            } 
          break;
        case CMANTIRemove:
          break;
        case CMICCard:
          break;
        case CMRESET_X7:
          break;
        default:
          break;          
        }
        break;
      default:
        break;
      }
      
    break;
  case 2:
    /*deal Door_DETC.delay 50 ms,to remove tingle*/   
    if((GPIO_ReadInputData(ABRPDDPort) & Door_DETC ) == 0x00)
     {
       /*remove tingle*/
       if(Door_DETCDelay1==0)
       {
        Door_DETCDelay1=Door_DETCDelay1Time;
       }        
       else{
         Door_DETCDelay1--;
         if(Door_DETCDelay1==0)
         { 
           Door_DetcFlag=TRUE;
           Door_DetcSendAgainFlag=TRUE;      
         }          
       }
      /*end if remove tingle*/
     }
     else
      {   
      	if (Door_DETCDelay2==0) 
          {
            Door_DETCDelay2=Door_DETCDelay2Time;
          }
      	else 
          {
                  Door_DETCDelay2--;
                  if (Door_DETCDelay2==0) 
                          {
                                  SendDoor_DETOneFlag=TRUE;
                                  Door_DetcFlag=FALSE;
                                  Door_DetcSendAgainFlag=FALSE;
                          }
          }      
                       
      } 
    /*-----------------------------------------*/
    if((GPIO_ReadInputData(ABRPDDPort)  & PeoInduction ) == 0x00)
    {
      if(PeoInductionDelay==0)
      {
        PeoInductionDelay=PeoInductionDelayTime;
      }
      else{
        PeoInductionDelay--;
        if(PeoInductionDelay==0)
        {
           PeoInductionFlag=TRUE;
           PeoInductionSendAgainFlag=TRUE;
        }
      }    
    }
    else
    {
    	
      SendPeoInductionOneFlag=TRUE;//note: is problem??
      PeoInductionFlag=FALSE;
      PeoInductionSendAgainFlag=FALSE;
    }
    /*-------------------------------------------*/
    if(( GPIO_ReadInputData(ABRPDDPort) & ANTIRemove) == 0x00)
    {
      ANTIRemoveFlag=TRUE;
      ANTIRemoveSendAgainFlag=TRUE;
    }
    else
    {
      
    }
    /*------------------------------------------*/
    break;
  case 3:
    //GPIO_WriteHigh(ABRPDDPort,Door_LOCK);
    //ADC2_StartConversion();
    //UART3_ITConfig(UART3_IT_TXE, ENABLE);
    if(SendDoor_DETOneFlag)
    {    
      if (Door_DetcFlag)
      {
       SendDoor_DETOneFlag=FALSE;
       Door_DetcFlag=FALSE;     
       SendSUM=SendCMDToSQueue(SendFrameHead,CMDoor_DETC,1); 
       //UART3_ITConfig(UART3_IT_TXE, ENABLE); 
      }
    }
    if(SendPeoInductionOneFlag)
    {
      if(PeoInductionFlag)
      { 
        SendPeoInductionOneFlag=FALSE;
        PeoInductionFlag=FALSE; 
        /*send the CMPeoInduction*/     
      }
    }
    if(SendANTIRemoveOneFlag)
    {
      if(ANTIRemoveFlag)
      {   
        SendANTIRemoveOneFlag=FALSE;
        ANTIRemoveFlag=FALSE;
        /*send the CMANTIRemove*/     
      }
    }
    
    if(SendDLOCKAckFlag)
    {
      SendDLOCKAckFlag=FALSE;
      SendAckToSQueue(ACKFrameHead,CMDoor_LOCK,ProtocolTemp.SUM);
    }else{      
    }
    break;
  case 4:
    //GPIO_WriteLow(ABRPDDPort,Door_LOCK);
    break;
  case 5:
     //GPIO_WriteHigh(ABRPDDPort,Door_LOCK);
     CMSYSTickCount++;
     CMCount++;
     if(CMCount>20)
     {
       CMCount=0;
       if(Door_DetcSendAgainFlag==TRUE)
       {
         /*send CMD again*/
       }
     }
     if(CMSYSTickCount>2500)//2500
     {
       CMSYSTickCount=0;
       //GPIO_WriteReverse(ABRPDDPort,Door_LOCK);
     }
     
     
      
     
     EventTime=0;
    break;
  default:
   
    break;
  }
}
