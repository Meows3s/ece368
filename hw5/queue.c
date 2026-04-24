#include "defs.h"

//queue
queue* newQueue(){
  queue* toReturn = calloc(1, sizeof(queue));
  return toReturn;
}

//enqueue: since this is a priority queue, sort it by distance to the source
void enqueue(queue* Qhead, node* graphData){
  queue* toInsert = newQueue(); //make a new queue node
  toInsert->data = graphData; //put the graph data in the queue node
  
  queue* addAfter = Qhead->next; //start at first node
  while(toInsert->data->dist > addAfter->data->dist){
    addAfter = addAfter->next; //increment
  }
  //rearrange the queue to insert the node at the correct location
  queue* addBefore = addAfter->next;
  addAfter->next = toInsert;
  toInsert->next = addBefore;
}

//dequque, return the pointer to the node in the queue node at the front
node* dequeue(queue* Qhead){
  node* data = Qhead->data; //get the graph data from the top node
  
  queue* newHead = Qhead->next; //move the head forward one
  free(Qhead->next);
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
