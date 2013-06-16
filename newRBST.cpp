#include <string>
#include <iostream>
#include <string>
#include <stdlib.h>  //srand, rand
using namespace std;

struct node{
  int size;
  string key;
  node* left;
  node* right;
  bool orientation_right;
};


class RBST {

private:
    int size;
    node* root;

    node* insertAtRoot(string, node *,int);
    node* insertNode(string, node *, int);
    void deleteNode(string, node *, int);
    node* join(node*, int);
    int split(string, node* , int, node**, node**);
    void flip_orientation(int*, struct node *);
    void pintaInOrdre(node*, bool&);
    string treeMinNode(node*);
    string treeMaxNode(node*);
    int leqNode(string, node*, int);
    int gtNode(string, node*, int);
    bool containsRec(node*, string);
    string nth_rec(int, node*, int);
    void betweenNode(node*, string, string, bool &); 

public:
    RBST();
    ~RBST();

    int getSize();
    node* getRoot();

    void pintaNode(node*); //aquesta va fora
    void insert(string);
    void deleteN(string);
    void inOrdre();
    string treeMin();
    string treeMax();
    bool contains(string);
    int leq(string);
    int gt(string);
    string nth(int);
    void merge(RBST);
    void between(string, string);

    void Imprimir();
 };


//Privades:

RBST::RBST(){
  this->size = 0;
  this->root = NULL;
  //cerr << "Me creo" << endl;
}


RBST::~RBST(){
  //cerr << "Me destruyo" << endl;
}


node *RBST::insertAtRoot(string x, node *p, int n) {
  //cout << "insertAtRoot (" << x << ", " << p << ", " << n << ")" << endl;
  node *q = new node();

  if (p == NULL)
  {
    //cout << "   (insertAtRoot) NULL" << endl;
    q->key = x;
    q->orientation_right = true;
    q->size = 0;
  }
  else
  {
    node *S = new node(); //Quiza no hace falta inicializarlos
    node *G = new node();

    q->size = split(x,p,n,&S,&G);
    //cout << "   insertAtRoot q-size = " << q->size << endl;
    q->orientation_right = false;
    q->key = x; q->left = S; q->right = G;
    //cout << "   (insertAtRoot) q: " << (*q).key << " S: " << S << " G: " << G << endl;
  }
  
  return q;
}

