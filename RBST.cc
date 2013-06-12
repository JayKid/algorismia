#include "RBST.h"


//Privades:

RBST::RBST(){
  this->size = 0;
  this->root = NULL;
  cerr << "Me creo" << endl;
}

/*RBST::RBST(int x, RBST *S, RBST *G){
  this->size = 1;
  this->root->size = 1;
  this->root->left = S;
  this->root->right = G;
  this->root->orientation_right = true;
  cerr << "Me creo wai" << endl;
}*/

RBST::~RBST(){
  cerr << "Me destruyo" << endl;
}


RBST RBST::insert_at_root(int x, RBST T) {
  struct node* p = T.root;
  RBST *S = new RBST();
  RBST *G = new RBST();
  
  split(x,T,S,G);
  RBST *Aux = new RBST(x,S,G);
  return *Aux;
};


void RBST::split(int x, RBST T, RBST *S, RBST *G) {
  struct node* p = T.root;
  if (T.root == NULL) {
    S = G = NULL;
  }
  else if (x < p->key) {
    G = &T;
    split(x, *(p->left), S, G->root->left);
  }
  else {
    S = &T;
    split(x, *(p->right), S->root->right, G);
  }
};

void RBST::Flip_orientatio(int *n, struct node *p) {
  int aux = *n-1-p->size;
  *n = p->size;
  p->size = aux;
  p->orientation_right = !p->orientation_right;
};






//Públiques:

RBST RBST::insert(int x, RBST T) {
  struct node *p = T.root;
  int n = T.size, m = p->size, r = rand()%n;
  if (r == n) {
    return insert_at_root(x,T);
  }
  if (x < p->key) {
    if (p->orientation_right) {
      p->orientation_right = !p->orientation_right; 
    }
    *(p->left) = insert(x, *(p->left));
  }
  else if (x > p->key) {
    *(p->right) = insert(x, *(p->right));
    
  }
  return T;
};

void pinta(struct node *p) {
  if (p == NULL) return;
  else {
    cout << p->key << " ";
    pinta(p->left);
    pinta(p->right);
  }
}

void RBST::Imprimir() {
    cout << "L'arbre inordre es: " << endl; 
    if (this->size == 0) return;
    else {
      pinta(this->root);
    }
    cout << endl;
};

