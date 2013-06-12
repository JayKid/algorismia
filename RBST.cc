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
  cout << "insertAtRoot" << endl;
  struct node *S, *G;
  
  split(x,p,&S,&G);
  node *q = new node();
  (*q).key = x; q->left = S; q->right = G;
  cout << "  q: " << (*q).key << " " << S << " " << G << endl;
  return q;
}


void RBST::split(int x, struct node *T, struct node **S, struct node **G) {
  cout << "Split" << endl;
  if (T == NULL) {
    cout << "   es null" << endl;
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
}

/*void RBST::Flip_orientatio(int *n, struct node *p) {
  int aux = *n-1-p->size;
  *n = p->size;
  p->size = aux;
  p->orientation_right = !p->orientation_right;
};*/



struct node *RBST::insertNode(int x, struct node *p, int n) {
  cout << "insertNode" << endl;
  int r = rand()%(n+1);
  if (r == n) {
    cout << "    insertRoot" << endl;
    p = insertAtRoot(x,p);
    cout << "    p->key: " << p->key << endl;
  }
  else if (x < p->key) {
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
  //p->size++;
  return p;
}


//Públiques:



void RBST::insert(int x) {
  struct node *p = insertNode(x, this->root, this->size);
  this->root = p;
}

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
    if (this->root == NULL) {
      cout << "Arbre buit, pointer null" << endl; 
      return;
    }
    else {
      pinta(this->root);
    }
    cout << endl;
}

