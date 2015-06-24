#ifndef DICCAVL_H
#define DICCAVL_H

#include "aed2.h"
#include <iostream>

using namespace std;

template<class K, class S>
class DiccAvl {
public:
  void Definir(const K clave, const S significado);
  bool Definido(const K clave);
  void Borrar(const K clave);
  
  DiccAvl();
  
  ~DiccAvl();

private:
	struct Nodo {
		K clave;
		S significado;
		int altura;
		Nodo* izq;
		Nodo* der;
		Nodo(K clav, S signif):significado(signif), clave(clav), izq(NULL),der(NULL),altura(1){}
	  Nodo(){}
  };

  Nodo** raiz;
  Nodo* raiz2;

	int max(int a, int b){return (a>b)?a:b;}
	void actualizarAltura(Nodo* p);
	int altura(Nodo* p);
  void rotarSimple(Nodo** a, bool rota_izq);
	void rotarDoble(Nodo** a, bool rota_izq);
	void balancear(Nodo** a);

  void _Definir(Nodo** d, K k, S s);
  bool _Definido(Nodo** d, K k);
  void _Borrar(Nodo** d, K k);



  Nodo borrarMin(Nodo** d){
    if((*d)->izq != NULL){
      Nodo res = borrarMin(&((*d)->izq));
      balancear(d);
      actualizarAltura(*d);
      return res;
    } else{
      Nodo * aux = *d;
      Nodo n(aux->clave, aux->significado);
      *d = (*d)->der;
      delete aux;
      balancear(d);
      actualizarAltura(*d);
      return n;
    }
  }

  int alturaNodo(Nodo * n){return n? n->altura : 0;}
};


template <typename K, typename S>
DiccAvl<K,S>::DiccAvl(){
  raiz2 = NULL;
  raiz = &raiz2;
}

template <typename K, typename S>
DiccAvl<K,S>::~DiccAvl(){
  while(*raiz != NULL){
    Borrar((*raiz)->clave);
  }
}


template <typename K, typename S>
void DiccAvl<K,S>::actualizarAltura(Nodo* p){
	if (p != NULL){
		p->altura = 1 + max(alturaNodo(p->izq),alturaNodo(p->der));	
	}
}

template <typename K, typename S>
int DiccAvl<K, S>::altura(Nodo* p){
	if (p != NULL){
		return 1 + max(altura(p->izq),altura(p->der));	
	}
	return 0;
}


template <typename K, typename S>
void DiccAvl<K, S>::rotarSimple(Nodo** a, bool rota_izq){
	Nodo* a1;
	if (rota_izq){
    a1 = (*a)->izq;
    ((*a)->izq)= a1->der;
    (a1->der)= *a;
	} else {
    a1 = (*a)->der;
    (*a)->der = a1->izq;
    a1->izq = *a;
	}
	actualizarAltura(*a);
	actualizarAltura(a1);
	*a = a1;
}



template <typename K, typename S>
void DiccAvl<K, S>::rotarDoble(Nodo** a, bool rota_izq){
	if (rota_izq){
		rotarSimple(&((*a)->izq),false);
		rotarSimple(a,true);
	} else {
		rotarSimple(&((*a)->der),true);
		rotarSimple(a,false);
	}
}


template <typename K, typename S>
void DiccAvl<K, S>::balancear(Nodo** a){
	if(*a!=NULL){
    if (alturaNodo((*a)->izq) >= alturaNodo((*a)->der)){
			if( alturaNodo((*a)->izq) - alturaNodo((*a)->der) == 2){
        if (alturaNodo((*a)->izq->izq) >= alturaNodo((*a)->izq->der))
          rotarSimple(a,true);
				else rotarDoble(a, true);
      }
		} else {
			if (alturaNodo((*a)->der) - alturaNodo((*a)->izq) == 2) {
				if (alturaNodo((*a)->der->der) >= alturaNodo((*a)->der->izq)) 
          rotarSimple(a, false);
        else rotarDoble(a, false);		  
      }		
		}
	}
}

template <typename K, typename S>
void DiccAvl<K, S>::_Definir(Nodo** d, const K k, const S s){

  if(*d == NULL){
    Nodo * nuevo = new Nodo;
    nuevo->clave = k; nuevo->significado = s;
    nuevo->der = NULL; nuevo->izq = NULL;
    nuevo->altura = 1;

    *d = nuevo;
  } else {
    if(k < (*d)->clave){
      _Definir(&((*d)->izq), k, s);
    } else {
      _Definir(&((*d)->der), k, s);
    }
  }

  balancear(d);
  actualizarAltura(*d);
}

template <typename K, typename S>
void DiccAvl<K, S>::Definir(const K clav, const S signif){
  _Definir(raiz, clav, signif);
}



template <typename K, typename S>
bool DiccAvl<K, S>::_Definido(Nodo** d, const K k){
  if(*d == NULL){
    return false;
  } else {
    if(k < (*d)->clave){
      return _Definido(&((*d)->izq), k);
    } else if(k > (*d)->clave){
      return _Definido(&((*d)->der), k);
    } else {
      return true;
    }
  }
}



template <typename K, typename S>
void DiccAvl<K, S>::_Borrar(Nodo** d, const K k){
  Nodo * aux;

  if(k < (*d)->clave){
    _Borrar(&(*d)->izq, k);
  } else if(k > (*d)->clave){
    _Borrar(&(*d)->der, k);
  } else{
    if((*d)->izq == NULL && (*d)->der == NULL){
      delete *d;
      *d = NULL;
    } else if((*d)->izq == NULL){
      aux = *d;
      *d = (*d)->der;
      delete aux;
      aux = NULL;
    } else if((*d)->der == NULL){
      aux = *d;
      *d = (*d)->izq;
      delete aux;
      aux = NULL;
    } else {
      Nodo min = borrarMin(&((*d)->der));
      (*d)->clave = min.clave;
      (*d)->significado = min.significado;
    }
  }
  balancear(d);
  actualizarAltura(*d);

}


template <typename K, typename S>
bool DiccAvl<K, S>::Definido(const K clav){
  return _Definido(raiz, clav);
}


template <typename K, typename S>
void DiccAvl<K, S>::Borrar(const K clav){
  _Borrar(raiz, clav);
}





#endif
