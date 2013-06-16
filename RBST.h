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
