#include <stdlib.h>
#define QUEUE_TYPE int

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
  
  void insert(QUEUE_TYPE value);
  
  /**
  * @brief  delete delete an element from the queue and brush off it 
  *         
  * @param  None 
  * @retval None
  * @note 
  */
  
  void delete(void);
  
  /**
  * @brief  first return the first element of the queue 
  *         
  * @param  None 
  * @retval the first QUEUE_TYPE element of queue 
  * @note 
  */
  
  QUEUE_TYPE first (void);
  
  /**
  * @brief  is_empty return true if queue empty,otherwise false 
  *         
  * @param  None 
  * @retval None 
  * @note 
  */
  
  int is_empty(void);
  
  /**
  * @brief  if_full return true if the queue full,otherwise false 
  *         
  * @param  None 
  * @retval None 
  * @note 
  */
  
  int if_full(void);
  