#include <iostream>
#include <assert.h>
#include "ColaPrior.h"
#include "DiccAvl.h"
#include "aed2.h"
#include "../mini_test.h"

using namespace std;

void colaprior1() {
	ColaPrior<int> c;
	c.Encolar(1);
	c.Encolar(-1);
	c.Encolar(2);
	c.Encolar(0);
	c.Encolar(100);
	c.Encolar(200);
	c.Encolar(200);
	c.Encolar(300);

	int a = c.Desencolar();
	int b = c.Desencolar();
	int d = c.Desencolar();
	int e = c.Desencolar();

	ASSERT_EQ(a, -1);
	ASSERT_EQ(b, 0);
	ASSERT_EQ(e, 2);
	ASSERT_EQ(d, 1);
}

void colaprior2() {
	ColaPrior<Nat> c;
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


orden comp_int(const int a, const int b){
  if(a<b) return LT;
  else if(a==b) return EQ;
  else return GT;
}

void avl1(){
  DiccLog<int, int> dicc(&comp_int);

  ASSERT_EQ(dicc.Definido(1), false); 
  ASSERT_EQ(dicc.Definido(2), false);
  ASSERT_EQ(dicc.Definido(3), false);
  ASSERT_EQ(dicc.Definido(4), false);
  ASSERT_EQ(dicc.Definido(5), false); 
  dicc.Definir(1,1);
  dicc.Definir(2,1); 
  dicc.Definir(3,1);
  dicc.Definir(4,1);
  dicc.Definir(5,1);
  ASSERT_EQ(dicc.Definido(1), true);
  ASSERT_EQ(dicc.Definido(2), true);
  ASSERT_EQ(dicc.Definido(3), true);
  ASSERT_EQ(dicc.Definido(4), true);
  ASSERT_EQ(dicc.Definido(5), true);


  dicc.Borrar(4);
  ASSERT_EQ(dicc.Definido(4), false);
  dicc.Definir(4,4);
  ASSERT_EQ(dicc.Definido(4), true);
} 

int main() {

  //RUN_TEST(colaprior1);
  //RUN_TEST(colaprior2);
  RUN_TEST(avl1);


  return 0;
}
