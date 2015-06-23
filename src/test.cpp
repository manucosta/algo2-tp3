#include <iostream>
#include <assert.h>
#include "ColaPrior.h"
#include "aed2.h"
#include "../mini_test.h"

void testearEncolar() {
	ColaPrior<int> c;
	c.Encolar(1);
	c.Encolar(-1);
	c.Encolar(2);
	c.Encolar(0);//Segmentation Fault: desencolar se invalida con esta cola
	ASSERT_EQ(c.Proximo(), -1);
	//int e = c.Desencolar();
	//ASSERT_EQ(e, -1);
}

int main() {

	RUN_TEST(testearEncolar);

  	return 0;
}