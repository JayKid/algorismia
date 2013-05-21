#include <string>
#include <iostream>
using namespace std;


#ifndef EMPLEADO_H
#define EMPLEADO_H
 
class Empleado {
  public:
    string m_nombre;	
    string m_departamento;
    string m_posicion;
    long m_salario;
    
    Empleado();
    ~Empleado();
    void Imprimir();
  private:
};
 
#endif