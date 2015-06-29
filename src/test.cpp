#include <iostream>
#include <assert.h>
#include "ColaPrior.h"
#include "DiccAvl.h"
#include "ConjAVL.h"
#include "red.h"
#include "../mini_test.h"

using namespace std;

/**Pego esto acá temporalmente para popder probar un par de cosas**/
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

  Paquete p1 = Paquete(1,10, "Pc1", "Pc2");
  Paquete p2 = Paquete(2,20, "Pc1", "Pc2");
  Paquete p3 = Paquete(3,5, "Pc1", "Pc2");
  Paquete p4 = Paquete(4,15, "Pc1", "Pc2");
  Paquete p5 = Paquete(5,10, "Pc1", "Pc2");
/******************************************************************/

orden comp_int(const int a, const int b){
  if(a<b) return LT;
  else if(a==b) return EQ;
  else return GT;
}


orden comp_nat(const Nat a, const Nat b){
  if(a<b) return LT;
  else if(a==b) return EQ;
  else return GT;
}

void colaprior1() {
	ColaPrior<Nat> c(comp_nat);
	c.Encolar(100);
	c.Encolar(20);
	c.Encolar(20);
	c.Encolar(30);
	c.Encolar(50);
  c.Encolar(0);
	c.Encolar(20);
	c.Encolar(6);
	c.Encolar(30);
	
	Nat a;

	a = c.Desencolar();
	ASSERT_EQ(a, 0);
	a = c.Desencolar();
	ASSERT_EQ(a, 6);
	a = c.Desencolar();
	ASSERT_EQ(a, 20);
	a = c.Desencolar();
	ASSERT_EQ(a, 20);
	a = c.Desencolar();
	ASSERT_EQ(a, 20);
	a = c.Desencolar();
	ASSERT_EQ(a, 30);
	a = c.Desencolar();
	ASSERT_EQ(a, 30);
	a = c.Desencolar();
	ASSERT_EQ(a, 50);	
	a = c.Desencolar();
	ASSERT_EQ(a, 100);
}

void colaprior2() {
  ColaPrior<Paquete> c(ComparPrioridad);
  c.Encolar(p1);
  c.Encolar(p2);
  c.Encolar(p3);
  c.Encolar(p4);
  c.Encolar(p5);
  
  Paquete p;

  p = c.Desencolar();
  ASSERT_EQ(p == p3, true);
  p = c.Desencolar();
  ASSERT_EQ(p == p1 || p == p5, true);
  p = c.Desencolar();
  ASSERT_EQ(p == p1 || p == p5, true);
  p = c.Desencolar();
  ASSERT_EQ(p == p4, true);
  p = c.Desencolar();
  ASSERT_EQ(p == p2, true);
}


void diccavl1(){
  DiccLog<int, int> dicc(&comp_int);

  ASSERT_EQ(dicc.Definido(1), false); 
  ASSERT_EQ(dicc.Definido(2), false);
  ASSERT_EQ(dicc.Definido(3), false);
  ASSERT_EQ(dicc.Definido(4), false);
  ASSERT_EQ(dicc.Definido(5), false); 
  dicc.Definir(1,1);
  dicc.Definir(2,11); 
  dicc.Definir(3,123);
  dicc.Definir(4,10);
  dicc.Definir(5,7);
  ASSERT_EQ(dicc.Definido(1), true);
  ASSERT_EQ(dicc.Definido(2), true);
  ASSERT_EQ(dicc.Definido(3), true);
  ASSERT_EQ(dicc.Definido(4), true);
  ASSERT_EQ(dicc.Definido(5), true);

  ASSERT_EQ(dicc.Obtener(4), 10);

  dicc.Borrar(4);
  ASSERT_EQ(dicc.Definido(4), false);
  dicc.Definir(4,4);
  ASSERT_EQ(dicc.Definido(4), true);

  ASSERT_EQ(dicc.Obtener(4), 4);
}

