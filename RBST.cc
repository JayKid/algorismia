#include "RBST.h"

RBST::RBST(){
  this->size = 0;
  this->root = NULL;
}


RBST::~RBST(){
}

/* Funcion que dados un elemento, un puntero a nodo y el size del arbol
 inserta el nodo en la raiz del arbol */

node *RBST::insertAtRoot(string x, node *p, int n) {
  node *q = new node();

  if (p == NULL)
  {
    q->key = x;
    q->orientation_right = true;
    q->size = 0;
  }
  else
  {
    node *S = new node(); //Quiza no hace falta inicializarlos
    node *G = new node();

    q->size = split(x,p,n,&S,&G);
    q->orientation_right = false;
    q->key = x; q->left = S; q->right = G;
  }
  
  return q;
}

/* 

???

*/
int RBST::split(string x, node *T, int sizeT, node **S, node **G) {
  int midaS;
  if (T == NULL) {
    *S = *G = NULL;
    midaS = 0;
  }
  else if (x < T->key) {
    *G = T;
    if (!T->orientation_right) {
      T->orientation_right = true;
      T->size = sizeT-1-T->size;
    }
    midaS = split(x, T->left, sizeT-1-T->size, S, &((*G)->left));
  }
  else {
    *S = T;
    if (T->orientation_right) {
      T->orientation_right = false;
      T->size = sizeT-1-T->size;
    }
    midaS = split(x, T->right, sizeT-1-T->size, &((*S)->right), G);
    midaS = T->size+midaS+1;
  }
  return midaS;
}

/* Funcion que dado un puntero a numero y otro a nodo 
cambia la orientacion del nodo y nos deja en n el size del hijo 
al que apuntaba */

void RBST::flip_orientation(int *n, node *p) {
  int aux = *n-1-p->size;
  *n = p->size;
  p->size = aux;
  p->orientation_right = !p->orientation_right;
};

/* Función que dado un puntero a nodo y un entero 
retorna un puntero apuntando al nuevo nodo que es la union 
de los dos subarboles del nodo inicial sin el nodo root inicial */

node* RBST::join(node* p, int gs) {
  node *l, *r, *result;
  node **parent;
  int m, n, u, total;

  if (p->orientation_right) {n = p->size; m = gs-1-n;}
  else {m = p->size; n = gs-1-m;}

  total = m+n;

  if (total == 0) return NULL;

  parent = &result;
  l = p->left; r = p->right;
       int cont = 1;
  while (total > 0) {
    u = 1+rand()%(total);
    if (u <= m) {
      *parent = l; parent = &(l->right);
      if (l->orientation_right) flip_orientation(&m,l);
      else m = m-1-l->size;
      l = l->right;
    }
    else {
      *parent = r; parent = &(r->left);
      if (!r->orientation_right) flip_orientation(&n,r);
      else n = n-1-r->size;
      r = r->left;
    }
    total = m+n;
    cont++;
  }
  return result;
}


/* Funcion que dado un elemento, un puntero a nodo y el tamaño
inserta el elemento en el árbol que tiene como nodo raiz p */

