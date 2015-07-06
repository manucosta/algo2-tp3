#ifndef CONJAVL_H
#define CONJAVL_H

#include "aed2.h"
#include "DiccAvl.h"
#include <iostream>

using namespace std;

template<typename T>
class ConjLog {
public:
  void Agregar(const T x);
  bool Pertenece(const T x);
  void Eliminar(const T x);
  Nat Cardinal() const;

  ConjLog(orden(*compar)(const T, const T));
  ConjLog(){c = NULL;}
  
  ~ConjLog();

private:
  DiccLog<T, Nat> * c;
};



template <typename T>
ConjLog<T>::ConjLog(orden(*compar)(const T, const T)){
  c = new DiccLog<T, Nat>(compar);
}

template <typename T>
ConjLog<T>::~ConjLog(){
  delete c;
}

template <typename T>
void ConjLog<T>::Agregar(const T x){
  return c->Definir(x, 0);
}


template <typename T>
bool ConjLog<T>::Pertenece(const T x){
  return c->Definido(x);
}

template <typename T>
void ConjLog<T>::Eliminar(const T x){
  return c->Borrar(x);
}

template <typename T>
Nat ConjLog<T>::Cardinal() const {
  return c->CantidadClaves();
}



#endif
