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


struct node *RBST::insertAtRoot(int x, struct node *p, int n) {
  cout << "insertAtRoot" << endl;
  node *q = new node();

  if (p == NULL)
  {
    q->key = x;
    q->orientation_right = true;
    q->size = 0;
  }

  else
  {
    struct node *S, *G;
    bool dreta = true;

    if (x > p->key)
    dreta = false;

    split(x,p,&S,&G);
    if (dreta && p->orientation_right || !dreta && !p->orientation_right) {
      q->orientation_right = !p->orientation_right;
      q->size = n-1-p->size;
    }
    else {
      q->orientation_right = p->orientation_right;
      q->size = p->size;
    }

    q->key = x; q->left = S; q->right = G;
    cout << "  q: " << (*q).key << " " << S << " " << G << endl;
  }
  
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
  cout << "    rand: " << r << endl;
  if (r == n) {
    cout << "    insertRoot" << endl;
    p = insertAtRoot(x,p,n);
    cout << "    p->key: " << p->key << endl;
  }
  else if (x < p->key) {
    if (!p->orientation_right) {
      p->orientation_right = !p->orientation_right;
      p->size = n-1-p->size;
    }
    p->left = insertNode(x, p->left, n-1-p->size);
  }
  else if (x > p->key) {
    if (p->orientation_right) {
      p->orientation_right = !p->orientation_right;
      p->size = n-1-p->size;
    }
    p->right = insertNode(x, p->right, n-1-p->size);
  }
  return p;
}

node* deleteNode(int x, node* t, int size) {
  node *p, *parent, *aux;
  parent = NULL;
  int n = size;
  while(t != NULL) {
    if (x == t->key) {
      aux = join(t,n);
      if (parent == NULL) t = aux;
      else {
        if (parent->key > x) parent->left = aux;
        else parent->right = aux;
      }
      break;
    }
    parent = t;
    if (x < t->key) {
      if (!t->orientation_right) flip_orientation(&n,t);
      t = t->left;
    }
    else {
      if (t->orientation_right) flip_orientation(&n,t);
      t = t->right;
    }
  }
}


//Públiques:

int RBST::getSize() {
  return size;
}

void RBST::insert(int x) {
  struct node *p = insertNode(x, this->root, this->size);
  this->root = p;
  this->size += 1;
}

void RBST::delete(int x) {
  struct node *p = deleteNode(x, this->root, this->size);
  this->root = p;
  this->size -= 1;
}

void pinta(node *p) {
  if (p == NULL) cout << "Abuit" << endl;
  else {
    if (p->orientation_right)
      cout << p->key <<  " te: " << p->size << " fills drets" << endl;
    else 
      cout << p->key <<  " te: " << p->size << " fills esquerres" << endl;
    pinta(p->left);
    pinta(p->right);
  }
}

void RBST::Imprimir() {
    cout << "L'arbre preordre es: " << endl; 
    if (this->root == NULL) {
      cout << "Arbre buit, pointer null" << endl; 
      return;
    }
    else {
      pinta(this->root);
    }
    cout << endl;
}

