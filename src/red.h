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

private:
  Conj<Lista<Compu> > CaminosDeLargoN(Compu c1, Compu c2, Nat n);

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

  return false;
}

Conj<Lista<Compu> > Red::CaminosMinimos(Compu c1, Compu c2){
  Nat k = 1;
  Nat n = Computadoras().Cardinal();
  Conj<Lista<Compu> > x = CaminosDeLargoN(c1, c2, k);
 
	while(k<n && x.EsVacio()){
    k++;	
		x = CaminosDeLargoN(c1,c2, k);
  }
  return x;
	
}

bool Red::HayCamino(Compu c1, Compu c2){
  return !(CaminosMinimos(c1,c2).EsVacio());
	
}

Conj<Lista<Compu> > Red::CaminosDeLargoN(Compu c1, Compu c2, Nat n){
  Conj<Lista<Compu> > caminos;	
  if(n == 0){
    Lista<Compu> camino;
    camino.AgregarAtras(c1);
    caminos.AgregarRapido(camino);
  } else {
    Conj<Compu> vec = this->Vecinos(c1);
    Conj<Compu>::Iterador itVecinos(vec);
    while(itVecinos.HaySiguiente()){
      Compu v = itVecinos.Siguiente();
      Conj<Lista<Compu> > cams = this->CaminosDeLargoN(v, c2, n-1);

      Conj<Lista<Compu> >::Iterador itCaminos(cams);

      while(itCaminos.HaySiguiente()){
        Lista<Compu> camino = itCaminos.Siguiente();
        if(camino.Ultimo() == c2){
          Lista<Compu> camino2 = camino;
          camino2.AgregarAdelante(c1);
          caminos.Agregar(camino2);
        } 
        itCaminos.Avanzar();
      }
      itVecinos.Avanzar();
    }
  }

  Conj<Lista<Compu> >::Iterador itCaminos2(caminos);
  while(itCaminos2.HaySiguiente()){
    if(itCaminos2.Siguiente().Ultimo() != c2){
      itCaminos2.EliminarSiguiente();
    }
	   
		if(itCaminos2.HaySiguiente()) itCaminos2.Avanzar(); //esta linea faltaba en el tp
  }

  return caminos;
}


#endif
