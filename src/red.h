#ifndef RED_H_
#define RED_H_

#include "aed2.h"
#include "defines.h"
#include <iostream>

using namespace std;


class Red {
public:
  Red();

  void AgregarComputadora(Compu c, Conj<InterfazN> is);
  void Conectar(Compu c1, Compu c2, InterfazN i1, InterfazN i2);
  bool Conectadas(const Compu c1, const Compu c2);
  Conj<Compu> Computadoras();
  const InterfazN& InterfazUsada(const Compu c1, const Compu c2);
  Conj<Compu> Vecinos(Compu c);
  bool UsaInterfaz(Compu c, InterfazN i);
  Conj<Lista<Compu> > CaminosMinimos(Compu c1, Compu c2);
  bool HayCamino(Compu c1, Compu c2);

  //Para el driver
  Conj<InterfazN> Interfaces(Compu c);

private:
  Conj<Lista<Compu> > CaminosDeLargoN(Compu c1, Compu c2, Nat n);

  DiccString<DiccString<InterfazN> > vecinos;
  DiccString<Conj<InterfazN> > interfaces;

};

#endif
