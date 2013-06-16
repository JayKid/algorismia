#include <string>
#include <iostream>
#include <stdlib.h>  //srand, rand
using namespace std;

struct node{
  int size;
  int key;
  node* left;
  node* right;
  bool orientation_right;
};


class RBST {
  
   private:
     int size;
     node* root;
     
     node* insertAtRoot(int, node *,int);
     node* insertNode(int, node *, int);
     void deleteNode(int, node *, int);
     node* join(node*, int);
     void flip_orientation(int*, struct node *);
     
   public:
     RBST();
     RBST(int, node*);
     ~RBST();
     
     int getSize();
     node* getRoot();

     void split(int, node* , int, node**, node**);//Aquesta va en privates, pero estic fent proves.
     void insert(int);
     void deleteN(int);
     
     void Imprimir();
};
 