#include "Driver.h"
#include "mini_test.h"

#include <string>
#include <iostream>

using namespace aed2;

/** 
 * Imprime un elemento a un string, en vez de a una pantalla, 
 * a través del operador << 
 */
template <typename T>
std::string to_str(const T& t)
{
	std::stringstream ss;
	ss << t;

	return ss.str();
}

/**
 * Esta función se puede utilizar para comparar dos colecciones
 * iterables que representen conjuntos, es decir, que no tengan 
 * elementos repetidos.
 */
template<typename T, typename S>
bool Comparar(const T& t, const S& s)
{
  typename T::const_Iterador it1 = t.CrearIt();
  typename S::const_Iterador it2 = s.CrearIt();

	// me fijo si tienen el mismo tamanho

	Nat len1 = 0;
	while( it1.HaySiguiente() ) {
		len1++;
		it1.Avanzar();
	}

	Nat len2 = 0;
	while( it2.HaySiguiente() ) {
		len2++;
		it2.Avanzar();
	}

	if ( len1 != len2 )
		return false;

	it1 = t.CrearIt();
	it2 = s.CrearIt();

	// me fijo que tengan los mismos elementos

	while( it1.HaySiguiente() )
	{
		bool esta = false;
		it2 = s.CrearIt();

		while( it2.HaySiguiente() ) {
		  if ( it1.Siguiente() == it2.Siguiente() ) {
			esta = true;
			break;
		  }
		  it2.Avanzar();
		}

		if ( !esta ) {
			return false;
		}
			
		it1.Avanzar();
	}
  
  return true;
}


// ---------------------------------------------------------------------

/**
 * Ejemplo de caso de test, con llamadas a las rutinas de aserción 
 * definidas en mini_test.h
 */
 
void test_dcnet_ejemplo() {
	Conj<Interfaz> conjIc1;
	Conj<Interfaz> conjIc2;
	Conj<Interfaz> conjIc3;
	
	conjIc1.Agregar(1);
	conjIc1.Agregar(2);
	conjIc1.Agregar(3);
	
	conjIc2.Agregar(1);
	conjIc2.Agregar(2);
	conjIc2.Agregar(3);
	
	conjIc3.Agregar(1);
	conjIc3.Agregar(2);
	
	Computadora c1 = "dc.uba.ar";
	Computadora c2 = "uba.ar";
	Computadora c3 = "dm.uba.ar";

	Driver dcnet;

	dcnet.AgregarComputadora(c1, conjIc1);
	dcnet.AgregarComputadora(c2, conjIc2);
	dcnet.AgregarComputadora(c3, conjIc3);
	
	// ejemplo - Indexado en 0 
	Interfaz i1 = dcnet.IesimaInterfazDe(c1, 0); 
	Interfaz i2 = dcnet.IesimaInterfazDe(c2, 2);

	dcnet.Conectar(c1, i1, c2, i2);
	dcnet.CrearPaquete(c1, c2, 3);

	ASSERT_EQ(dcnet.prioridad(dcnet.IesimoEnEsperaEn(c1, 0)), 3);

	dcnet.AvanzarSegundo();

	ASSERT_EQ(dcnet.laQueMasEnvio(), c1);		
}


