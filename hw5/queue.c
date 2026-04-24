#include "defs.h"

//queue
queue* newQueue(){
  queue* toReturn = calloc(1, sizeof(queue));
  return toReturn;
}

//enqueue, always add the node to the end of the queue
void enqueue(queue* Qhead, node* graphData){
  queue* toAppend = newQueue(); //make a new queue node
  toAppend->data = graphData; //put the graph data in the queue node
  
  queue* lastQNode = Qhead->last; //put the new queue node at the end of the queue
  lastQNode->next = toAppend;
  
  Qhead->next = toAppend; //update the last pointer
}

//dequque, return the pointer to the node in the queue node at the front
node* dequeue(queue* Qhead){
  node* data = Qhead->data; //get the graph data from the top node
  
  queue* newHead = Qhead->next; //move the head forward one
  free(Qhead->next);
  free(Qhead->last);
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
