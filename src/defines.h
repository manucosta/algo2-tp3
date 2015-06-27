#ifndef DEFINES_H
#define DEFINES_H
#include "aed2.h"

typedef String Compu;
typedef Nat Interfaz;
typedef Nat Id;
typedef Nat Prioridad;

struct Paquete{
  Paquete(){}
  Paquete(Id i, Prioridad p, Compu o, Compu d) : id(i), prioridad(p), origen(o), destino(d) {}
  Id id;
  Prioridad prioridad;
  Compu origen;
  Compu destino;
};

bool operator==(const Paquete p1, const Paquete p2){
	return p1.id == p2.id;
}

#endif
