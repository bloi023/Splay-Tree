#include <iostream>
#include <string>
#include "tree.h"

int main() {

  SplayTree t;
  int operations;
  std::string next;
  std::cin >> operations;
  node* root = NULL;
  
  while( std::cin >> next ) {
    if( next == "insert" ) {
      std::cin >> next;
      root = t.Insert( std::stoi(next), root );
    }
    else if( next == "find" ) {
      std::cin >> next;
      root = t.Find( std::stoi(next), root );
      if( root->key != std::stoi(next) )
	std::cout << "item " << next << " not found" << endl;
      else
	std::cout << "item " << next << " found" << endl;
    }
    else if( next == "delete" ) {
      std::cin >> next;
      root = t.Delete( std::stoi(next), root );
    }
    else
      t.print(root);
  }
	  
  return 0;

}