node *RBST::insertNode(string x, node *p, int n) {
  int r = rand()%(n+1);
  if (r == n) {
    p = insertAtRoot(x,p,n);
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

/* Funcion que dado un elemento, un puntero a nodo y el tamaño
borra el elemento en el árbol que tiene como nodo raiz p */

void RBST::deleteNode(string x, node* t, int size) {
  node *parent, *aux;
  parent = NULL;
  int n = size;
      int cont = 1;
  while(t != NULL) {
    if (x == t->key) {
      aux = join(t,n);
      if (parent == NULL) this->root = aux;
      else {
        if (parent->key > x) parent->left = aux;
        else parent->right = aux;
      }
      break;
    }
    parent = t;
    if (x < t->key) {
      if (!t->orientation_right) flip_orientation(&n,t);
      else n = n-1-t->size;
      t = t->left;
    }
    else {
      if (t->orientation_right) flip_orientation(&n,t);
      else n = n-1-t->size;
      t = t->right;
    }
    cont++;
  }
}

/* Funcion que dado un puntero a nodo, retorna el elemento
de orden lexicografico menor */

string RBST::treeMinNode(node* p) {
   return (p->left != NULL)?treeMinNode(p->left):p->key;
}

/* Funcion que dado un puntero a nodo, retorna el elemento
de orden lexicografico mayor */

string RBST::treeMaxNode(node* p) {
   return (p->right != NULL)?treeMaxNode(p->right):p->key;
}

/* Funcion que dado un elemento, un puntero a nodo y el tamaño,
retorna todos los elementos menores o iguales */

int RBST::leqNode(string x, node* T, int sizeT) {

  int midaS;
  if (T == NULL) {
    midaS = 0;
  }
  else if (x == T->key) {
    return (T->orientation_right)?(sizeT-T->size):(T->size+1);
  }
  else if (x < T->key) {
    if (!T->orientation_right) {
      T->orientation_right = true;
      T->size = sizeT-1-T->size;
    }
    midaS = leqNode(x, T->left, sizeT-1-T->size);
  }
  else {
    if (T->orientation_right) {
      T->orientation_right = false;
      T->size = sizeT-1-T->size;
    }
    midaS = leqNode(x, T->right, sizeT-1-T->size);
    midaS = T->size+midaS+1;
  }
  return midaS;
}

/* Funcion que dado un elemento, un puntero a nodo y el tamaño,
retorna todos los elementos mayores */

int RBST::gtNode(string x, node* T, int sizeT) {
  return sizeT-leqNode(x,T,sizeT);
}

/* Funcion que retorna todos los elementos que son >= que min
y <= que max */

void RBST::betweenNode(node* p, string min, string max, bool &trobat) {
  if (p != NULL)
  {
    if (p->key >= min && p->key <= max) {
      betweenNode(p->left, min, max, trobat);
      if (!trobat) {cout << p->key; trobat = true;}
      else cout << "," << p->key;
      betweenNode(p->right, min, max, trobat);
    }
    else if (p->key > max) 
      betweenNode(p->left, min, max, trobat);
    else 
      betweenNode(p->right, min, max, trobat);
  }

}

/* Funcion que une dos arboles en el objeto desde el que se llama */

void RBST::merge(RBST b) {
  while (b.size) {
    if (!contains(b.root->key)){
      insert(b.root->key);
    }
    b.deleteN(b.root->key);
  }
}

/* Funcion que retorna el tamaño del árbol */

int RBST::getSize() {
  return size;
}

/* Funcion que retorna la raiz del árbol */

node* RBST::getRoot() {
  return root;
}

/* Funcion que inserta el elemento x en el árbol */

void RBST::insert(string x) {
  node *p = insertNode(x, this->root, this->size);
  this->root = p;
  this->size += 1;
}

/* Funcion que elimina el elemento x del árbol */

void RBST::deleteN(string x) {
  deleteNode(x, this->root, this->size);
  this->size -= 1;
}

/* Funcion que imprime el árbol */

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

/* Funcion que imprime el árbol en inorden */

void RBST::pintaInOrdre(node *p, bool &trobat) {
  if (p != NULL)
  {
    pintaInOrdre(p->left, trobat);
    if (!trobat) {cout << p->key; trobat = true;}
    else cout << "," << p->key;
    pintaInOrdre(p->right, trobat);
  }
}


/* Funcion que retorna cierto si existe el elemento
en el árbol */

bool RBST::contains(string element) {
  return containsRec(root,element);
}

/* Funcion que retorna cierto si existe el elemento
en el árbol apuntado por p */

bool RBST::containsRec(node *p, string element) {
  if (p != NULL)
  {
    if (p->key == element)
      return true;
    else if (p->key > element)
      return containsRec(p->left,element);
    else 
      return containsRec(p->right,element);
  }
  return false;
}

/* Funcion que retorna el enésimo elemento del arbol
en orden lexicografico */

string RBST::nth_rec(int index, node *p, int sizeT)
{
  if (p != NULL)
  {
    if (p->orientation_right) {
      p->orientation_right = !p->orientation_right;
      p->size = sizeT-1-p->size;
    }

    if (index <= p->size)
    {
      return nth_rec(index, p->left, p->size);
    }

    else if (index == p->size+1)
    {
      return p->key;
    }

    else 
    {
      return nth_rec(index-p->size-1,p->right, sizeT-1-p->size);
    }
  }
}

/* Funcion que retorna el enésimo elemento del arbol
en orden lexicografico */

string RBST::nth(int i){
  return nth_rec(i, root, size);
}

/* Funcion que dado un elemento retorna todos los
 elementos menores o iguales */

int RBST::leq(string s) {
  return leqNode(s,this->root,this->size);
}

/* Funcion que dado un elemento retorna todos los
 elementos mayores */

int RBST::gt(string s) {
  return gtNode(s,this->root, this->size);
}

/* Funcion que imprime el árbol en inorden */

void RBST::inOrdre() {
    cout << "[";
    bool trobat = false;
    if (this->root != NULL)
       pintaInOrdre(this->root, trobat);
    cout << "]" << endl;
}


/* Funcion que retorna todos los elementos que son >= que min
y <= que max */

void RBST::between(string min, string max) {
  cout << "[";
  bool trobat = false;
  node *p = this->root;
  if (p != NULL) {
    while (p != NULL and p->key < min) p = p->right;
    while (p != NULL and p->key > max) p = p->left; 
    if (p != NULL) betweenNode(p, min, max, trobat);  
  }
  cout << "]" << endl;
}

/* Funcion que retorna el elemento
de orden lexicografico menor */

string RBST::treeMin() {
  return treeMinNode(this->root);
}

/* Funcion que retorna el elemento
de orden lexicografico menor */

string RBST::treeMax(){
  return treeMaxNode(this->root);
}

/* Funcion que imprime el árbol en preorden */

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

  void RBST::pintaNode(node* subarbre) {
      if (subarbre == NULL) cout << "Abuit" << endl;
      else {
        if (subarbre->orientation_right)
          cout << subarbre->key <<  " te: " << subarbre->size << " fills drets" << endl;
        else 
          cout << subarbre->key <<  " te: " << subarbre->size << " fills esquerres" << endl;
        pintaNode(subarbre->left);
        pintaNode(subarbre->right);
    }
  }