#include "RBST.h"


//Privades:

RBST::RBST(){
  this->size = 0;
  this->root = NULL;
  cerr << "Me creo" << endl;
}


RBST::~RBST(){
  cerr << "Me destruyo" << endl;
}


node *RBST::insertAtRoot(string x, node *p, int n) {
  cout << "insertAtRoot (" << x << ", " << p << ", " << n << ")" << endl;
  node *q = new node();

  if (p == NULL)
  {
    cout << "   (insertAtRoot) NULL" << endl;
    q->key = x;
    q->orientation_right = true;
    q->size = 0;
  }
  else
  {
    node *S = new node(); //Quiza no hace falta inicializarlos
    node *G = new node();

    q->size = split(x,p,n,&S,&G);
    cout << "   insertAtRoot q-size = " << q->size << endl;
    q->orientation_right = false;
    q->key = x; q->left = S; q->right = G;
    cout << "   (insertAtRoot) q: " << (*q).key << " S: " << S << " G: " << G << endl;
  }
  
  return q;
}

//retorna el size de S
int RBST::split(string x, node *T, int sizeT, node **S, node **G) {
  cout << "Split (" << x << ", " << T << "," << sizeT << ")" << endl;
  int midaS;
  if (T == NULL) {
    cout << "   es null" << endl;
    *S = *G = NULL;
    midaS = 0;
  }
  else if (x < T->key) {
    *G = T;
    if (!T->orientation_right) {
      T->orientation_right = true;
      T->size = sizeT-1-T->size;
    }
    cout << "cridara amb: " << sizeT-1-T->size << endl;
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
  cout << "Salimos SPLIT con S = " << *S << " i G = " << *G << endl;
  cout << "---------------S-------------" << endl; pintaNode(*S); cout << endl;
  cout << "---------------G-------------" << endl; pintaNode(*G); cout << endl;
  return midaS;
}

void RBST::flip_orientation(int *n, node *p) {
  cout << "FLIP_ORIENTATION (" << *n << ")" << endl;
  if (p == NULL) cout << "es null la liarem!!!!!!" << endl; 
  int aux = *n-1-p->size;
  *n = p->size;
  p->size = aux;
  p->orientation_right = !p->orientation_right;
};


node* RBST::join(node* p, int gs) {
  cout << "            Entra al Join con un size: "<< gs << endl;
  node *l, *r, *result;
  node **parent;
  int m, n, u, total;

  if (p->orientation_right) {n = p->size; m = gs-1-n;}
  else {m = p->size; n = gs-1-m;}

  cout << "            hijos derechos: " << n << ", hijos izquierdos: " << m << endl;

  total = m+n;

  if (total == 0) return NULL;

  parent = &result;
  l = p->left; r = p->right;
       int cont = 1;
  while (total > 0) {
    cout << "            estem a la iteracio: " << cont << " del bucle, total = " << total << endl;
    cout << "            LA L: " << l << " i la R: " << r << endl;
    u = 1+rand()%(total);
    if (u <= m) {
      cout << "               entra en el if" << endl;
      *parent = l; parent = &(l->right);
      cout << "               m i l: " << m << " ; " << l << " entra a FLIP_ORIENTATION" << endl;
      if (l->orientation_right) flip_orientation(&m,l);
      else m = m-1-l->size;
      l = l->right;
    }
    else {
      cout << "               entra en el else" << endl;
      *parent = r; parent = &(r->left);
      cout << "               n i r: " << n << " ; " << r << " entra a FLIP_ORIENTATION" << endl;
      if (!r->orientation_right) flip_orientation(&n,r);
      else n = n-1-r->size;
      r = r->left;
    }
    total = m+n;
    cont++;
  }
  //free(p); //NO SE SI FA EL QUE HAURIA.
  return result;

}



node *RBST::insertNode(string x, node *p, int n) {
  cout << "insertNode" << endl;
  int r = rand()%(n+1);
  cout << "    rand: " << r << " n: " << n << endl;
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

void RBST::deleteNode(string x, node* t, int size) {
  cout << "   Entrem a deleteNode (" << x << ", " << t << ", " << size << ")" << endl;
  node *parent, *aux;
  parent = NULL;
  int n = size;
      int cont = 1;
  while(t != NULL) {
    cout << "      estem a la iteracio: " << cont << " del bucle, el size es: " << n << " i t es: " << t << endl;
    cout << "      x <> t->key : " << x << " <> " << t->key << endl;
    if (x == t->key) {
      cout << "         El troba!!! cridem a JOIN" << endl;
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
    //n = n-1-t->size;
    cont++;
  }
}


//Públiques:

int RBST::getSize() {
  return size;
}

node* RBST::getRoot() {
  return root;
}

void RBST::insert(string x) {
  node *p = insertNode(x, this->root, this->size);
  this->root = p;
  this->size += 1;
}

void RBST::deleteN(string x) {
  cout << "Entrem a deleteN (" << x << ")" << endl;
  deleteNode(x, this->root, this->size);
  this->size -= 1;
  cout << "Sortim de deleteN" << endl;
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


void RBST::pintaInOrdre(node *p, bool primer) {
  if (p != NULL)
  {
    pintaInOrdre(p->left, false);
    if (primer) cout << p->key;
    else cout << "," << p->key;
    pintaInOrdre(p->right, false);
  }
}


RBST RBST::merge(RBST T) {

  RBST a;
  return a;
}

bool RBST::contains(string s) {

  return true;
}


string RBST::nth(int i){
  return "caca";
}

int RBST::leq(string s) {

  return 1231;
}

int RBST::gt(string s) {

  return 231;
}

void RBST::inOrdre() {
    cout << "[";
    if (this->root != NULL)
      pintaInOrdre(this->root, true);
    cout << "]" << endl;
}

void RBST::between(string, string) {

  cout << "[1,2,3] loool te lo has creido!" << endl;
}

string RBST::treeMin() {

  return "dale a ALL i mira el primero tonto!";
}

string RBST::treeMax(){

  return "dale a ALL i mira el ultimo tontaina!";
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