//retorna el size de S
int RBST::split(string x, node *T, int sizeT, node **S, node **G) {
  //cout << "Split (" << x << ", " << T << "," << sizeT << ")" << endl;
  int midaS;
  if (T == NULL) {
    //cout << "   es null" << endl;
    *S = *G = NULL;
    midaS = 0;
  }
  else if (x < T->key) {
    *G = T;
    if (!T->orientation_right) {
      T->orientation_right = true;
      T->size = sizeT-1-T->size;
    }
    //cout << "cridara amb: " << sizeT-1-T->size << endl;
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
  //cout << "Salimos SPLIT con S = " << *S << " i G = " << *G << endl;
  //cout << "---------------S-------------" << endl; pintaNode(*S); cout << endl;
  //cout << "---------------G-------------" << endl; pintaNode(*G); cout << endl;
  return midaS;
}

void RBST::flip_orientation(int *n, node *p) {
  //cout << "FLIP_ORIENTATION (" << *n << ")" << endl;
  //if (p == NULL) cout << "es null la liarem!!!!!!" << endl; 
  int aux = *n-1-p->size;
  *n = p->size;
  p->size = aux;
  p->orientation_right = !p->orientation_right;
};


node* RBST::join(node* p, int gs) {
  //cout << "            Entra al Join con un size: "<< gs << endl;
  node *l, *r, *result;
  node **parent;
  int m, n, u, total;

  if (p->orientation_right) {n = p->size; m = gs-1-n;}
  else {m = p->size; n = gs-1-m;}

  //cout << "            hijos derechos: " << n << ", hijos izquierdos: " << m << endl;

  total = m+n;

  if (total == 0) return NULL;

  parent = &result;
  l = p->left; r = p->right;
       int cont = 1;
  while (total > 0) {
    //cout << "            estem a la iteracio: " << cont << " del bucle, total = " << total << endl;
    //cout << "            LA L: " << l << " i la R: " << r << endl;
    u = 1+rand()%(total);
    if (u <= m) {
      //cout << "               entra en el if" << endl;
      *parent = l; parent = &(l->right);
      //cout << "               m i l: " << m << " ; " << l << " entra a FLIP_ORIENTATION" << endl;
      if (l->orientation_right) flip_orientation(&m,l);
      else m = m-1-l->size;
      l = l->right;
    }
    else {
      //cout << "               entra en el else" << endl;
      *parent = r; parent = &(r->left);
      //cout << "               n i r: " << n << " ; " << r << " entra a FLIP_ORIENTATION" << endl;
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
  //cout << "insertNode" << endl;
  int r = rand()%(n+1);
  //cout << "    rand: " << r << " n: " << n << endl;
  if (r == n) {
    //cout << "    insertRoot" << endl;
    p = insertAtRoot(x,p,n);
    //cout << "    p->key: " << p->key << endl;
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
  //cout << "   Entrem a deleteNode (" << x << ", " << t << ", " << size << ")" << endl;
  node *parent, *aux;
  parent = NULL;
  int n = size;
      int cont = 1;
  while(t != NULL) {
    //cout << "      estem a la iteracio: " << cont << " del bucle, el size es: " << n << " i t es: " << t << endl;
    //cout << "      x <> t->key : " << x << " <> " << t->key << endl;
    if (x == t->key) {
      //cout << "         El troba!!! cridem a JOIN" << endl;
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

string RBST::treeMinNode(node* p) {
   return (p->left != NULL)?treeMinNode(p->left):p->key;
}

string RBST::treeMaxNode(node* p) {
   return (p->right != NULL)?treeMaxNode(p->right):p->key;
}

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

int RBST::gtNode(string x, node* T, int sizeT) {
  return sizeT-leqNode(x,T,sizeT);
}

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

//Públiques:


void RBST::merge(RBST b) {
  while (b.size) {
    if (!contains(b.root->key)){
      insert(b.root->key);
    }
    b.deleteN(b.root->key);
  }
}

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
  //cout << "Entrem a deleteN (" << x << ")" << endl;
  deleteNode(x, this->root, this->size);
  this->size -= 1;
  //cout << "Sortim de deleteN" << endl;
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


void RBST::pintaInOrdre(node *p, bool &trobat) {
  if (p != NULL)
  {
    pintaInOrdre(p->left, trobat);
    if (!trobat) {cout << p->key; trobat = true;}
    else cout << "," << p->key;
    pintaInOrdre(p->right, trobat);
  }
}


bool RBST::contains(string element) {
  return containsRec(root,element);
}

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


string RBST::nth_rec(int index, node *p, int sizeT)
{
  //cout << "REC index es: " << index << " size es: " << sizeT << endl;
  if (p != NULL)
  {
    if (p->orientation_right) {
      p->orientation_right = !p->orientation_right;
      p->size = sizeT-1-p->size;
    }

    if (index <= p->size)
    {
      //cout << "entra per geq" << endl;
      return nth_rec(index, p->left, p->size);
    }

    else if (index == p->size+1)
    {
      //cout << "entra per equals" << endl;
      return p->key;
    }

    else 
    {
      //cout << "entra per lt" << endl;
      return nth_rec(index-p->size-1,p->right, sizeT-1-p->size);
    }
  }
}

string RBST::nth(int i){
  //cout << "NONREC index es: " << i << " size es: " << size << endl;
  return nth_rec(i, root, size);
}

int RBST::leq(string s) {
  return leqNode(s,this->root,this->size);
}

int RBST::gt(string s) {
  return gtNode(s,this->root, this->size);
}

void RBST::inOrdre() {
    cout << "[";
    bool trobat = false;
    if (this->root != NULL)
       pintaInOrdre(this->root, trobat);
    cout << "]" << endl;
}




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

string RBST::treeMin() {
  return treeMinNode(this->root);
}

string RBST::treeMax(){
  return treeMaxNode(this->root);
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


#include <map>

const int INIT = 1;const int INS = 2;
const int DEL = 3;const int CONT = 4;
const int MERGE = 5;const int CARD = 6;
const int NTH = 7;const int LEQ = 8;
const int GT = 9;const int BETWEEN = 10;
const int MIN = 11;const int MAX = 12;
const int ALL = 13;

map<string,int> getSwitchMap() 
{
    map<string,int> m;
    m["init"] = INIT;
    m["ins"] = INS;
    m["del"] = DEL;
    m["cont"] = CONT;
    m["merge"] = MERGE;
    m["card"] = CARD;
    m["nth"] = NTH;
    m["leq"] = LEQ;
    m["gt"] = GT;
    m["between"] = BETWEEN;
    m["min"] = MIN;
    m["max"] = MAX;
    m["all"] = ALL;
    m["impr"] = 100;
    return m;
}

int main() {

    map<string,int> switchmap = getSwitchMap();

    string command;
    map<string,RBST> arbres;
    while (cin >> command) 
    {
        int command_num = switchmap[command];
        int number;
        string arbre, arbre2, element, element2;
        RBST aux,aux2,nou;
        cin >> arbre;
        cout << "> " << command << " " << arbre;

        switch ( command_num ) 
        {
            case INIT:
                cout << endl;
                arbres[arbre] = nou;
                cout << "OK" << endl;
            break;

            case INS:
                cin >> element;
                cout << " " << element << endl;

                if(arbres.find(arbre) == arbres.end())
                    cout << "ERROR" << endl;

                else
                {
                    aux = arbres[arbre];
                    if (!aux.contains(element))
                    {
                        aux.insert(element);
                        arbres[arbre] = aux;
                    }
                    cout << "OK" << endl;
                }
            break;
            case DEL:
                cin >> element;
                cout << " " << element << endl;

                if(arbres.find(arbre) == arbres.end())
                    cout << "ERROR" << endl;

                else
                {
                    aux = arbres[arbre];
                    if (aux.contains(element))
                    {
                        aux.deleteN(element);
                        arbres[arbre] = aux;
                    }
                    cout << "OK" << endl;
                }
            break;

            case CONT:
                cin >> element;
                cout << " " << element << endl;

                if(arbres.find(arbre) == arbres.end())
                    cout << "ERROR" << endl;

                else
                {
                    aux = arbres[arbre];
                    if (aux.contains(element))
                        cout << "true";
                    else cout << "false";
                    cout << endl;
                    
                }
            break;

            case MERGE:
                cin >> arbre2;
                cout << " " << arbre2 << endl;

                // cout << "arbre1 es: " << arbre << " arbre2 es: " << arbre2 << endl;
                if(arbres.find(arbre) == arbres.end() || arbres.find(arbre2) == arbres.end())
                    cout << "ERROR" << endl;

                else
                {
                    aux = arbres[arbre];
                    aux2 = arbres[arbre2];
                    aux.merge(aux2);
                    aux2 = nou;
                    arbres[arbre] = aux;
                    arbres[arbre2] = aux2;
                    cout << "OK" << endl;
                }

            break;

            case CARD:

                cout << endl;
                if(arbres.find(arbre) == arbres.end())
                    cout << "ERROR" << endl;

                else
                {
                    cout << arbres[arbre].getSize() << endl;
                }
                
            break;

            case NTH:

                cin >> number;
                cout << " " << number << endl;

                if(arbres.find(arbre) == arbres.end())
                    cout << "ERROR" << endl;

                else if (number < 1 || number > arbres[arbre].getSize())
                    cout << "ERROR";

                else
                {
                    aux = arbres[arbre];
                    cout << aux.nth(number) << endl;
                }

            break;

            case LEQ:
                cin >> element;
                cout << " " << element << endl;

                if(arbres.find(arbre) == arbres.end())
                    cout << "ERROR" << endl;

                else 
                {
                    aux = arbres[arbre];
                    cout << aux.leq(element) << endl;
                }

            break;

            case GT:
                cin >> element;
                cout << " " << element << endl;

                if(arbres.find(arbre) == arbres.end())
                    cout << "ERROR" << endl;

                else 
                {
                    aux = arbres[arbre];
                    cout << aux.gt(element) << endl;
                }
                
            break;

            case BETWEEN:
                cin >> element >> element2;
                cout << " " << element << " " << element2 << endl;


                if(arbres.find(arbre) == arbres.end())
                    cout << "ERROR" << endl;
                else
                {
                    aux = arbres[arbre];
                    aux.between(element,element2);
                }

            break;

            case MIN:
                cout << endl;
                if(arbres.find(arbre) == arbres.end())
                    cout << "ERROR" << endl;

                else
                {
                    aux = arbres[arbre];
                    if (aux.getSize() == 0)
                        cout << "ERROR" << endl;
                    else
                    {
                        cout << aux.treeMin() << endl;
                    }
                }
            break;

            case MAX:
                cout << endl;
                if(arbres.find(arbre) == arbres.end())
                    cout << "ERROR" << endl;

                else
                {
                    aux = arbres[arbre];
                    if (aux.getSize() == 0)
                        cout << "ERROR" << endl;
                    else
                    {
                        cout << aux.treeMax() << endl;
                    }
                }
                
            break;

            case ALL:
                cout << endl;
                arbres[arbre].inOrdre();
            break;
        }
    }
}