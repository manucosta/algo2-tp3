#ifndef COLAPRIOR_H
#define COLAPRIOR_H

#include <iostream>
#include "aed2.h"

template<class T>
class ColaPrior {
public:
	//Constructor por defecto: crea una cola vacía
	//Cumple con el diseño de Vacia()
	ColaPrior();

	//Destructor
	~ColaPrior();

	//
	bool Vacia() const;

	//Agrega el elmento a la cola.
	void Encolar(const T elem);

	//
	T& Desencolar();

	//Devuelve el elemento más prioritario
	T& Proximo() const;

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

	void Intercambiar(Nodo*, Nodo* );
};

//Operador de comparación (como no-miembro)
template<class T>
bool operator==(const Arreglo<T>&, const Arreglo<T>&);

template<class T>
ColaPrior<T>::ColaPrior(): cabeza(NULL), tam(0) {}

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
			if (it.Siguiente() == 0)
			{
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
		while(actual->padre != NULL && actual->padre->dato > actual->dato){
			Intercambiar(actual->padre, actual);
		}
	}
	tam++;
}

template<class T>
T& ColaPrior<T>::Desencolar(){
	assert(!Vacia());
	T& res = cabeza->dato;
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

		//Quito el ultimo nodo y lo pongo como nueva cabeza
		//En este cacho hay un problema con la memoria
		std::cout<< ultimo->dato;//debug
		if(recorridoHastaUltimo.Ultimo() == 1){
			Nodo* papa = ultimo->padre;//der
			papa->der = NULL;
		}else{
			Nodo* papa = ultimo->padre;//izq
			papa->izq = NULL;
		}
		
		ultimo->der = cabeza->der;
		ultimo->izq = cabeza->izq;
		ultimo->padre = NULL;
		delete cabeza;
		cabeza = ultimo;

		//Bajo el elemento que esta en la cabeza hasta que se restablezca el invariante
		Nodo* actual = cabeza;
		while((actual->izq != NULL && actual->dato > actual->izq->dato) || 
				(actual->der != NULL && actual->dato > actual->der->dato)){
			
			if(actual->der == NULL || actual->dato > actual->izq->dato){
				Intercambiar(actual, actual->izq);
			}else{
				Intercambiar(actual, actual->der);
			}
		}

	}
	tam--;
	return res;
}

template<class T>
void ColaPrior<T>::Intercambiar(Nodo* padre, Nodo* hijo){
	if(hijo == padre->izq){
		Nodo* derechaPadre = padre->der;
		padre->der         = hijo->der;
		padre->izq         = hijo->izq;
		hijo->izq          = padre;
		hijo->der          = derechaPadre;
	}else{
		Nodo* izquierdaPadre = padre->izq;
		padre->der         	= hijo->der;
		padre->izq        	= hijo->izq;
		hijo->der         	= padre;
		hijo->izq          	= izquierdaPadre;
	}

	hijo->padre = padre->padre;
	padre->padre = hijo;
	if(hijo->padre == NULL){
		this->cabeza = hijo;
	}
}

template<class T>
T& ColaPrior<T>::Proximo() const{
	return cabeza->dato;
}

/**
template<class T>
bool operator==(const ColaPrior<T>& cola1, const ColaPrior<T>& cola2){
	bool vacia_1 = cola1.Vacia();
	bool vacia_2 = cola2.Vacia();
	if(vacia_1 == vacia_2){
		if(!vacia_1){
			T& min1 = cola1.Desencolar();
			T& min2 = cola2.Desencolar();

		}
	}else{
		return false;
	}
}
**/

#endif