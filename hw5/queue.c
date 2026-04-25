#include "defs.h"

//queue
queue* newQueue(){
  queue* toReturn = calloc(1, sizeof(queue));
  toReturn->data = NULL;
  toReturn->next = NULL;
  return toReturn;
}

//enqueue: since this is a priority queue, sort it by distance to the source
void enqueue(queue* Qhead, node* graphData){
  queue* toInsert = newQueue();
  toInsert->data = graphData;

  queue* addAfter = Qhead;
  while(addAfter->next != NULL && addAfter->next->data != NULL && toInsert->data->dist > addAfter->next->data->dist){
    addAfter = addAfter->next;
  }

  toInsert->next = addAfter->next;
  addAfter->next = toInsert;  
}

//dequque, return the pointer to the node in the queue node at the front
node* dequeue(queue* Qhead){
  node* data = Qhead->next->data; //get the graph data from the top non-head node
  
  queue* newHead = Qhead->next; //move the head forward one
  free(Qhead);//free old head
  Qhead = newHead; //update head pointer
  
  return data; //return the data requested
}

int isQueueEmpty(queue* Qhead){
  if(Qhead == NULL){
    return 1; 
  }else{
    return 0;
  }
}
