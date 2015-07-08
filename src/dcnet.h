#ifndef DCNET_H_
#define DCNET_H_
#include "aed2.h"
#include "ColaPrior.h"
#include "DiccAvl.h"
#include "ConjAVL.h"
#include "red.h"
#include "defines.h"
#include <iostream>

using namespace std;


orden ComparIdx(const PaqueteN p1, const PaqueteN p2);

orden ComparPrioridadx(const PaqueteN p1, const PaqueteN p2);

class DcNet{
public:
	DcNet(Red *); //es const por dicc_trie, rompe todo
	~DcNet();

	void CrearPaquete(PaqueteN paq);
	void AvanzarSegundo();
	Red& ObtenerRed() const;
	const Lista<Compu>& CaminoRecorrido(const PaqueteN& paq) const;
	Nat CantidadEnviados(const Compu& c);
	const ConjLog<PaqueteN>& EnEspera(const Compu& c);
	bool PaqueteEnTransito(const PaqueteN& paq) const;
	const Compu& LaQueMasEnvio() const;

private:
	typedef struct InfoPaquetes_t{
		InfoPaquetes_t() : cola(new ColaPrior<PaqueteN>(&ComparPrioridadx)),
        	 diccPaqCamino(new DiccLog<PaqueteN, Lista<Lista<Compu> >::Iterador>(&ComparIdx)),
           conjPaquetes(new ConjLog<PaqueteN>(&ComparIdx)),
           cantidadEnviados(0)
					 {}
		
    	ColaPrior<PaqueteN> * cola; //(orden ComparPrioridad(PaqueteN, PaqueteN));
		DiccLog<PaqueteN, Lista<Lista<Compu> >::Iterador> * diccPaqCamino; //(orden ComparId(PaqueteN, PaqueteN));
		ConjLog<PaqueteN> * conjPaquetes; //(orden ComparId(PaqueteN, PaqueteN));
		Nat cantidadEnviados;
	} InfoPaquetes;

	Red* red;
	Lista<Lista<Compu> > caminosRecorridos;
	struct {Nat cuantosEnvio ; Compu cualCompu;} laQueMasEnvio;
	DiccString<DiccString<Compu> >  proximaEnCamino;
	DiccString<InfoPaquetes> paquetes;

};

#endif // DCNET_H
