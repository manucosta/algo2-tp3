#include <iostream>
#include <assert.h>
#include "ColaPrior.h"
#include "DiccAvl.h"
#include "ConjAVL.h"
#include "red.h"
#include "aed2.h"
#include "../mini_test.h"

using namespace std;

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
  ColaPrior<int> cola(comp_int);

  for(int i = 1000; i >= 0; i--){
    cola.Encolar(i*i);
  }

  for(int i = 0; i < 1000; i++){
    ASSERT_EQ(cola.Desencolar(), i*i);
  }
}

void colaprior2() {
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



void conjavl1(){
  ConjLog<int> conj(&comp_int);

  for(int i = 0; i<1000; i++){
    ASSERT_EQ(conj.Pertenece(i*i), false);
  }


  for(int i = 0; i<1000; i++){
    conj.Agregar(i*i);
  }

  for(int i = 0; i<1000; i++){
    ASSERT_EQ(conj.Pertenece(i*i), true);
  }


  for(int i = 0; i<1000; i++){
    conj.Eliminar(i*i);
  }

  for(int i = 0; i<1000; i++){
    ASSERT_EQ(conj.Pertenece(i*i), false);
  }
} 

int main() {

  RUN_TEST(colaprior1);
  RUN_TEST(colaprior2);
  RUN_TEST(diccavl1);
  RUN_TEST(conjavl1);


  return 0;
}
