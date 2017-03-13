/*
 *  a queue that make through static array,the array size can change by define again 
 *  this is a circular queue!!
 */
 
#include "queue.h"
#include <stdio.h>
#include <assert.h>

#define QUEUE_SIZE 100
#define ARRAY_SIZE (QUEUE_SIZE + 1)

/*
 * the array that stores elements && the pointer that point to the head as well as the tail of the array 
 */
 
 static QUEUE_TYPE queue[ARRAY_SIZE];
 static size_t front =1;
 static size_t rear =0;
 
 /**
  * @brief  insert 
  *         
  * @param  value the element what is needed to be added
  * @retval None
  * @note the function is only suitably for the queue that creat dynamically
  */
  
  void insert(QUEUE_TYPE value)
  {
  	assert( !is_full());
  	rear = (rear +1)%ARRAY_SIZE;
  	queue[ rear ] = value;
  }
  
  /**
  * @brief  delete delete an element from the queue and brush off it 
  *         
  * @param  None 
  * @retval None
  * @note 
  */
  
  void delete(void)
  {
  	assert(!is_empty());
  	front = (front +1)%ARRAY_SIZE;
  }
  
   /**
  * @brief  first return the first element of the queue 
  *         
  * @param  None 
  * @retval the first QUEUE_TYPE element of queue 
  * @note 
  */
  
  QUEUE_TYPE first (void)
  {
  	assert(!is_empty());
  	return queue[front];
  }
  
  /**
  * @brief  is_empty return true if queue empty,otherwise false 
  *         
  * @param  None 
  * @retval None 
  * @note 
  */
  
  int is_empty(void)
  {
  	return (rear +1)%ARRAY_SIZE == front;
  }
  
  /**
  * @brief  if_full return true if the queue full,otherwise false 
  *         
  * @param  None 
  * @retval None 
  * @note 
  */
  
  int if_full(void)
  {
  	return (rear +2)%ARRAY_SIZE == front;
  }