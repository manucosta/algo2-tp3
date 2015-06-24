#ifndef DICCAVL_H
#define DICCAVL_H

#include "aed2.h"
#include <iostream>

using namespace std;

template<class K, class S>
class DiccAvl {
public:


private:
		struct node
	{
		K clave;
		S significado;
		int altura;
		node* izq;
		node* der;
		node(K clav, S signif):significado(signif), clave(clav), izq(NULL),der(NULL),altura(1){}
	};

	int max(int a, int b)
	{
		
		return (a>b)?a:b;
	}

	void actualizarAltura(node* p)
	{
		if (p != NULL)
		{
			p->altura = 1 + max((p->izq)->altura,(p->der)->altura);	
		}
	}

	int altura(node* p)
	{
		if (p != NULL)
		{
			return 1 + max(altura(p->izq),altura(p->der));	
		}
		return 0;
	}

	void rotarSimple(node** a, bool rota_izq)
	{
			node* a1;
			if (rota_izq)
			{
			a1 = (*a)->izq;
			((*a)->izq)= a1->der;
			(a1->der)= *a;
			}
			else
			{
			a1 = (*a)->der;
			(*a)->der = a1->izq;
			a1->izq = *a;
			}
			actualizarAltura(*a);
			actualizarAltura(a1);
			*a = a1;
	}

	void rotarDoble(node** a, bool rota_izq)
	{
		if (rota_izq)
		{
		rotarSimple(&((*a)->izq),false);
		rotarSimple(a,true);
		}
		else
		{
		rotarSimple(&((*a)->der),true);
		rotarSimple(a,false);
		}
	}

	void balancear(node** a)
	{
			if(*a!=NULL)
			{
				if (((*a)->izq)->altura>=((*a)->der)->altura)
				{
					if((((((*a)->izq)->altura))-(((*a)->der)->altura)) == 2)
					{
				
							if ((((*a)->izq)->izq)->altura >= (((*a)->izq)->der)->altura)
								{
								rotarSimple(a,true);
								}
							else
								{
								rotarDoble(a, true);
								}
					}
				
				}
				else
				{
					if ((((*a)->der)->altura-((*a)->izq)->altura) == 2)
						{
						if ((((*a)->der)->der)->altura >= (((*a)->der)->izq)->altura)  // Capaz es chamuyo.
							rotarSimple(a, false);
						}	
						else
						{
							rotarDoble(a, false);
						}
						
				}
			}
	}
}
