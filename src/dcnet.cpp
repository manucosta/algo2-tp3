#include "dcnet.h"

/****Implementación de comparaciones para PaqueteN****/
orden ComparIdx(const PaqueteN p1, const PaqueteN p2){
  if(p1.id < p2.id){
    return LT;
  }else if(p1.id == p2.id){
    return EQ;
  }else{
    return GT;
  }
}

orden ComparPrioridadx(const PaqueteN p1, const PaqueteN p2){
  if(p1.prioridad < p2.prioridad){
    return LT;
  }else if(p1.prioridad == p2.prioridad){
    return EQ;
  }else{
    return GT;
  }
}

/****Implementación de operaciones de DcNet****/

DcNet::~DcNet(){ 

	DiccString<InfoPaquetes>::Iterador it(&paquetes);
  do{
    InfoPaquetes * info = it.valorActual();
    delete info->cola;
    info->cola = NULL;
    delete info->diccPaqCamino;
    info->diccPaqCamino = NULL;
    delete info->conjPaquetes;
    info->conjPaquetes = NULL;
  }while(it.avanzar());
}

DcNet::DcNet(Red * r){
  red = r;
  caminosRecorridos = Lista<Lista<Compu> >();
  Conj<Compu> compus = red->Computadoras();
  Conj<Compu>::Iterador it = compus.CrearIt();
  laQueMasEnvio.cuantosEnvio = 0;
  laQueMasEnvio.cualCompu = it.Siguiente();
  //DiccString<DiccString<Compu> >proximaEnCamino;
  
  while(it.HaySiguiente()) {
      DiccString<Compu> diccActual;
      
      InfoPaquetes tupInfoPaquetes; 
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
            siguiente = caminoMinimo.Primero();
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
  paquetesAEnv(PaqueteN px, Lista<Lista<Compu> > ::Iterador itx) : p(px), it(itx) {}

  PaqueteN p;
  Lista<Lista<Compu> >::Iterador it;
};

void DcNet::CrearPaquete(PaqueteN paq){
  if(paq.origen != paq.destino){ 
    Lista<Compu> nuevoCaminoRecorrido;
    nuevoCaminoRecorrido.AgregarAtras(paq.origen);

    Lista<Lista<Compu> >::Iterador it = caminosRecorridos.AgregarAtras(nuevoCaminoRecorrido);

    InfoPaquetes * losPaquetes = paquetes.obtener(paq.origen);


    losPaquetes->cola->Encolar(paq);
    losPaquetes->conjPaquetes->Agregar(paq);
    losPaquetes->diccPaqCamino->Definir(paq, it);
  }
}



void DcNet::AvanzarSegundo(){
	Lista<struct paquetesAEnv> paquetesAEnviar;
	DiccString<InfoPaquetes>::Iterador it(&paquetes);
	//se rompe si dicc es vacio,deberiamos hacer el assert
	do{
		InfoPaquetes * s = it.valorActual();	
		if(!s->cola->Vacia()){
			PaqueteN estePaquete = s->cola->Desencolar();
      s->conjPaquetes->Eliminar(estePaquete);
      
      struct paquetesAEnv x(estePaquete, s->diccPaqCamino->Obtener(estePaquete));
      paquetesAEnviar.AgregarAtras(x);

      s->diccPaqCamino->Borrar(estePaquete);
      s->cantidadEnviados++; 

      if(s->cantidadEnviados > laQueMasEnvio.cuantosEnvio){
        laQueMasEnvio.cuantosEnvio = s->cantidadEnviados;
        laQueMasEnvio.cualCompu = x.it.Siguiente().Ultimo();
      }
		}
	}while(it.avanzar()); 

	Lista<struct paquetesAEnv>::Iterador it2 = paquetesAEnviar.CrearIt();
  	while(it2.HaySiguiente()){
	    struct paquetesAEnv p = it2.Siguiente(); 
	    DiccString<Compu> * proximasCompus = proximaEnCamino.obtener(p.it.Siguiente().Ultimo());
	    Compu proximaCompu = *(proximasCompus->obtener(p.p.destino));

	    if(proximaCompu != p.p.destino){ //esto estaba mal en el tp
	        InfoPaquetes * paquetesDeProximaCompu = paquetes.obtener(proximaCompu);
		    p.it.Siguiente().AgregarAtras(proximaCompu);
	    	paquetesDeProximaCompu->cola->Encolar(p.p);
	    	paquetesDeProximaCompu->conjPaquetes->Agregar(p.p);
	     	paquetesDeProximaCompu->diccPaqCamino->Definir(p.p, p.it);
    }
    it2.Avanzar();
  }
}

Red& DcNet::ObtenerRed() const{//La red que se devuelve es const
  return *red;
}

const Lista<Compu>& DcNet::CaminoRecorrido(const PaqueteN& paq) const{
 /* dicc_trie esta mal hecho entonces no puede iterar diccionarios vacios */

  DiccString<InfoPaquetes>::Iterador it(const_cast<DiccString<DcNet::InfoPaquetes_t>*>(&paquetes)); //cosas raras del trie

  while(!(it.valorActual()->conjPaquetes->Pertenece(paq))){
    it.avanzar();
  }

  DiccLog<PaqueteN, Lista<Lista<Compu> >::Iterador> * d = it.valorActual()->diccPaqCamino;
  return d->Obtener(paq).Siguiente();
}

Nat DcNet::CantidadEnviados(const Compu& c){
  // no toma parametro const porque dicc_trie se rompe
  InfoPaquetes * info =  paquetes.obtener(c);
  return info->cantidadEnviados;
}

bool DcNet::PaqueteEnTransito(const PaqueteN& paq) const{
  DiccString<InfoPaquetes>::Iterador it(const_cast<DiccString<DcNet::InfoPaquetes_t>*>(&paquetes)); //lo mismo que antes, el trie no se banca cosas const

  //como el iterador del trie es cualquiera, esto puede fallar
 
  bool res = true;
  while(!(it.valorActual()->conjPaquetes->Pertenece(paq))){
    if(!it.avanzar()) {
      res = false; 
      break;
    }
  }
  return res;
}

const ConjLog<PaqueteN>& DcNet::EnEspera(const Compu& c){
  //hay que sacarle el const de this, si no dicc_trie explota
  InfoPaquetes * info = paquetes.obtener(c);
  return *(info->conjPaquetes);
}


const Compu& DcNet::LaQueMasEnvio() const{
  return laQueMasEnvio.cualCompu;
}
