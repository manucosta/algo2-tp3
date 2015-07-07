#include "Driver.h"
#include "ArbolSintactico.h"

namespace aed2 {

orden comp_nat(const Nat a, const Nat b){
    if(a<b) return LT;
    else if(a==b) return EQ;
    else return GT;
}

Driver::Driver() {
    red = new Red;
    dcnet = NULL;
    proxPaq = 0;
    paq2paqN = new DiccLog<Paquete, PaqueteN>(comp_nat);
}

Driver::~Driver() {
    if(red != NULL) delete red;
    red = NULL;
    if(dcnet != NULL) delete dcnet;
    dcnet = NULL;
    if(paq2paqN != NULL) delete paq2paqN;
    paq2paqN = NULL;
}

// TAD RED
Nat Driver::CantidadComputadoras() const {
    return red->Computadoras().Cardinal();
}

const Computadora& Driver::IesimaComputadora(const Nat i) const {//Indexo desde 0
    Conj<Computadora> compus = red->Computadoras();
    Conj<Computadora>::Iterador it = compus.CrearIt();
    for(Nat j = 0; j < i && it.HaySiguiente(); j++){
        it.Avanzar();
    }
	return it.Siguiente();
}
        
Nat Driver::CantidadInterfacesDe(const Computadora& c) const {
    return red->Interfaces(c).Cardinal();
}

const Interfaz& Driver::IesimaInterfazDe(const Computadora& c, const Nat i) const{//Indexo desde 0
    Conj<Interfaz> interfaces = dcnet->ObtenerRed().Interfaces(c);
    Conj<Interfaz>::Iterador it = interfaces.CrearIt();
    for(Nat j = 0; j < i && it.HaySiguiente(); j++){
        it.Avanzar();
    }
    return it.Siguiente();
} 

const Interfaz& Driver::IntefazUsada(const Computadora& c1, const Computadora& c2) const {
    return red->InterfazUsada(c1, c2);
}


bool Driver::conectadas(const Computadora& c1, const Computadora& c2) const {
    return red->Conectadas(c1, c2);
}

//ARMADO DE RED
void Driver::AgregarComputadora(const Computadora& ip, const Conj<Interfaz>& ci) {
    red->AgregarComputadora(ip, ci);
    if(dcnet != NULL) delete dcnet;
    dcnet = new DcNet(red);
}
        
void Driver::Conectar(const Computadora& c1, const Interfaz& i1, const Computadora& c2, const Interfaz& i2) {
    red->Conectar(c1, c2, i1, i2);
    if(dcnet != NULL) delete dcnet;
    dcnet = new DcNet(red);
}
	
// TAD DCNET	
Nat Driver::CantidadNodosRecorridosPor(const Paquete& p) const {
    PaqueteN pn = paq2paqN->Obtener(p);
    Lista<Computadora> camino = dcnet->CaminoRecorrido(pn);
    return camino.Longitud();
}

const Computadora& Driver::IesimoNodoRecorridoPor(const Paquete& p, const Nat i) const {
    PaqueteN pn = paq2paqN->Obtener(p);
    Lista<Computadora> camino = dcnet->CaminoRecorrido(pn);
    return camino[i];
}

Nat Driver::CantidadEnviadosPor(const Computadora& c) const {
    return dcnet->CantidadEnviados(c);
}
	
Nat Driver::CantidadEnEsperaEn(const Computadora& c) const {
    return dcnet->EnEspera(c).Cardinal();
}

Paquete Driver::IesimoEnEsperaEn(const Computadora& c, const Nat i) const { 
    Lista<PaqueteN> lp = dcnet->EnEspera(c).Enlistar();
    
    Lista<PaqueteN>::Iterador it = lp.CrearIt();
    
    Nat j = i;

    while(it.HaySiguiente()){
      if(j == 0) return it.Siguiente().id;
      else j--;
      it.Avanzar();
    }
    
}

void Driver::CrearPaquete(const Computadora& origen, const Computadora& destino, Nat prioridad) {
    PaqueteN paq(proxPaq, prioridad, origen, destino);
    dcnet->CrearPaquete(paq);
    paq2paqN->Definir(proxPaq, paq);
    proxPaq++;
}
		
void Driver::AvanzarSegundo() {
    dcnet->AvanzarSegundo();
}
		
const Computadora& Driver::laQueMasEnvio() const {
    return dcnet->LaQueMasEnvio();
}

const Computadora& Driver::origen(const Paquete& p) const {
    const PaqueteN& pn = paq2paqN->Obtener(p);
    return pn.origen;
} 

const Computadora& Driver::destino(const Paquete& p) const { 
    const PaqueteN& pn = paq2paqN->Obtener(p);
    return pn.destino;
}

Nat Driver::prioridad(const Paquete& p) const { 
    const PaqueteN& pn = paq2paqN->Obtener(p);
    return pn.prioridad;
}
		


} // namespace aed2

