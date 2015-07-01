#ifndef DCNET_H
#define DCNET_H
#include "aed2.h"
#include "ColaPrior.h"
#include "DiccAvl.h"
#include "ConjAVL.h"
#include "red.h"
#include "defines.h"
#include <iostream>

using namespace std;


	orden ComparId(const PaqueteN p1, const PaqueteN p2){
		if(p1.id < p2.id){
			return LT;
		}else if(p1.id == p2.id){
			return EQ;
		}else{
			return GT;
		}
	}

	orden ComparPrioridad(const PaqueteN p1, const PaqueteN p2){
		if(p1.prioridad < p2.prioridad){
			return LT;
		}else if(p1.prioridad == p2.prioridad){
			return EQ;
		}else{
			return GT;
		}
	}

class DcNet{
public:
	DcNet(Red&); //es const por dicc_trie, rompe todo
	//~DcNet();

	void CrearPaquete(const PaqueteN& paq);
	void AvanzarSegundo();
	const Red& ObtenerRed() const;
	const Lista<Compu>& CaminoRecorrido(const PaqueteN& paq) const;
	Nat CantidadEnviados(const Compu& c) const;
	const Conj<PaqueteN>& EnEspera(const Compu& c) const;
	bool PaqueteEnTransito(const PaqueteN& paq) const;
	const Compu& LaQueMasEnvio() const;

private:



	typedef struct InfoPaquetes_t{
		
		InfoPaquetes_t(){
			//cola((orden(*)(const PaqueteN, const PaqueteN)) &ComparPrioridad);
			cola(&ComparPrioridad);
			diccPaqCamino(&ComparId);
			conjPaquetes(&ComparId);
			cantidadEnviados = 0;
		}
		
		ColaPrior<PaqueteN> cola; //(orden ComparPrioridad(PaqueteN, PaqueteN));
		DiccLog<PaqueteN, Lista<Lista<Compu> >::Iterador> diccPaqCamino; //(orden ComparId(PaqueteN, PaqueteN));
		ConjLog<PaqueteN> conjPaquetes; //(orden ComparId(PaqueteN, PaqueteN));
		Nat cantidadEnviados;
	} InfoPaquetes;

	Red* red;
	Lista<Lista<Compu> > caminosRecorridos;
	struct {Nat cuantosEnvio ; Compu cualCompu;} laQueMasEnvio;
	DiccString<DiccString<Compu> > proximaEnCamino;
	DiccString<InfoPaquetes> paquetes;

};


DcNet::DcNet(Red& r){
	red = &r;
	caminosRecorridos = Lista<Lista<Compu> >();
	Conj<Compu> compus = red->Computadoras();
	Conj<Compu>::Iterador it = compus.CrearIt();
	laQueMasEnvio.cuantosEnvio = 0;
	laQueMasEnvio.cualCompu = it.Siguiente();
	DiccString<DiccString<Compu> >proximaEnCamino;
	cout << endl;
  while(it.HaySiguiente()) {
	      
	    DiccString<Compu> diccActual;
	    
			/*InfoPaquetes tupInfoPaquetes;
	    tupInfoPaquetes.cantidadEnviados = 0;
	    paquetes.definir(it.Siguiente(), tupInfoPaquetes);
	    */
			
			Conj<Compu>::Iterador it2 = compus.CrearIt();

		
			while(it2.HaySiguiente()){
					Compu siguiente;
					Compu c1 = it.Siguiente();
					Compu c2 = it2.Siguiente();
					Conj<Lista<Compu> > camMinimos = red->CaminosMinimos(c1, c2);
	        Conj<Lista<Compu> >::Iterador it3 = camMinimos.CrearIt();
					
	        
					if(it3.HaySiguiente()){
	          Lista<Compu> caminoMinimo = it3.Siguiente();
	          caminoMinimo.Fin();
	          Compu siguiente = caminoMinimo.Primero();
			    } else {
						siguiente = "";
					} 
				
					diccActual.definir(it2.Siguiente(), siguiente);
	        
					it2.Avanzar();
	    }
	    proximaEnCamino.definir(it.Siguiente(), diccActual);
	    	
			it.Avanzar();
	}
}

struct paquetesAEnv{
	paquetesAEnv(const paquetesAEnv& paq) {
	  p = paq.p;
		it = paq.it;
	}
	PaqueteN p;
	Lista<Id>::Iterador it;
};

void DcNet::AvanzarSegundo(){
	Lista<struct paquetesAEnv> paquetesAEnviar;
	DiccString<InfoPaquetes>::Iterador it(&paquetes);
	//se rompe si dicc es vacio,deberiamos hacer el assert

	do{
		InfoPaquetes s = *(it.valorActual());
		ColaPrior<PaqueteN> scola = s.cola;
		if(!scola.Vacia()){
			PaqueteN estePaquete = scola.Desencolar();
		}

	}while(it.avanzar());


}

/*
	typedef struct InfoPaquetes_t{
		ColaPrior<PaqueteN> cola(orden ComparPrioridad(PaqueteN, PaqueteN));
		DiccLog<PaqueteN, Lista<Lista<Compu> >::Iterador> diccPaqCamino(orden ComparId(PaqueteN, PaqueteN));
		ConjLog<PaqueteN> conjPaquetes(orden ComparId(PaqueteN, PaqueteN));
		Nat cantidadEnviados;
	} InfoPaquetes;

	Red* red;
	Lista<Lista<Compu> > caminosRecorridos;
	struct {Nat cuantosEnvio ; Compu cualCompu;} laQueMasEnvio;
	DiccString<DiccString<Compu> > proximaEnCamino;
	DiccString<InfoPaquetes> paquetes;
*/

#endif // DCNET_H
