/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USER_SENDTOSQUEUE_H
#define __USER_SENDTOSQUEUE_H
#include "main.h"

    void SendAckToSQueue(FrameHead FH,Command CMD,uint8_t SUM);
    uint8_t SendCMDToSQueue(FrameHead FH,Command CMD,uint8_t LEN);
#endif