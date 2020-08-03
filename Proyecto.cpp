#include <iostream>
#include <cstdlib>
#include <ctime> 
using namespace std;



// lista de las paginas que estan almacenadas en la memoria swap. Operada mediante FIFO

struct nodoSwap{
	double memoriaUsada;
	int idProceso;
	int paginaProceso;
	nodoSwap*siguiente;
};

typedef nodoSwap*listaSwap;

// Contiene la lista de tablas de paginacion de los procesos en ejecucion

 struct nodoPagTabla{
    int numPagina;
    int marcoUbicacion;
    nodoPagTabla*siguiente;
};


struct nodoTablaPag{
	int idProceso;
	nodoPagTabla*paginasTablaPag;
	nodoTablaPag*siguiente;
};

typedef nodoTablaPag*listaTablas;

// Contiene lista de procesos que el sistema puede abrir, asi como su paginacion, realizada de antemano al dividir la memoria requerida por este en bloques de 64MB

struct nodoPaginaProceso{
    bool enUso;
    bool enEspera;
    double memoria;
    int idPagina; 
    int idProceso;
    nodoPaginaProceso*siguiente;
};


struct nodoProceso{
	int idProceso;
	string nombre;
	double memTotal;
	nodoPaginaProceso*paginas;
	nodoProceso*siguiente;
};
typedef nodoProceso*listaProcesos;

// Cola operada mediante FIFO para detallar que pagina de que proceso esta usando cual marco de memoria

struct nodoUsoMarco{
	int idMarco;
	int idProceso;
	int paginaProceso;
	double memoriaUsada;
	nodoUsoMarco*siguiente;
};
typedef nodoUsoMarco*colaUso;

// Lista de los marcos en los que se divide la memoria fisica

struct nodoMarcoPagina{
	bool enUso;
	int idMarco;
	double memTotal;
	nodoMarcoPagina*siguiente;
};
typedef nodoMarcoPagina*listaMarcos;

// Cola de numeros

struct nodoNumero{
	int num;
	nodoNumero*siguiente;
};
typedef nodoNumero*colaNumeros;

//------------Metodos---------------------------------------------


