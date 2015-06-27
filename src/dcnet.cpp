#include "dcnet.h"

DcNet::DcNet(const Red& r){
	red = r;
	caminosRecorridos = Lista<Lista<Compu> >();
	Conj<Compu> compus = red.Computadoras();
	Conj<Compu>::Iterador it = compus.CrearIt();
	laQueMasEnvio.cuantosEnvio = 0;
	laQueMasEnvio.cualCompu = it.Siguiente();
	proximaEnCamino = DiccString<DiccString<Compu> >();
	while(it.HaySiguiente()) {
	    Conj<Compu>::Iterador it2 = compus.CrearIt();
	    DiccString<Compu*> diccActual;
	    InfoPaquetes tupInfoPaquetes;
	    tupInfoPaquetes.cantidadEnviados = 0;
	    paquetes.definir(it.Siguiente(), tupInfoPaquetes);
	    while(it2.HaySiguiente()){
	        Conj<Lista<Compu> > camMinimos = red.CaminosMinimos(it.Siguiente(), it2.Siguiente());
	        Conj<Compu>::Iterador it3 = camMinimos.CrearIt();
	        Lista<Compu> caminoMinimo = it3.Siguiente();
	        caminoMinimo.Fin();
	        Compu* siguiente = &(caminoMinimo.Primero());
	        diccActual.Definir(it2.Siguiente(), siguiente);
	        it2.Avanzar();
	    }
	    proximaEnCamino.definir(it.Siguiente, diccActual);
	    it.Avanzar();
	}
}