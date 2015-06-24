#include <iostream>
#include <assert.h>
#include "ColaPrior.h"
#include "aed2.h"
#include "../mini_test.h"

using namespace std;

void check1() {
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

void check2() {
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

int main() {

  RUN_TEST(check1);
  RUN_TEST(check2);


  return 0;
}
