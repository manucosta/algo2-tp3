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

	orden ComparId(PaqueteN p1, PaqueteN p2){
		if(p1.id < p2.id){
			return LT;
		}else if(p1.id == p2.id){
			return EQ;
		}else{
			return GT;
		}
	}

	orden ComparPrioridad(PaqueteN p1, PaqueteN p2){
		if(p1.prioridad < p2.prioridad){
			return LT;
		}else if(p1.prioridad == p2.prioridad){
			return EQ;
		}else{
			return GT;
		}
	}

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
	    InfoPaquetes tupInfoPaquetes;
	    tupInfoPaquetes.cantidadEnviados = 0;
	    paquetes.definir(it.Siguiente(), tupInfoPaquetes);
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

void AvanzarSegundo(){
	struct paquetesAEnv{
		PaqueteN p;
		Lista<Id>::Iterador it;
	};

	//Lista<struct paquetesAEnv> paquetesAEnviar;


}



#endif // DCNET_H
