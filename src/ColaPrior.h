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
		cout<<"Encolo: "<<nuevo->dato<<endl;
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
		/**DEBUG**/
		std::cout << "Encolo: "<< actual->dato<< std::endl;
		while(actual->padre != NULL && actual->padre->dato > actual->dato){
			T x = actual->dato;
			actual->dato = actual->padre->dato;
			actual->padre->dato = x;
			actual = actual->padre;
		}
	}
	tam++;
}

template<class T>
T& ColaPrior<T>::Desencolar(){
	assert(!Vacia());
	T res = Proximo();
	if (tam == 1){
	 	std::cout<< cabeza->dato << std::endl;
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

		/**DEBUG**/
		//std::cout<< ultimo->dato << std::endl;
		if(recorridoHastaUltimo.Ultimo() == 1){
			Nodo* papa = ultimo->padre;
			papa->der = NULL;
		}else{
			Nodo* papa = ultimo->padre;
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
			
			T x = actual->dato;
			if(actual->der == NULL || actual->dato > actual->izq->dato){
				actual->dato = actual->izq->dato;
				actual->izq->dato = x;
				actual = actual->izq;
			}else{
				actual->dato = actual->der->dato;
				actual->der->dato = x;
				actual = actual->der;
			}
		}
	}
	tam--;
	return res;
}

template<class T>
T& ColaPrior<T>::Proximo() const{
	return cabeza->dato;
}

#endif
