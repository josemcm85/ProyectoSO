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

//-----------colaNumeros-------------------

void ingresarColaNum(colaNumeros&cab,int num){
	nodoNumero*nuevo;
	colaNumeros aux;
	nuevo=crearNodoNumero(num);

		if(cab==NULL){

		cab=nuevo;

		}else{

		aux=cab;
		//Recorre la lista al revisar el puntero "siguiente"
		while(aux->siguiente!=NULL){
			aux=aux->siguiente;
		}

		//Una vez siguiente==NULL, significa que ha llegado al
		//final de la lista, así que coloca el nuevo como el
		//siguiente al último
		aux->siguiente=nuevo;

	}

}

colaNumeros sacarColaNum(colaNumeros cab){
//Saca el número en cabeza de cola


	colaNumeros aux;

	if (cab->siguiente==NULL){
		aux = cab;

		aux = NULL;
		cab = NULL;
		delete(aux);

	} else{
		aux = cab;
		cab = cab->siguiente;
		aux = NULL;
		delete(aux);

	}

	return cab;
}

bool numExiste(colaNumeros cab, int num){
	bool existe=false;
	colaNumeros aux;
	aux=cab;

	while(aux!=NULL){
		if(aux->num==num){
			existe=true;
		}

		aux=aux->siguiente;
	}

	return existe;
}

//------listaMarcos----------
void ingresarMarcoPagina(listaMarcos&cab,int idMarco, double memTotal, bool enUso){
	nodoMarcoPagina*nuevo;
	listaMarcos aux;
	nuevo=crearNodoMarcoPagina(idMarco,memTotal,enUso);

	if(cab==NULL)

	cab=nuevo;

	else{
		aux=cab;
		while(aux->siguiente!=NULL)
		aux=aux->siguiente;

		aux->siguiente=nuevo;
	}

}

void modificarMarcoPagina(listaMarcos&cab,int idMarco,bool enUso){
	listaMarcos aux;

	aux=cab;
	if(cab==NULL){

		cout<<"lista vacia";

	}else{

		while(aux!=NULL){

			if(idMarco==aux->idMarco){
				aux->enUso=enUso;
			}

			aux=aux->siguiente;
		}
	}
}

//------colaUso--------
void ingresarUsoMarco(colaUso&cab,int idMarco,int idProceso,int paginaProceso,double memoriaUsada){
	nodoUsoMarco*nuevo;
	colaUso aux;
	nuevo=crearNodoUsoMarco(idMarco,idProceso,paginaProceso,memoriaUsada);

	if(cab==NULL)
	cab=nuevo;
	else
	{
		aux=cab;
		while(aux->siguiente!=NULL)
		aux=aux->siguiente;

		aux->siguiente=nuevo;
	}


}

colaUso sacarUsoMarco(colaUso cab){
	//Saca la cabeza de colaUso
	colaUso aux;

	if (cab->siguiente == NULL) {
		aux = cab;


		aux = NULL;
		cab = NULL;
		delete(aux);
	}
	else {
		aux = cab;

		cab = cab->siguiente;
		aux = NULL;
		delete(aux);
	}

	return cab;

}

colaUso eliminarUsoMarco(colaUso cab, int idProceso){
	//Elimina coincidencias del proceso especificado
colaUso aux;
colaUso aux2;


	if(cab==NULL){
		cout<<"No hay marcos por liberar, todos estan disponibles"<<endl;

	}else{
		aux=cab;

		if(aux->idProceso==idProceso){

			cab=cab->siguiente;
			aux->siguiente=NULL;
			aux=NULL;
			free(aux);
		}else{

			while(aux->siguiente!=NULL){

				if(aux->siguiente->idProceso==idProceso){
					aux2=aux->siguiente;
					aux->siguiente=aux->siguiente->siguiente;
					aux2->siguiente=NULL;
					aux2=NULL;
					free(aux2);
					break;
				}
				aux=aux->siguiente;
			}
		}
	}
	return cab;
}

bool usoMarcoExiste(colaUso cab, int idProceso){
bool existe=false;
colaUso aux;
aux=cab;

while(aux!=NULL){

	if(aux->idProceso==idProceso){
		existe=true;
	}

	aux=aux->siguiente;
}
return existe;
}

//--------------------------listaProcesos---------------
void ingresarProceso(listaProcesos&cab,int idProceso,string nombre,double memTotal){
	nodoProceso*nuevo;
	listaProcesos aux;
	nuevo=crearNodoProceso(idProceso,nombre,memTotal);


	if(cab==NULL)
	cab=nuevo;
	else
	{
		aux=cab;
		while(aux->siguiente!=NULL)
		aux=aux->siguiente;

		aux->siguiente=nuevo;
	}

}



//------------------------paginaProceso---------------------
void ingresarPaginaProceso(listaProcesos&cab,int idPagina,int idProceso,double memoria,bool enUso,bool enEspera){
	nodoPaginaProceso*nuevo,*auxp;
	listaProcesos aux;
	nuevo=crearNodoPaginaProceso(idPagina,idProceso,memoria,enUso,enEspera);

	if(cab==NULL){
		cout<<"Lista vacia"<<endl;
	}else{

		aux=cab;
		while(aux->idProceso!=idProceso){
			aux=aux->siguiente;
		}

		if(aux->paginas==NULL){

			aux->paginas=nuevo;

		}else{

			auxp=aux->paginas;

			while(auxp->siguiente!=NULL){

				auxp=auxp->siguiente;
			}
			auxp->siguiente=nuevo;
		}

	}
}

void modificarPaginaProceso(listaProcesos cab,int idProceso,int idPagina,bool enUso,bool enEspera){
	listaProcesos aux;
	nodoPaginaProceso*aux1;
	aux=cab;
	if(cab==NULL){
		cout<<"Lista vacia"<<endl;
	}else{

		while(aux!=NULL){

			if(aux->idProceso==idProceso){

				aux1=aux->paginas;
				while(aux1!=NULL){

					if(aux1->idPagina==idPagina){
						aux1->enUso=enUso;
						aux1->enEspera=enEspera;
					}


					aux1=aux1->siguiente;
				}

			}


			aux=aux->siguiente;
		}

	}
}

//---------listaTablas--------------------
void ingresarTabla(listaTablas&cab, int idProceso){
nodoTablaPag*nuevo;
listaTablas aux;
nuevo=crearNodoTablaPag(idProceso);

if(cab==NULL)
cab=nuevo;
else
{
	aux=cab;
	while(aux->siguiente!=NULL)
	aux=aux->siguiente;

	aux->siguiente=nuevo;
}



}

listaTablas eliminarTabla(listaTablas cab,int idProceso){
	listaTablas aux;
	listaTablas aux2;
	if(cab==NULL){
			cout<<"No existen tablas de paginacion"<<endl;

		}else{
			aux=cab;

			if(aux->idProceso==idProceso){

				cab=cab->siguiente;
				aux->siguiente=NULL;
				aux=NULL;
				free(aux);
			}else{

				while(aux->siguiente!=NULL){

					if(aux->siguiente->idProceso==idProceso){
						aux2=aux->siguiente;
						aux->siguiente=aux->siguiente->siguiente;
						aux2->siguiente=NULL;
						aux2=NULL;
						free(aux2);
						break;
					}
					aux=aux->siguiente;
				}
			}
		}


	return cab;
}


int main(){

	return 0;
}
