#include "Driver.h"
#include "ArbolSintactico.h"

namespace aed2 {

Driver::Driver() {
    Red red;
    dcnet = new DcNet(&red);
    proxPaq = 0;
    paq2paqN = new DiccLog<Paquete, PaqueteN>(comp_nat);
}

Driver::~Driver() {
    delete dcnet;
    dcnet = NULL;
}

// TAD RED
Nat Driver::CantidadComputadoras() const {
    return dcnet->ObtenerRed().Computadoras().Cardinal();
}

const Computadora& Driver::IesimaComputadora(const Nat i) const {//No entiendo la semántica
    // TODO
	return 0;
}
        
Nat Driver::CantidadInterfacesDe(const Computadora& c) const {
    return dcnet->ObtenerRed().Interfaces(c).Cardinal();
}

const Interfaz& Driver::IesimaInterfazDe(const Computadora& c, const Nat i) const{//No entiendo la semántica
    // TODO
    return 0;
} 

const Interfaz& Driver::IntefazUsada(const Computadora& c1, const Computadora& c2) const {
    return dcnet->ObtenerRed().InterfazUsada(c1, c2);
}


bool Driver::conectadas(const Computadora& c1, const Computadora& c2) const {
    return dcnet->ObtenerRed().Conectadas(c1, c2);
}

// TAD DCNET
void Driver::AgregarComputadora(const Computadora& ip, const Conj<Interfaz>& ci) {
    dcnet->ObtenerRed().AgregarComputadora(ip, ci);
}
        
void Driver::Conectar(const Computadora& c1, const Interfaz& i1, const Computadora& c2, const Interfaz& i2) {
    dcnet->ObtenerRed().Conectar(c1, c2, i1, i2);
}
	
	
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

const Paquete& Driver::IesimoEnEsperaEn(const Computadora& c, const Nat i) const {//No entiendo la semántica 
    return 0;                                                                     //(estimo que puede ser por la prioridad)
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
    PaqueteN pn = paq2paqN->Obtener(p);
    return pn.origen;
} 

const Computadora& Driver::destino(const Paquete& p) const { 
    PaqueteN pn = paq2paqN->Obtener(p);
    return pn.destino;
}

Nat Driver::prioridad(const Paquete& p) const { 
    PaqueteN pn = paq2paqN->Obtener(p);
    return pn.prioridad;
}
		


} // namespace aed2

