/*
 *  a RECQueue that make through static array,the array size can change by define again 
 *  this is a circular RECQueue!!
 */
 
#include "user_recqueue.h"
#include <stdio.h>
#include <assert.h>
   
#include "stm8s.h"
/*receive RECQueue*/
#define RECQUEUE_SIZE 20
#define RECARRAY_SIZE (RECQUEUE_SIZE + 1)
/*-------------*/
   

/*
 * the array that stores elements && the pointer that point to the head as well as the tail of the array 
 */
 /*receive RECQueue*/
  static  QUEUE_TYPE RECQueue[RECARRAY_SIZE];
  static  size_t RECfront =1;
  static  size_t RECrear =0;
 /*---------------*/
   
 /**
  * @brief  insert 
  *         
  * @param  value the element what is needed to be added
  * @retval None
  * @note the function is only suitably for the RECQueue that creat dynamically
  */
  
  void RECinsert(QUEUE_TYPE value)
  {
  	assert( !RECis_full());
  	RECrear = (RECrear +1)%RECARRAY_SIZE;
        RECQueue[ RECrear ] = value;
  }
  
  /**
  * @brief  delete delete an element from the RECQueue and brush off it 
  *         
  * @param  None 
  * @retval None
  * @note 
  */
  
  void RECdelete(void)
  {
      assert(!RECis_empty());
      RECfront = (RECfront +1)%RECARRAY_SIZE;
  }
  
   /**
  * @brief  first return the first element of the RECQueue 
  *         
  * @param  None 
  * @retval the first QUEUE_TYPE element of RECQueue 
  * @note 
  */
  
  QUEUE_TYPE RECfirst (void)
  {
  	assert(!RECis_empty());
  	return RECQueue[RECfront];
  }
  
  /**
  * @brief  is_empty return true if RECQueue empty,otherwise false 
  *         
  * @param  None 
  * @retval None 
  * @note 
  */
  
  int RECis_empty(void)
  {
      return ((RECrear +1)%RECARRAY_SIZE) == RECfront;
  }
  /**
  * @brief  if_full return true if the RECQueue full,otherwise false 
  *         
  * @param  None 
  * @retval None 
  * @note 
  */
  
  int RECis_full(void)
  {
  	return (RECrear +2)%RECARRAY_SIZE == RECfront;
  }
  