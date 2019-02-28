#include "tree.h"
#include <iostream>
#include <cstdlib>
#include <queue>
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
    cout << "item " << key << " inserted" << endl;
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
    cout << "item " << key << " inserted" << endl;
  }
  else if( key > root->key ) {
    temp->right = root->right;
    temp->left = root;
    root->right = NULL;
    root = temp;
    cout << "item " <<  key << " inserted" << endl;
  }
  else {
    cout << "item " << key << " not inserted; already present" << endl;
    return root;
  }

  temp = NULL;
  return root;
}

node* SplayTree::Delete( int key, node* root ) {
  node* temp;
  if(!root)
    return NULL;
  root = Splay( key, root );
  if( key != root->key ) {
    cout << "item " << key << " not deleted; not present" << endl;
    return root;
  }
  else {
    
    cout << "item " << key << " deleted" << endl;
    
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
 return Splay( key, root );
}

int SplayTree::height( node* root ) {
  if( !root )
    return 0;
  else {
    int lefth = height(root->left);
    int righth = height(root->right);

    if( lefth > righth )
      return( lefth + 1 );
    else
      return( righth +1 );
  }
}
		      
void SplayTree::print( node* root ) {
  if( !root )
    return;

  queue< node* > z;
  z.push(root);

  int first = 0;
  int counter = 0;
  
  while(!z.empty()) {
    counter = z.size();

    while(counter > 0) {
      node* temp = z.front();
      if( first == 0 )
	cout << temp->key;
      else
	cout << ", " << temp->key;
      z.pop();
      
      if(temp->left != NULL)
	z.push(temp->left);
      if(temp->right != NULL)
	z.push(temp->right);

      counter--;
      first++;
    }
    cout << endl;
    first = 0;
  }
}
