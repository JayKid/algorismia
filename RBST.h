#include <string>
#include <iostream>
#include <stdlib.h>  //srand, rand
using namespace std;


#ifndef EMPLEADO_H
#define EMPLEADO_H


struct node{
  int size;
  int key;
  struct node* left;
  struct node* right;
  bool orientation_right;
};


class RBST {
  
   private:
     int size;
     node* root;
     
     node* insertAtRoot(int, node *);
     node* insertNode(int, node *, int);
     
     
     
     void split(int, node* , node**, node**);
     //void Flip_orientatio(int*, struct node *);
     
   public:
     RBST();
     RBST(int, node*);
     ~RBST();
     
     RBST insert(int, RBST);
     
     void Imprimir();
};
 
#endif