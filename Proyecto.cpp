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

//-----------Constructores-----------------------------------------
nodoNumero*crearNodoNumero(int num){
	nodoNumero*aux=new(struct nodoNumero);
	aux->num=num;
	aux->siguiente=NULL;
	return aux;
}

nodoMarcoPagina*crearNodoMarcoPagina(int idMarco, double memTotal, bool enUso){
	nodoMarcoPagina*aux=new (struct nodoMarcoPagina);
	aux->idMarco=idMarco;
	aux->memTotal=memTotal;
	aux->enUso=enUso;
	aux->siguiente=NULL;
	return aux;

}

nodoUsoMarco*crearNodoUsoMarco(int idMarco,int idProceso,int paginaProceso,double memoriaUsada){
	nodoUsoMarco*aux=new(struct nodoUsoMarco);
	aux->idMarco=idMarco;
	aux->idProceso=idProceso;
	aux->paginaProceso=paginaProceso;
	aux->memoriaUsada=memoriaUsada;
	aux->siguiente=NULL;
	return aux;

}

nodoPaginaProceso*crearNodoPaginaProceso(int idPagina,int idProceso,double memoria,bool enUso,bool enEspera){
	nodoPaginaProceso*aux=new(struct nodoPaginaProceso);
	aux->idPagina=idPagina;
	aux->idProceso=idProceso;
	aux->memoria=memoria;
	aux->enUso=enUso;
	aux->enEspera=enEspera;
	aux->siguiente=NULL;
	return aux;

}

nodoProceso*crearNodoProceso(int idProceso,string nombre,double memTotal){
	nodoProceso*aux=new(struct nodoProceso);
	aux->idProceso=idProceso;
	aux->nombre=nombre;
	aux->memTotal=memTotal;
	aux->paginas=NULL;
	aux->siguiente=NULL;
	return aux;
}

 nodoSwap*crearNodoSwap(double memoriaUsada, int idProceso, int paginaProceso){
	nodoSwap*aux=new(struct nodoSwap);
	aux->memoriaUsada=memoriaUsada;
	aux->idProceso=idProceso;
	aux->paginaProceso=paginaProceso;
	aux->siguiente=NULL;
	return aux;
}

	nodoPagTabla*crearNodoPagTabla(int numPagina,int marcoUbicacion){
		nodoPagTabla*aux=new(struct nodoPagTabla);
		aux->numPagina=numPagina;
		aux->marcoUbicacion=marcoUbicacion;
		aux->siguiente=NULL;
		return aux;
	}

	nodoTablaPag*crearNodoTablaPag(int idProceso){
		nodoTablaPag*aux=new(struct nodoTablaPag);
		aux->idProceso=idProceso;
		aux->paginasTablaPag=NULL;
		aux->siguiente=NULL;
		return aux;
	}






//------------Metodos---------------------------------------------
