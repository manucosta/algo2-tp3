#ifndef DCNET_H
#define DCNET_H

#include "ColaPrior.h"
#include "DiccAvl.h"
#include "ConjAVL.h"
#include "red.h"
#include <iostream>

using namespace std;

struct Paquete{
	Id id;
	Prioridad prioridad;
	Compu origen;
	Compu destino;
};

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
		ColaPrior<Paquete> colas;
		DiccLog<Paquete, Lista<Lista<Compu> >::Iterador> diccPaqCamino;
		ConjLog<Paquete> conjPaquetes;
		Nat cantidadEnviados;
	};

	DiccString<Compu> proximaEnCamino;
	DiccString<InfoPaquetes> paquetes;
	Lista<Lista<Compu> > caminosRecorridos;
	struct {Nat cuantosEnvio ; Compu cualCompu;} laQueMasEnvio;
	Red red;
};


#endif // DCNET_H
