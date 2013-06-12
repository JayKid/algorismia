#include "RBST.h"
int main() {
  RBST T;
  rand();
  T.insert(4);
  T.insert(1);
  T.insert(2);
  
  cout << "size arbre: " << T.getSize() << endl;
  T.Imprimir();
  
  return 0;
}