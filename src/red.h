#ifndef RED_H
#define RED_H

#include "aed2.h"
#include "dicc_trie.h"
#include "defines.h"
#include <iostream>

using namespace std;


class Red {
public:
  Red();
  ~Red();

  void AgregarComputadora(compu c, Conj<interfaz> is);
  void Conectar(compu c1, compu c2, interfaz i1, interfaz i2);
  Conj<compu> Computadoras();
  interfaz InterfazUsada(compu c1, compu c2);
  Conj<compu> Vecinos(compu c);
  bool UsaInterfaz(compu c, interfaz i);
  Conj<Lista<compu> > CaminosMinimos(compu c1, compu c2);
  bool HayCamino(compu c1, compu c2);
  Conj<Lista<compu> > CaminosDeLargoN(compu c1, compu c2, Nat n);


private:
  DiccString<DiccString<interfaz> > vecinos;
  DiccString<Conj<interfaz> > interfaces;

};

/* computadoras es no-trivial, hay que hacer un par de cositas */


#endif
