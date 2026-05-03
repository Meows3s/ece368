#include "defs.h"

Tnode* RRPath(Tnode** rootptr, int leftFirst){
  Tnode* root = *rootptr;
  if(root == NULL ||root->divType == LEAF){return root;}
  
  Tnode* child = (leftFirst ? root->left : root->right);
  if(child->divType == LEAF){return root;}

  Tnode* newChild = pathGen(&child, !leftFirst);

  if(leftFirst){
    root->left = newChild;
  }else{
    root->right = newChild;
  }

  recalcDims(root);
  return root;
}

Tnode* pathGen(Tnode** rootptr, int leftFirst){
  Tnode* root = *rootptr;
  if(root == NULL || root->divType == LEAF){return root;} //no leaves allowed

  Tnode* child = (leftFirst ? root->left : root->right);
  if(child->divType == LEAF){return (leftFirst ? RRLeft(&root) : RRRight(&root));}

  Tnode* newNode = (leftFirst ? RRLeft(&root) : RRRight(&root));
  Tnode* newParent = (leftFirst ? newNode->right : newNode->left);
  Tnode* newNext = pathGen(&newParent, !leftFirst);

  if(leftFirst){
    newNode->right = newNext;
  }else{
    newNode->left = newNext;
  }

  recalcDims(newNode);
  return newNode;
}

//reroot left
Tnode* RRLeft(Tnode** rootptr){
  Tnode* root = *rootptr;
  Tnode* child = root->left;
  root->left = child->right;
  child->right = root;
  recalcDims(root);
  recalcDims(child);
  return child;
}

//reroot right
Tnode* RRRight(Tnode** rootptr){
  Tnode* root = *rootptr;
  Tnode* child = root->right;
  root->right = child->left;
  child->left = root;
  recalcDims(root);
  recalcDims(child);
  return child;
}