void diccavl2(){
  DiccLog<Paquete, int> dicc(&ComparId);

  ASSERT_EQ(dicc.Definido(p1), false); 
  ASSERT_EQ(dicc.Definido(p2), false);
  ASSERT_EQ(dicc.Definido(p3), false);
  ASSERT_EQ(dicc.Definido(p4), false);
  ASSERT_EQ(dicc.Definido(p5), false); 
  dicc.Definir(p5,7);
  dicc.Definir(p1,1);
  dicc.Definir(p3,123);
  dicc.Definir(p2,11); 
  dicc.Definir(p4,10);
  ASSERT_EQ(dicc.Definido(p1), true);
  ASSERT_EQ(dicc.Definido(p2), true);
  ASSERT_EQ(dicc.Definido(p3), true);
  ASSERT_EQ(dicc.Definido(p4), true);
  ASSERT_EQ(dicc.Definido(p5), true);

  ASSERT_EQ(dicc.Obtener(p4), 10);

  dicc.Borrar(p4);
  ASSERT_EQ(dicc.Definido(p4), false);
  dicc.Definir(p4,4);
  ASSERT_EQ(dicc.Definido(p4), true);

  ASSERT_EQ(dicc.Obtener(p4), 4);
}

void conjavl1(){
  ConjLog<int> conj(&comp_int);

  for(int i = 0; i<1000; i++){
    ASSERT_EQ(conj.Pertenece(i*i), false);
  }


  for(int i = 0; i<1000; i++){
    if(i%3 == 0){
      conj.Agregar(i*i);
    }else{
      conj.Agregar(-i*i);
    }
  }

  for(int i = 0; i<1000; i++){
    if(i%3 == 0){
      ASSERT_EQ(conj.Pertenece(i*i), true);
    }else{
      ASSERT_EQ(conj.Pertenece(-i*i), true);
    }
  }


  for(int i = 0; i<1000; i += 2){
    if(i%3 == 0){
      conj.Eliminar(i*i);
    }else{
      conj.Eliminar(-i*i);
    }
  }

  for(int i = 0; i<1000; i++){
    if(i % 2 == 0){
      ASSERT_EQ(conj.Pertenece(i*i) || conj.Pertenece(-i*i), false);
    }else{
      ASSERT_EQ(conj.Pertenece(i*i) || conj.Pertenece(-i*i), true);
    }
  } 
}

void conjavl2(){
  ConjLog<Paquete> conj(&ComparId);
  Nat tam = 1000;
  Arreglo<Paquete> a(tam);
  for(int i = 0; i < 1000; i++){
    Paquete p = Paquete(i, i%5, "pc1", "pc2");
    a.Definir(i, p);
  }

  for(int i = 0; i<1000; i++){
    ASSERT_EQ(conj.Pertenece(a[i]), false);
  }


  for(int i = 0; i<1000; i++){
    conj.Agregar(a[i]);
  }

  for(int i = 0; i<1000; i++){
    conj.Pertenece(a[i]);
  }


  for(int i = 0; i<1000; i += 2){
    conj.Eliminar(a[i]);
  }

  for(int i = 0; i<1000; i++){
    if(i % 2 == 0){
      ASSERT_EQ(conj.Pertenece(a[i]), false);
    }else{
      ASSERT_EQ(conj.Pertenece(a[i]), true);
    }
  } 
}

void red(){
	Red r;
	Compu com1 = "compu1", com2 = "compu2", com3 = "compu3";
	Conj<Interfaz> c1, c2, c3;
	c1.Agregar(1);
	c2.Agregar(1);
	r.AgregarComputadora(com1,c1);
	r.AgregarComputadora(com2,c2);	
	r.AgregarComputadora(com3,c3);
	r.Conectar(com1,com2,1,1);
	ASSERT_EQ(r.Conectadas(com1,com2), true);
	ASSERT_EQ(r.Conectadas(com1,com3), false);
}

class X{
  public:
    X(){
      x = 0;
      y = NULL;
    }

    bool operator==(const X x1){ return true;}
    bool operator!=(const X x1){ return false;}
  private:
    int x;
    int * y;
};


int main() {
/*
  RUN_TEST(colaprior1);
  RUN_TEST(colaprior2);
  RUN_TEST(diccavl1);
  RUN_TEST(diccavl2);
  RUN_TEST(conjavl1);
<<<<<<< HEAD
  RUN_TEST(red);
*/
  DiccString<int> dicc;
  //dicc.claves();

  RUN_TEST(conjavl2);
  //RUN_TEST(red);



  return 0;
}
