#include "dcnet.h"

DcNet::DcNet(const Red& r){
	red = r;
	caminosRecorridos = Lista();
	Conj<Compu> compus = red.Computadoras();
	Conj<Compu>::Iterador it = compus.CrearIt();
	laQueMasEnvio.cuantosEnvio = 0;
	laQueMasEnvio.cualCompu = it.Siguiente();
	proximaEnCamino = DiccString();



}