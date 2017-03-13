#include "user_sendtosqueue.h"
#include "user_sendqueue.h"
void SendAckToSQueue(FrameHead FH,Command CMD,uint8_t SUM)
{
  if(!SENDis_full())
  {
    SENDinsert((QUEUE_TYPE)FH);
    /*must judge SENDis_full,has not been written*/
    SENDinsert((QUEUE_TYPE)CMD);
    /*must judge SENDis_full,has not been written*/
    SENDinsert((QUEUE_TYPE)SUM); 
  }
}
uint8_t SendCMDToSQueue(FrameHead FH,Command CMD,uint8_t LEN)
{
   uint8_t sumtemp=0;
   if(!SENDis_full())
   {
     SENDinsert((QUEUE_TYPE)FH);
    /*must judge SENDis_full,has not been written*/
     SENDinsert((QUEUE_TYPE)CMD);
    /*must judge SENDis_full,has not been written*/
     SENDinsert((QUEUE_TYPE)LEN);
    /*must judge SENDis_full,has not been written*/
     
     SENDinsert((QUEUE_TYPE)0x01);
    /*must judge SENDis_full,has not been written*/
     sumtemp=CMD|LEN|0X01;
   }
   return sumtemp;
}