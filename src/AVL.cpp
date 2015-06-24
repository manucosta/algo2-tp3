#include <iostream>
using namespace std;

template<class BETA>
template<class ALFA>

struct node
{
    ALFA clave;
    BETA significado;
    int altura;
    node* izq;
    node* der;
    node(int k) { clave = k; izq = der = 0; altura = 1; }
};

int max(int a, int b){
	
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

int main(){
	node b = node(4);
	node* a = &b;
//	node** c = &a;
//	balancear(c);
	cout << altura(a)  << endl;
}


