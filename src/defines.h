#ifndef DEFINES_H
#define DEFINES_H
#include "aed2.h"

typedef String Compu;
typedef Nat InterfazN;
typedef Nat Id;
typedef Nat PrioridadN;


struct PaqueteN{
  PaqueteN(){}
  PaqueteN(Id i, PrioridadN p, Compu o, Compu d) : id(i), prioridad(p), origen(o), destino(d) {}
  Id id;
  PrioridadN prioridad;
  Compu origen;
  Compu destino;

  bool operator==(const PaqueteN otro){
	return id == otro.id;
  }
};

#endif
