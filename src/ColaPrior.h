#ifndef COLAPRIOR_H
#define COLAPRIOR_H

#include "aed2.h"
#include <iostream>

using namespace std;

template<class T>
class ColaPrior {
public:
	//Constructor por defecto: crea una cola vacía
	//Cumple con el diseño de Vacia()
	ColaPrior(orden(*comp)(const T, const T));

	//Destructor
	~ColaPrior();

	//
	bool Vacia() const;

	//Agrega el elmento a la cola.
	void Encolar(const T elem);

	//
	T Desencolar();

	//Devuelve el elemento más prioritario
	T Proximo() const;

private:
	struct Nodo{
		Nodo(const T elem): dato(elem), padre(NULL), izq(NULL), der(NULL){}
		T dato;
		Nodo* padre;
		Nodo* izq;
		Nodo* der;
	};

	Nodo* cabeza;
	Nat tam;
  	orden(*compar)(const T, const T);

	void Intercambiar(Nodo* padre, Nodo* hijo){
    if(hijo == padre -> izq){
      
      Nodo * derechoPadre = padre->der;
      padre->der = hijo->der;
      padre->izq = hijo->izq;
      hijo->izq = padre;
      hijo->der = derechoPadre;

      if(derechoPadre != NULL)  derechoPadre->padre = hijo;
    } else{
      Nodo * izquierdoPadre = padre->izq;
      padre->izq = hijo->izq;
      padre->der = hijo->der;
      hijo->der = padre;
      hijo->izq = izquierdoPadre;

      if(izquierdoPadre != NULL)  izquierdoPadre->padre = hijo;
    }
    hijo->padre = padre->padre;
    padre->padre = hijo;
    if(hijo -> padre == NULL){
      cabeza = hijo;
    } else{
      if(hijo->padre->izq == padre)
        hijo->padre->izq = hijo;
      else
        hijo->padre->der = hijo;
    }
    if(padre->izq != NULL)
      padre->izq->padre = padre;
    if(padre->der != NULL)
      padre->der->padre = padre;

  }

  void print(Nodo* cab, bool primero = true){
    if(cab != NULL){
      std::cout << "("<< cab->dato << " ";
      print(cab->izq, false);
      print(cab->der, false);
      std::cout << ")";
      if(primero) std::cout << std::endl;
    }
  }
  bool chequeo_inv(Nodo * cab){
    if(cab == NULL) return true;
    if(cab->der != NULL){
      if(cab->izq == NULL) return false;
      if(cab->izq->padre != cab) {std::cout << "se rompio link " << cab->dato; return false;}
      if(cab->der->padre != cab) {std::cout << "se rompio link " << cab->dato; return false;}
    
      if(cab->dato > cab->izq->dato) {std::cout << "mas grande"; return false;}
      if(cab->dato > cab->der->dato) {std::cout << "mas grande"; return false;}

      if(!chequeo_inv(cab->izq)) return false;
      if(!chequeo_inv(cab->der)) return false;
    } else if(cab->izq != NULL){
      if(cab->izq->padre != cab) {std::cout << "se rompio link"; return false;}
      if(cab->dato > cab->izq->dato) {std::cout << "mas grande"; return false;}
   
      if(!chequeo_inv(cab->izq)) return false;
    }
    return true;
  }
};

template<class T>
ColaPrior<T>::ColaPrior(orden(*comp)(const T, const T)): cabeza(NULL), tam(0), compar(comp) {}

template<class T>
ColaPrior<T>::~ColaPrior(){
	while(tam > 0){
		Desencolar();
	} 
}

template<class T>
bool ColaPrior<T>::Vacia() const {
	return (tam == 0);
}

template<class T>
void ColaPrior<T>::Encolar(const T elem) {

	Nodo* nuevo = new Nodo(elem);
	if(tam == 0){	
		cabeza = nuevo;
	}else{
		//Armo el recorrido hasta la primer posición libre
		Lista<Nat> recorridoHastaUltimo;
		Nat x = tam + 1;
		while(x > 1){
			recorridoHastaUltimo.AgregarAdelante(x % 2);
			x = x/2;
		}

		//Agrego el nodo nuevo en el primer lugar libre
		Nodo* padreNuevo = cabeza;
		Nat ultimo = recorridoHastaUltimo.Ultimo();
		recorridoHastaUltimo.Comienzo();
		Lista<Nat>::Iterador it = recorridoHastaUltimo.CrearIt();
		while(it.HaySiguiente()){
			if (it.Siguiente() == 0){
				padreNuevo = padreNuevo->izq;
			}else{
				padreNuevo = padreNuevo->der;
			}
			it.Avanzar();
		}

 nuevo->padre = padreNuevo;
		if (ultimo == 0)
		{
			padreNuevo->izq = nuevo;
		}else{
			padreNuevo->der = nuevo;
		}

		//Reposiciono el nuevo elemento donde corresponde
		Nodo* actual = nuevo;
    while(actual->padre != NULL && compar(actual->padre->dato, actual->dato) == GT){
      Intercambiar(actual->padre, actual); 
    }

	}
	tam++;
}

template<class T>
T ColaPrior<T>::Desencolar(){
	assert(!Vacia());
	T res = Proximo();

 
	if (tam == 1){
	 	
	 	delete cabeza;
	 	cabeza = NULL;
	 }else{
	 	//Armo el recorrido hasta la primer posición libre
		Lista<Nat> recorridoHastaUltimo;
		Nat x = tam;
		while(x > 1){
			recorridoHastaUltimo.AgregarAdelante(x % 2);
			x = x/2;
		}
		
		Nodo* ultimo = cabeza;
		Lista<Nat>::Iterador it = recorridoHastaUltimo.CrearIt();
		while(it.HaySiguiente()){
			if(it.Siguiente() == 0)
			{
				ultimo = ultimo->izq;
			}else{
				ultimo = ultimo->der;
			}
			it.Avanzar();
		}

		if(recorridoHastaUltimo.Ultimo() == 1){
			Nodo* papa = ultimo->padre;
			papa->der = NULL;
		}else{
			Nodo* papa = ultimo->padre;
			papa->izq = NULL;
		}
		
		ultimo->der = cabeza->der;
		if(cabeza->der != NULL) cabeza->der->padre = ultimo;
		ultimo->izq = cabeza->izq;
		if(cabeza->izq != NULL) cabeza->izq->padre = ultimo;
		ultimo->padre = NULL;
		delete cabeza;
		cabeza = ultimo;

		//Bajo el elemento que esta en la cabeza hasta que se restablezca el invariante
		Nodo* actual = cabeza;

    	while((actual->izq != NULL && compar(actual->dato, actual->izq->dato) == GT) || (actual->der != NULL && compar(actual->dato, actual->der->dato) == GT)){
      		if(actual->der == NULL){
        		if(compar(actual->izq->dato, actual->dato) == LT)
          			Intercambiar(actual, actual->izq);
      			} else {
        			if(compar(actual->izq->dato, actual->dato) == LT && compar(actual->izq->dato, actual->der->dato) == LT){
          				Intercambiar(actual, actual->izq);
        			} else {
          				Intercambiar(actual, actual->der);
        		}
      		}  
    	}
	}
	tam--;
	return res;
}

template<class T>
T ColaPrior<T>::Proximo() const{
	return cabeza->dato;
}

#endif