void test_dcnet_nuestro_1() {
	Conj<Interfaz> conjIc1;
	Conj<Interfaz> conjIc2;
	Conj<Interfaz> conjIc3;
	Conj<Interfaz> conjIc4;
	
	conjIc1.Agregar(1);
	conjIc1.Agregar(2);
	
	conjIc2.Agregar(1);
	conjIc2.Agregar(2);
	
	conjIc3.Agregar(1);
	conjIc3.Agregar(2);


	conjIc4.Agregar(1);
	conjIc4.Agregar(2);

	
	Computadora c1 = "dc.uba.ar";
	Computadora c2 = "uba.ar";
	Computadora c3 = "dm.uba.ar";
	Computadora c4 = "df.uba.ar";

	Driver dcnet;

	dcnet.AgregarComputadora(c1, conjIc1);
	dcnet.AgregarComputadora(c2, conjIc2);
	dcnet.AgregarComputadora(c3, conjIc3);
	dcnet.AgregarComputadora(c4, conjIc4);
	
	// ejemplo - Indexado en 0 
	dcnet.Conectar(c1, dcnet.IesimaInterfazDe(c1, 0), c2, dcnet.IesimaInterfazDe(c2, 0));
	dcnet.Conectar(c2, dcnet.IesimaInterfazDe(c2, 1), c3, dcnet.IesimaInterfazDe(c3, 0));
	dcnet.Conectar(c3, dcnet.IesimaInterfazDe(c3, 1), c4, dcnet.IesimaInterfazDe(c4, 0));

	dcnet.CrearPaquete(c1, c4, 3);

	ASSERT_EQ(dcnet.prioridad(dcnet.IesimoEnEsperaEn(c1, 0)), 3);	
  dcnet.AvanzarSegundo();
	ASSERT_EQ(dcnet.prioridad(dcnet.IesimoEnEsperaEn(c2, 0)), 3);	
  dcnet.AvanzarSegundo();
	ASSERT_EQ(dcnet.prioridad(dcnet.IesimoEnEsperaEn(c3, 0)), 3);	
  dcnet.AvanzarSegundo();
}


void test_dcnet_nuestro_2() {
	Conj<Interfaz> conjIc1;
	Conj<Interfaz> conjIc2;
	Conj<Interfaz> conjIc3;
	Conj<Interfaz> conjIc4;
	
	conjIc1.Agregar(1);
	conjIc1.Agregar(2);
	
	conjIc2.Agregar(1);
	conjIc2.Agregar(2);
	
	conjIc3.Agregar(1);
	conjIc3.Agregar(2);


	conjIc4.Agregar(1);
	conjIc4.Agregar(2);

	
	Computadora c1 = "dc.uba.ar";
	Computadora c2 = "uba.ar";
	Computadora c3 = "dm.uba.ar";
	Computadora c4 = "df.uba.ar";

	Driver dcnet;

	dcnet.AgregarComputadora(c1, conjIc1);
	dcnet.AgregarComputadora(c2, conjIc2);
	dcnet.AgregarComputadora(c3, conjIc3);
	dcnet.AgregarComputadora(c4, conjIc4);
	
	// ejemplo - Indexado en 0 
	dcnet.Conectar(c1, dcnet.IesimaInterfazDe(c1, 0), c2, dcnet.IesimaInterfazDe(c2, 0));
	dcnet.Conectar(c2, dcnet.IesimaInterfazDe(c2, 1), c3, dcnet.IesimaInterfazDe(c3, 0));
	dcnet.Conectar(c3, dcnet.IesimaInterfazDe(c3, 1), c4, dcnet.IesimaInterfazDe(c4, 0));

	dcnet.CrearPaquete(c1, c4, 1);
	dcnet.CrearPaquete(c1, c4, 5);

	ASSERT_EQ(dcnet.prioridad(dcnet.IesimoEnEsperaEn(c1, 0)), 1);	
	ASSERT_EQ(dcnet.prioridad(dcnet.IesimoEnEsperaEn(c1, 1)), 5);	
  dcnet.AvanzarSegundo();
	ASSERT_EQ(dcnet.prioridad(dcnet.IesimoEnEsperaEn(c2, 0)), 1);	
	ASSERT_EQ(dcnet.prioridad(dcnet.IesimoEnEsperaEn(c1, 0)), 5);	
  dcnet.AvanzarSegundo();
	ASSERT_EQ(dcnet.prioridad(dcnet.IesimoEnEsperaEn(c3, 0)), 1);	
	ASSERT_EQ(dcnet.prioridad(dcnet.IesimoEnEsperaEn(c2, 0)), 5);	
  dcnet.AvanzarSegundo();
	ASSERT_EQ(dcnet.prioridad(dcnet.IesimoEnEsperaEn(c4, 0)), 1);	
	ASSERT_EQ(dcnet.prioridad(dcnet.IesimoEnEsperaEn(c3, 0)), 5);	
}



int main(int argc, char **argv)
{
    RUN_TEST(test_dcnet_ejemplo);
    RUN_TEST(test_dcnet_nuestro_1);
    RUN_TEST(test_dcnet_nuestro_2);
	 
  // valgrind --leak-check=full --show-leak-kinds=all ./test
 
  
  
	return 0;
}
