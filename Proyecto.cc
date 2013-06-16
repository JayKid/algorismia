#include "RBST.h"

void pintaNode(node* subarbre) {
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

int main() {
  RBST T;
  rand();

  int element = 1;
  while (element != -1) {
    T.insert(element);
    T.Imprimir();
    cout << "Quin element vols inserir?" << endl;
    cin >> element; 
  }
  
cout << "FEM SPLIT" << endl;

node *S, *G;
T.split(314,T.getRoot(), T.getSize(), &S, &G);
T.Imprimir();

cout << "FI SPLIT" << endl;












for (int i = 10; i>=1 ; i--) {
  cout << "VAMOS A INSERTAR " << i << endl;
  T.insert(i);
  cout << "HEMOS INSERTADO " << i << endl;

  T.Imprimir();
}

  cout << "size arbre: " << T.getSize() << endl;

for (int i = 10; i >=1; i--) {
  T.deleteN(i);
}

  cout << "size arbre: " << T.getSize() << endl;

  int j;
  cin >> j;

  T.Imprimir();

  return 0;
}