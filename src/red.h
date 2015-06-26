#ifndef RED_H
#define RED_H

#include "aed2.h"
#include "dicc_trie.h"
#include "Conj.h"
#include "defines.h"
#include <iostream>

using namespace std;


class Red {
public:
  Red();
  ~Red();

  void AgregarComputadora(compu c, Conj<interfaz> is);
  void Conectar(compu c1, compu c2, interfaz i1, interfaz i2);
  bool Conectadas(compu c1, compu c2);
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
Red::Red(){
	vecinos = DiccString<DiccString<interfaz> >();
	interfaces = DiccString<Conj<interfaz> >();
	}
Red::~Red(){
	vecinos.~DiccString<DiccString<interfaz> >();
	interfaces.~DiccString<Conj<interfaz> >();
	}
void Red::AgregarComputadora(compu c, Conj<interfaz> is){
	DiccString<interfaz> vacio;
	vecinos.definir(c, vacio);
	interfaces.definir(c,is);
	}

void Red::Conectar(compu c1, compu c2, interfaz i1, interfaz i2){
	DiccString<interfaz>* x;
	x = vecinos.obtener(c1);
	x->definir(c2,i1);
	DiccString<interfaz>* y;
	y = vecinos.obtener(c2);
	y->definir(c1,i2);
	}

bool Red::Conectadas(compu c1, compu c2){
	DiccString<interfaz>* x = vecinos.obtener(c1);
	bool res = x->definido(c2);
	return res;
	}

#endif
