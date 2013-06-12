HEADERS = RBST.h
OBJECTS = Proyecto.o RBST.o

default: Proyecto cleano

Proyecto.o: Proyecto.cc 
	g++ -c Proyecto.cc -o Proyecto.o

RBST.o: RBST.cc $(HEADERS)
	g++ -c RBST.cc -o RBST.o
    
Proyecto: $(OBJECTS)
	g++ Proyecto.o RBST.o -o Proyecto.x

cleano:
	-rm -f *.o
clean:
	-rm -f Proyecto
