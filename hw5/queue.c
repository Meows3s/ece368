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
  
  //while(addAfter->next != NULL && addAfter->next->data != NULL && toInsert->data->distFromLast > addAfter->next->data->distFromLast){
    //addAfter = addAfter->next;
  //}
  
  while(addAfter->next != NULL && addAfter->next->data != NULL && toInsert->data->distFromSource > addAfter->next->data->distFromSource){
    addAfter = addAfter->next;
  }

  toInsert->next = addAfter->next;
  addAfter->next = toInsert;  
}

//dequque, return the pointer to the node in the queue node at the front
node* dequeue(queue** Qhead){
  if(*Qhead == NULL || (*Qhead)->next == NULL){return NULL;}
  
  queue* toRemove = (*Qhead)->next;
  node* data = toRemove->data;
  (*Qhead)->next = toRemove->next; //don't delete the actual head, just the first node after it
  free(toRemove);

  return data; //return the data requested
}
