#ifndef RED_H
#define RED_H

#include "aed2.h"
#include "defines.h"
#include <iostream>

using namespace std;


class Red {
public:
  Red();
  ~Red();

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
	vecinos = DiccString<DiccString<Interfaz> >();
	interfaces = DiccString<Conj<Interfaz> >();
	}
Red::~Red(){
//	vecinos.~DiccString<DiccString<Interfaz> >();
//	interfaces.~DiccString<Conj<Interfaz> >();
	}
void Red::AgregarComputadora(Compu c, Conj<Interfaz> is){
	DiccString<Interfaz> vacio;
	vecinos.definir(c, vacio);
	interfaces.definir(c,is);
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
/**
Conj<Compu> Red::Computadoras(){
	vector<Compu> vec;
	vec = interfaces.claves();
	Conj<Compu> con;
	while(!(vec.EsVacio())){
		con.Agregar(vec.Ultimo());
		vec.TirarUltimos(1);
		}
	return con;
	}
**/
Interfaz Red::InterfazUsada(Compu c1, Compu c2){
	
	}

Conj<Compu> Red::Vecinos(Compu c){
	
	}

bool Red::UsaInterfaz(Compu c, Interfaz i){
	
	
	}

Conj<Lista<Compu> > Red::CaminosMinimos(Compu c1, Compu c2){
	
	
	}

bool Red::HayCamino(Compu c1, Compu c2){
	
	
	}

Conj<Lista<Compu> > Red::CaminosDeLargoN(Compu c1, Compu c2, Nat n){

	}


#endif
