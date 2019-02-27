#include "tree.h"
#include <iostream>
#include <cstdlib>
using namespace std;

SplayTree::SplayTree(){
}

node* SplayTree::rrotate( node* a ) {
  node* b = a->left;
  a->left = b->right;
  b->right = a;
  return b;
}

node* SplayTree::lrotate( node* a ) {
  node* b = a->right;
  a->right = b->left;
  b->left = a;
  return b;
}

node* SplayTree::Splay( int key, node* root ) {
  if(!root)
    return NULL;
  node head;
  head.left = head.right = NULL;
  node* max = &head;
  node* min = &head;

  bool done = false;

  while(!done) {
    if( key < root->key ) {
      if(!root->left) {
	done = true;
	break;
      }
      if( key < root->left->key ) {
	root = rrotate(root);
	if(!root->left)
	  break;
      }
      min->left = root;
      min = min->left;
      root = root->left;
      min->left = NULL;
    }
    else if(key > root->key ) {
      if(!root->right) {
	done = true;
	break;
      }
      if( key > root->right->key ) {
	root = lrotate(root);
	if( !root->right )
	  break;
      }

      max->right = root;
      max = max->right;
      root = root->right;
      max->right = NULL;
    }
    else
      done = true;
  }

  max->right = root->left;
  min->left = root->right;
  root->left = head.right;
  root->right = head.left;
  return root;
}

node* SplayTree::Insert( int key, node* root ) {
  node* temp = new node;
  temp->key = key;
  temp->left = NULL;
  temp->right = NULL;

  if(!root) {
    root = temp;
    temp = NULL;
    return root;
  }

  root = Splay( key, root );

  if( key < root->key ) {
    temp->left = root->left;
    temp->right = root;
    root->left = NULL;
    root = temp;
  }
  else if( key > root->key ) {
    temp->right = root->right;
    temp->left = root;
    root->right = NULL;
    root = temp;
  }
  else
    return root;

  temp = NULL;
  return root;
}

node* SplayTree::Delete( int key, node* root ) {
  node* temp;
  if(!root)
    return NULL;
  root = Splay( key, root );
  if( key != root->key )
    return root;
  else {
    if( !root->left ) {
      temp = root;
      root = root->right;
    }
    else {
      temp = root;
      root = Splay(key, root->left);
      root->right = temp->right;
    }

    delete temp;
    return root;
  }
}

node* SplayTree::Find( int key, node* root ) {
 node* temp = Splay( key, root );
 if( temp->key = key )
   cout << "item " << key << "found" << endl;
 else
   cout << "item " << key << "not found" << endl;

 delete temp;
 return Splay( key, root );
}

  
