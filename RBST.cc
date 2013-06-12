#include "RBST.h"


//Privades:

RBST::RBST(){
  this->size = 0;
  this->root = NULL;
  cerr << "Me creo" << endl;
}

RBST::RBST(int x, struct node *p){
  this->size = x;
  this->root = p;
  cerr << "Me creo wai" << endl;
}

RBST::~RBST(){
  cerr << "Me destruyo" << endl;
}


struct node *RBST::insertAtRoot(int x, struct node *p) {
  struct node *S, *G;
  
  split(x,p,&S,&G);
  p->key = x; p->left = S; p->right = G;
  return p;
};


void RBST::split(int x, struct node *T, struct node **S, struct node **G) {
  if (T == NULL) {
    *S = *G = NULL;
  }
  else if (x < T->key) {
    *G = T;
    split(x, T->left, S, &((*G)->left));
  }
  else {
    *S = T;
    split(x, T->right, &((*S)->right), G);
  }
};

/*void RBST::Flip_orientatio(int *n, struct node *p) {
  int aux = *n-1-p->size;
  *n = p->size;
  p->size = aux;
  p->orientation_right = !p->orientation_right;
};*/



struct node *RBST::insertNode(int x, struct node *p, int n) {
  int r = rand()%n+1;
  if (r == n) {
    p = insertAtRoot(x,p);
  }
  if (x < p->key) {
    if (p->orientation_right) {
      p->orientation_right = !p->orientation_right;
      p->size = n-1-p->size;
    }
    p->left = insertNode(x, p->left, p->size);
  }
  else if (x > p->key) {
    if (!p->orientation_right) {
      p->orientation_right = !p->orientation_right;
      p->size = n-1-p->size;
    }
    p->right = insertNode(x, p->right, p->size);
  }
  p->size++;
  return p;
}


//Públiques:



RBST RBST::insert(int x, RBST T) {
  struct node *p = insertNode(x,T.root, T.size);
  RBST *ret = new RBST(T.size+1,p);
  return *ret;
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

