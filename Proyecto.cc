#include "RBST.h"
int main() {
  RBST T;
  rand();
  T.insert(1);
  T.insert(5);
  T.insert(3);
  T.insert(13);
  T.insert(8);
  
  cout << "size arbre: " << T.getSize() << endl;
  T.Imprimir();
  
  return 0;
}