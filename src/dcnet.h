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
	DcNet(const Red&);
	~DcNet();

	void CrearPaquete(const Paquete& paq);
	void AvanzarSegundo();
	const Red& ObtenerRed() const;
	const Lista<Compu>& CaminoRecorrido(const Paquete& paq) const;
	Nat CantidadEnviados(const Compu& c) const;
	const Conj<Paquete>& EnEspera(const Compu& c) const;
	bool PaqueteEnTransito(const Paquete& paq) const;
	const Compu& LaQueMasEnvio() const;

private:
	struct InfoPaquetes{
		InfoPaquetes() : colas()
		ColaPrior<Paquete> colas;
		DiccLog<Paquete, Lista<Lista<Compu> >::Iterador> diccPaqCamino;
		ConjLog<Paquete> conjPaquetes;
		Nat cantidadEnviados;
	};

	Red red;
	Lista<Lista<Compu> > caminosRecorridos;
	struct {Nat cuantosEnvio ; Compu cualCompu;} laQueMasEnvio;
	DiccString<Compu> proximaEnCamino;
	DiccString<InfoPaquetes> paquetes;

	orden ComparId(Paquete p1, Paquete p2){
		if(p1.id < p2.id){
			return LT;
		}else if(p1.id == p2.id){
			return EQ;
		}else{
			return GT;
		}
	}

	orden ComparPrioridad(Paquete p1, Paquete p2){
		if(p1.prioridad < p2.prioridad){
			return LT;
		}else if(p1.prioridad == p2.prioridad){
			return EQ;
		}else{
			return GT;
		}
	}
	
	

};


#endif // DCNET_H
