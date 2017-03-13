
/*the file is written by dr.ye*/

/* Define to prevent SENDursive inclusion -------------------------------------*/
#ifndef __USER_SENDQUEUE_H
#define __USER_SENDQUEUE_H
#include "user_recqueue.h"
#include <stdlib.h>
//#define QUEUE_TYPE uint8_t
//typedef unsigned char    QUEUE_TYPE;

/**
  * @brief  create queue 
  *          
  * @param  size the max number of the queue that could store
  * @retval None
  * @note the function is only suitably for the queue that creat dynamically
  */
  void create_queue(size_t size);
  
  /**
  * @brief  destroy_queue
  *         
  * @param  None
  * @retval None
  * @note the function is only suitably for the queue that creat dynamically
  */
  
  void destroy_queue(void);
  
  /**
  * @brief  insert 
  *         
  * @param  value the element what is needed to be added
  * @retval None
  * @note the function is only suitably for the queue that creat dynamically
  */
  
  void SENDinsert(QUEUE_TYPE value);
  
  /**
  * @brief  delete delete an element from the queue and brush off it 
  *         
  * @param  None 
  * @retval None
  * @note 
  */
  
  void SENDdelete(void);
  
  /**
  * @brief  first return the first element of the queue 
  *         
  * @param  None 
  * @retval the first QUEUE_TYPE element of queue 
  * @note 
  */
  
  QUEUE_TYPE SENDfirst (void);
  
  /**
  * @brief  is_empty return true if queue empty,otherwise false 
  *         
  * @param  None 
  * @retval None 
  * @note 
  */
  
  int SENDis_empty(void);
  
  /**
  * @brief  if_full return true if the queue full,otherwise false 
  *         
  * @param  None 
  * @retval None 
  * @note 
  */
  
  int SENDis_full(void);
  
#endif
  