HEADERS = Empleado.h
OBJECTS = Proyecto.o Empleado.o

default: Proyecto

Proyecto.o: Proyecto.cc 
	g++ -c Proyecto.cc -o Proyecto.o

Empleado.o: Empleado.cc $(HEADERS)
	g++ -c Empleado.cc -o Empleado.o
    
Proyecto: $(OBJECTS)
	g++ Proyecto.o Empleado.o -o Proyecto

clean:
	-rm -f Proyecto.o
	-rm -f Proyecto
