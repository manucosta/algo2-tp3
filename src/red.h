#ifndef RED_H
#define RED_H

#include "aed2.h"
#include "defines.h"
#include <iostream>

using namespace std;


class Red {
public:
  Red();

  void AgregarComputadora(Compu c, Conj<Interfaz> is);
  void Conectar(Compu c1, Compu c2, Interfaz i1, Interfaz i2);
  bool Conectadas(Compu c1, Compu c2);
  Conj<Compu> Computadoras();
  Interfaz InterfazUsada(Compu c1, Compu c2);
  Conj<Compu> Vecinos(Compu c);
  bool UsaInterfaz(Compu c, Interfaz i);
  Conj<Lista<Compu> > CaminosMinimos(Compu c1, Compu c2);
  bool HayCamino(Compu c1, Compu c2);
  Conj<Lista<Compu> > CaminosDeLargoN(Compu c1, Compu c2, Nat n);


private:
  DiccString<DiccString<Interfaz> > vecinos;
  DiccString<Conj<Interfaz> > interfaces;

};


Red::Red(){
	DiccString<DiccString<Interfaz> > vecinos;
	DiccString<Conj<Interfaz> > interfaces;
}

void Red::AgregarComputadora(Compu c, Conj<Interfaz> is){
	DiccString<Interfaz> vacio;
	vecinos.definir(c, vacio);
	//interfaces.definir(c,is);
}

void Red::Conectar(Compu c1, Compu c2, Interfaz i1, Interfaz i2){
	DiccString<Interfaz>* x;
	x = vecinos.obtener(c1);
	x->definir(c2,i1);
	DiccString<Interfaz>* y;
	y = vecinos.obtener(c2);
	y->definir(c1,i2);
}

bool Red::Conectadas(Compu c1, Compu c2){
	DiccString<Interfaz>* x = vecinos.obtener(c1);
	bool res = x->definido(c2);
	return res;
}


Conj<Compu> Red::Computadoras(){
	vector<string> vec = vecinos.claves();
  
  Conj<Compu> con;
  for(unsigned int i = 0; i<vec.size(); i++){
    con.Agregar(vec[i]);
  }

	return con;
}


Interfaz Red::InterfazUsada(Compu c1, Compu c2){
  DiccString<Interfaz> * x = vecinos.obtener(c1);
  return *(x->obtener(c2));
}

Conj<Compu> Red::Vecinos(Compu c){
  DiccString<unsigned int> * x = vecinos.obtener(c);

	vector<string> vec = x->claves();
  
  Conj<Compu> con;
  for(unsigned int i = 0; i<vec.size(); i++){
    con.Agregar(vec[i]);
  }
  return con;
}

bool Red::UsaInterfaz(Compu c, Interfaz i){
  DiccString<unsigned int> * x = vecinos.obtener(c);

  DiccString<unsigned int>::Iterador it(x);

  while(1){
    if(*(it.valorActual()) == i) return true;
    if(!it.avanzar()) break; 
  }
}

Conj<Lista<Compu> > Red::CaminosMinimos(Compu c1, Compu c2){
	
	
}

bool Red::HayCamino(Compu c1, Compu c2){
	
	
}

Conj<Lista<Compu> > Red::CaminosDeLargoN(Compu c1, Compu c2, Nat n){
  Conj<Lista<Compu> > caminos;
  if(n == 0){
    Lista<Compu> camino;
    camino.AgregarAtras(c1);
    caminos.AgregarRapido(camino);
  } else {
    //Conj<Compu> vec = this->vecinos(c1);
  }
}


#endif
