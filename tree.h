#include <string>
#include <cstdlib>
using namespace std;

struct node {
  int key;
  node* left;
  node* right;
};

class SplayTree {
 public:
  SplayTree();
  node* rrotate( node* a );
  node* lrotate( node* a );
  node* Splay( int key, node* root );
  node* Insert( int key, node* root );
  node* Delete( int key, node* root );
  node* Find( int key, node* root );

 private:
  node root;

};
