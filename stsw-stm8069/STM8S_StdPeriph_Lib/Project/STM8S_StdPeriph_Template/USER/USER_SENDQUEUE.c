/*
 *  a SENDQueue that make through static array,the array size can change by define again 
 *  this is a circular SENDQueue!!
 */
 
#include "user_sendqueue.h"
#include <stdio.h>
#include <assert.h>
   
#include "stm8s.h"
/*SENDeive SENDQueue*/
#define SENDQUEUE_SIZE 20
#define SENDARRAY_SIZE (SENDQUEUE_SIZE + 1)
/*-------------*/
   

/*
 * the array that stores elements && the pointer that point to the head as well as the tail of the array 
 */
 /*SENDeive SENDQueue*/
  static  QUEUE_TYPE SENDQueue[SENDARRAY_SIZE];
  static  size_t SENDfront =1;
  static  size_t SENDrear =0;
 /*---------------*/
   
 /**
  * @brief  insert 
  *         
  * @param  value the element what is needed to be added
  * @retval None
  * @note the function is only suitably for the SENDQueue that creat dynamically
  */
  
  void SENDinsert(QUEUE_TYPE value)
  {
  	assert( !SENDis_full());
  	SENDrear = (SENDrear +1)%SENDARRAY_SIZE;
        SENDQueue[ SENDrear ] = value;
  }
  
  /**
  * @brief  delete delete an element from the SENDQueue and brush off it 
  *         
  * @param  None 
  * @retval None
  * @note 
  */
  
  void SENDdelete(void)
  {
      assert(!SENDis_empty());
      SENDfront = (SENDfront +1)%SENDARRAY_SIZE;
  }
  
   /**
  * @brief  first return the first element of the SENDQueue 
  *         
  * @param  None 
  * @retval the first QUEUE_TYPE element of SENDQueue 
  * @note 
  */
  
  QUEUE_TYPE SENDfirst (void)
  {
  	assert(!SENDis_empty());
  	return SENDQueue[SENDfront];
  }
  
  /**
  * @brief  is_empty return true if SENDQueue empty,otherwise false 
  *         
  * @param  None 
  * @retval None 
  * @note 
  */
  
  int SENDis_empty(void)
  {
      return ((SENDrear +1)%SENDARRAY_SIZE) == SENDfront;
  }
  /**
  * @brief  if_full return true if the SENDQueue full,otherwise false 
  *         
  * @param  None 
  * @retval None 
  * @note 
  */
  
  int SENDis_full(void)
  {
  	return (SENDrear +2)%SENDARRAY_SIZE == SENDfront;
  }
  