#include "Empleado.h"

Empleado::Empleado(){
  cerr << "Me creo" << endl;
}

Empleado::~Empleado(){
  cerr << "Me destruyo" << endl;
}


void Empleado::Imprimir() {
    cout << "Aqui va la info del empleado:" << endl;
    cout << "Me llamo: " << this->m_nombre << endl;
};