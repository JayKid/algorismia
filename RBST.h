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
     struct node* root;
     
     RBST insert_at_root(int, RBST);
     //void split(int, RBST, RBST*, RBST*);
     //void Flip_orientatio(int*, struct node *);
     
   public:
     RBST();
     //RBST(int, RBST*, RBST*);
     ~RBST();
     
     RBST insert(int, RBST);
     
     void Imprimir();
};
 
#endif