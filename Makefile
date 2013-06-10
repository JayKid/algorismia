HEADERS = RBST.h
OBJECTS = Proyecto.o RBST.o

default: Proyecto

Proyecto.o: Proyecto.cc 
	g++ -c Proyecto.cc -o Proyecto.o

RBST.o: RBST.cc $(HEADERS)
	g++ -c RBST.cc -o RBST.o
    
Proyecto: $(OBJECTS)
	g++ Proyecto.o RBST.o -o Proyecto

clean:
	-rm -f Proyecto.o
	-rm -f Proyecto
