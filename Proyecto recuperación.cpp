#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <string>
#include <string.h>

using namespace std;

struct Nodo
{
	int carnet;
	string nombre;
	string semestre;
	string carrera;
	Nodo *der;
	Nodo *izq;
	Nodo *padre;
};

void menu();
Nodo *crear(int,string,string,string, Nodo *);
void insertar(Nodo *&,int,string,string,string, Nodo *);
void postOrden(Nodo *);
void preOrden(Nodo *);
void inOrden(Nodo *);
void eliminar(Nodo *, int);
void eliminarN(Nodo *);
Nodo *minimo(Nodo *);
void reemplazar(Nodo *, Nodo *);
void dNodo(Nodo *);

Nodo *arbol = NULL;

int main()
{
	menu();
	getch();
	return 0;
}

//Menu
void menu()
{
	int carnet, op, contador=0;
	string nombre, semestre, carrera;
	
	do
	{
		cout<<"\t----:MENU:----"<<endl;
		cout<<"1. Insertar Nodo"<<endl;
		cout<<"2. Mostrar recorrido Arbol PostOrden"<<endl;
		cout<<"3. Mostrar recorrido Arbol PreOrden"<<endl;
		cout<<"4. Mostrar recorrido Arbol InOrden"<<endl;
		cout<<"5. Eliminar Nodo"<<endl;
		cout<<"6. Salir"<<endl;
		cout<<"Opcion: ";
		cin>>op;
		
		switch(op)
		{
			case 1: cout<<"\nCarnet: ";
					cin>>carnet;
					cout<<"Nombre: ";
					cin>>nombre;
					cout<<"Semestre: ";
					cin>>semestre;
					cout<<"Carrera: ";
					cin>>carrera;
					//Inserta Nodo Nuevo
					insertar(arbol,carnet,nombre,semestre,carrera, NULL);
					cout<<"\n";
					system("pause");
					break;
			case 2: cout<<"\nRecorrido en PostOrden: ";
					postOrden(arbol);
					cout<<"\n\n";
					system("pause");
					break;
			case 3: cout<<"\nRecorrido en PreOrden: ";
					preOrden(arbol);
					cout<<"\n\n";
					system("pause");
					break;	
			case 4: cout<<"\nRecorrido en InOrden: ";
					inOrden(arbol);
					cout<<"\n\n";
					system("pause");
					break;			
			case 5: cout<<"\nDigite el Carnet para eliminar: ";
					cin>>carnet;
					eliminar(arbol,carnet);
					cout<<"\n";
					system("pause");
					break;		
		}
		system("cls");
	}while(op != 6);
}

//Funcion Crear
Nodo *crear(int c,string n, string s, string ca, Nodo *padre)
{
	Nodo *nuevo = new Nodo();
	nuevo->carnet = c;
	nuevo->nombre = n;
	nuevo->semestre = s;
	nuevo->carrera = ca;
	nuevo->der = NULL;
	nuevo->izq = NULL;
	nuevo->padre = padre;
	
	return nuevo;
}

//Funcion Insertar
void insertar(Nodo *&arbol,int c,string n, string s, string ca, Nodo *padre)
{
	//Si el arbol esta vacio
	if(arbol == NULL)
	{
		Nodo *nuevo = crear(c,n,s,ca, padre);
		arbol = nuevo;
	//Si el arbol tiene 1 o mas nodos
	}
	else
	{
		//Obtener el valor de raiz
		int raiz = arbol->carnet;
		//Si el elemento es menor a la raiz, inserta izq
		if(c < raiz)
		{
			insertar(arbol->izq,c,n,s,ca,padre);
		}
		//Si el elemento es mayor a la raiz, inserta der
		else
		{
			insertar(arbol->der,c,n,s,ca,padre);
		}
	}
}

//funcion de recorrido PostOrden
void postOrden(Nodo *arbol)
{
	if(arbol == NULL)
	{
		return;
	}
	else
	{
		postOrden(arbol->izq);
		postOrden(arbol->der);
		cout<<"{"<<arbol->carnet<<" - "<<arbol->nombre<<"} - ";
	}
}

//funcion de recorrido PreOrden
void preOrden(Nodo *arbol)
{
	if (arbol == NULL)
	{
		return;
	}
	else
	{
		cout<<"{"<<arbol->carnet<<" - "<<arbol->nombre<<"} - ";
		preOrden(arbol->izq);
		preOrden(arbol->der);
	}
}

//funcion recorrido InOrden
void inOrden(Nodo *arbol)
{
	if (arbol == NULL)
	{
		return;
	}
	else
	{
		inOrden(arbol->izq);
		cout<<"{"<<arbol->carnet<<" - "<<arbol->nombre<<"} - ";
		inOrden(arbol->der);
		
	}
}

//Funcion eliminar
void eliminar(Nodo *arbol, int c)
{
	if(arbol == NULL)
	{
		return;
	}
	else if(c < arbol->carnet)
	{
		eliminar(arbol->izq,c);
	}
	else if(c > arbol->carnet)
	{
		eliminar(arbol->der,c);
	}
	else
	{
	    eliminarN(arbol);
	}
}

//Funcion Nodo + izq
Nodo *minimo(Nodo *arbol)
{
	if(arbol == NULL)
	{
		return NULL;
	}
	if(arbol->izq)
	{
		return minimo(arbol->izq);
	}
	else
	{
		return arbol;
	}
}

//Funcion reemplazar 2 nodos
void reemplazar(Nodo *arbol, Nodo *nuevo)
{
	if(arbol->padre)
	{
		if(arbol->carnet == arbol->padre->izq->carnet)
		{
			arbol->padre->izq = nuevo;
		}
		else if(arbol->carnet == arbol->padre->der->carnet)
		{
			arbol->padre->der = nuevo;
		}
	}
	if(nuevo)
	{
		nuevo->padre = arbol->padre;
	}
}

//Funcion destruir un nodo
void dNodo(Nodo *nodo)
{
	nodo->izq=NULL;
	nodo->der=NULL;
	
	delete nodo;
}

//Funcion eliminar nodo encontrado
void eliminarN(Nodo *nodoE)
{
	if(nodoE->izq && nodoE->der)
	{
		Nodo *menor = minimo(nodoE->der);
		nodoE->carnet = menor->carnet;
		eliminarN(menor);
	}
	else if(nodoE->izq)
	{
		reemplazar(nodoE, nodoE->izq);
		dNodo(nodoE);
	}
	else if(nodoE->der)
	{
		reemplazar(nodoE, nodoE->der);
		dNodo(nodoE);
	}
	else
	{
		reemplazar(nodoE, NULL);
		dNodo(nodoE);
	}
}
