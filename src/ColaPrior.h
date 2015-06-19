#ifndef COLAPRIOR_H
#define COLAPRIOR_H

#include "aed2.h"


template<class T>
class ColaPrior {
public:
	//Constructor por defecto: crea una cola vacía
	//Cumple con el diseño de Vacia()
	ColaPrior();

	//Destructor
	~ColaPrior();

	//Agrega el elmento a la cola.
	void Encolar(const T elem);

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
};

template<class T>
ColaPrior<T>::ColaPrior(): cabeza(NULL), tam(0) {}

template<class T>
void ColaPrior<T>::Encolar(const T elem) {
	Nodo* nuevo = new Nodo(elem);
	if(tam == 0){
		cabeza = nuevo;
	}else{
		//Armo el recorrido hasta la primer posición libre
		Lista<Nat> recorridoHastaUltimo();
		Nat x = tam + 1;
		do {
			recorridoHastaUltimo.AgregarAdelante(x % 2);
			x = x/2;
		}while(x > 1);

		Nodo* padreNuevo = cabeza;
	}
}

#endif