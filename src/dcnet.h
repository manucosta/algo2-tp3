##ifndef DCNET_H
#define DCNET_H

#include "ColaPrior.h"
#include "DiccAvl.h"
#include "ConjAVL.h"
#include "red.h"
#include <iostream>

using namespace std;

class DcNet{
public:
	DcNet(const Red&);
	~DcNet();

	void CrearPaquete(const Paquete& paq);
	void AvanzarSegundo();
	const Red& Red() const;
	const Lista<Compu>& CaminoRecorrido(const Paquete& paq) const;
	Nat CantidadEnviados(const Compu& c) const;
	const Conj<Paquete>& EnEspera(const Compu& c) const;
	bool PaqueteEnTransito(const Paquete& paq) const;
	const Compu& LaQueMasEnvio() const;
}


#endif // DCNET_H
