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

	void Intercambiar(Nodo* padre, Nodo* hijo){
    if(hijo == padre -> izq){
      Nodo * derechoPadre = padre->der;
      padre->der = hijo->der;
      padre->izq = hijo->izq;
      hijo->izq = padre;
      hijo->der = derechoPadre;
    } else{
      Nodo * izquierdoPadre = padre->izq;
      padre->izq = hijo->izq;
      padre->der = hijo->der;
      hijo->der = padre;
      hijo->izq = izquierdoPadre;
    }
    hijo->padre = padre->padre;
    padre->padre = hijo;
    if(hijo -> padre == NULL){
      cabeza = hijo;
    }
  }

  void print(Nodo* cab, bool primero = true){
    if(cab != NULL){
      std::cout << cab->dato << " ";
      print(cab->izq, false);
      print(cab->der, false);
      if(primero) std::cout << std::endl;
    }
  }
  bool chequeo_inv(Nodo * cab){
    if(cab == NULL) return true;
    if(cab->der != NULL){
      if(cab->izq == NULL) return false;
      if(cab->izq->padre != cab) return false;
      if(cab->der->padre != cab) return false;
    
      if(cab->dato > cab->izq->dato) return false;
      if(cab->dato > cab->der->dato) return false;

      if(!chequeo_inv(cab->izq)) return false;
      if(!chequeo_inv(cab->der)) return false;
    } else if(cab->izq != NULL){
      if(cab->izq->padre != cab) return false;
      if(cab->dato > cab->izq->dato) return false; 
   
      if(!chequeo_inv(cab->izq)) return false;
    }
    return true;
  }



};

template<class T>
ColaPrior<T>::ColaPrior(): cabeza(NULL), tam(0) {}

template<class T>
ColaPrior<T>::~ColaPrior(){
	while(tam > 0){
		Desencolar();
	}
  //std::cout << "quiere borrar" << std::endl;
}

template<class T>
bool ColaPrior<T>::Vacia() const {
	return (tam == 0);
}

template<class T>
void ColaPrior<T>::Encolar(const T elem) {


  

	Nodo* nuevo = new Nodo(elem);
	if(tam == 0){
		//cout<<"Encolo: "<<nuevo->dato<<endl;
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
		//std::cout << "Encolo: "<< actual->dato<< std::endl;
		/*while(actual->padre != NULL && actual->padre->dato > actual->dato){
			T x = actual->dato;
			actual->dato = actual->padre->dato;
			actual->padre->dato = x;
			actual = actual->padre;
		}*/

    while(actual->padre != NULL && actual->padre->dato > actual->dato){
      Intercambiar(actual->padre, actual);
    }

	}
	tam++;
 
  //std::cout << tam << ": "; print(cabeza); 
}

template<class T>
T ColaPrior<T>::Desencolar(){
	assert(!Vacia());
	T res = Proximo();

 //std::cout << "cumple invariante al principio: " << chequeo_inv(cabeza) << std::endl;
	if (tam == 1){
	 	//std::cout<< cabeza->dato << std::endl;
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
		/*while((actual->izq != NULL && actual->dato > actual->izq->dato) || 
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
		}*/

    while((actual->izq != NULL && actual->dato > actual->izq->dato) || (actual->der != NULL && actual->dato > actual->der->dato)){
      if(actual->der == NULL){
        if(actual->izq->dato < actual->dato){
          Intercambiar(actual, actual->izq);
        } else {
          if(actual->izq->dato < actual->dato && actual->izq->dato < actual->der->dato){
            Intercambiar(actual, actual->izq);
          } else {
            Intercambiar(actual, actual->der);
          }
        }
      }
    }
	}
	tam--;
  //std::cout << "cumple invariante al final: " << chequeo_inv(cabeza) << std::endl;

	return res;
}

template<class T>
T ColaPrior<T>::Proximo() const{
	return cabeza->dato;
}

#endif
