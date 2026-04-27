#include "defs.h"

//enqueue: since this is a priority queue, sort it by distance to the source
void enqueue(queue* Qhead, node* graphData, int dir){
  queue* toInsert = newQueue();
  toInsert->data = graphData;
  toInsert->dir = dir;

  queue* addAfter = Qhead;
  while(addAfter->next != NULL && addAfter->next->data != NULL && toInsert->data->distFromSource[dir] > addAfter->next->data->distFromSource[dir]){
    addAfter = addAfter->next;
  }

  toInsert->next = addAfter->next;
  addAfter->next = toInsert;  
}

//dequque, return a copy of the queue node at the front
queue dequeue(queue** Qhead){
  if(*Qhead == NULL || (*Qhead)->next == NULL){
    queue nullQ = {NULL, -1, NULL};
    return nullQ;
  }
  
  queue* toRemove = (*Qhead)->next;
  queue data = *toRemove; //make a copy of the data at this node
  (*Qhead)->next = toRemove->next; //don't delete the actual head, just the first node after it
  free(toRemove);

  return data; //return the data requested
}
