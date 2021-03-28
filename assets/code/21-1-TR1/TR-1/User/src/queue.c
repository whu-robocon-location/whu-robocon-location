#include "queue.h"


#define IsEmpty() (queue->front == queue->rear)
#define IsFull()  (((queue->rear + 1) % ARRAY_SIZE) == queue->front)

/*
*********************************************************************************************************
* Function    : SetEmpty
* 
* Description : ��ն���
*
* Arguments   :
*
* Returns     : 
*********************************************************************************************************
*/
void SetEmpty(QueueTypeDef * queue)
{
    queue->front = 0;        
    queue->rear = 0;
}
/*
*********************************************************************************************************
* Function    : EnQueue
* 
* Description : ��Ӻ���
*
* Arguments   :
*
* Returns     : 
*********************************************************************************************************
*/
void EnQueue(QueueTypeDef * queue,uint8_t Data)
{
    if (IsFull())
    {
        return;
        
    }
    queue->Data[queue->rear] = Data;
    queue->rear = (queue->rear + 1) % ARRAY_SIZE;
}
/*
*********************************************************************************************************
* Function    : DeQueue
*
* Description : ���Ӻ���
*
* Arguments   :
*
* Returns     : 
*********************************************************************************************************
*/
void DeQueue(QueueTypeDef * queue,uint8_t * Data)
{
    if (IsEmpty())
    {
        return;
    }
    memcpy(Data, &queue->Data[queue->front], sizeof(uint8_t));
    queue->front = (queue->front + 1) % ARRAY_SIZE;
}

/*
*********************************************************************************************************
* Function    : GetQueueLength
*
* Description : ��ȡ���г���
*
* Arguments   :
*
* Returns     : 
*********************************************************************************************************
*/
uint8_t GetQueueLength(QueueTypeDef * queue)
{
    if(queue->rear > queue->front) 
        return (queue->rear - queue->front);
    else if (queue->rear < queue->front) 
        return (QUEUE_SIZE - (queue->front - queue->rear) + 1);
    else
        return 0;

} 
