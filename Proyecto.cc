#include "RBST.h"



int main() {
  RBST T;
  rand();

//   int element = 1;
//   while (element != -1) {
//     T.insert(element);
//     T.Imprimir();
//     cout << "Quin element vols inserir?" << endl;
//     cin >> element; 
//   }
  
// cout << "FEM SPLIT" << endl;

// node *S, *G;
// cout << "returnSplit: " << T.split(314,T.getRoot(), T.getSize(), &S, &G) << endl;
// T.Imprimir();

// cout << "FI SPLIT" << endl;












T.insert("hola");

T.insert("adios");

T.insert("enga!");

  T.Imprimir();
  cout << "size arbre: " << T.getSize() << endl;

T.deleteN("hola");

  T.Imprimir();

T.deleteN("adios");

  T.Imprimir();

T.deleteN("enga!");

  T.Imprimir();

  cout << "size arbre: " << T.getSize() << endl;

  return 0;
}