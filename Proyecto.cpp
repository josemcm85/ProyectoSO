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

int getMarcoyPagColaUso(colaUso cab,int idProceso){
	colaUso aux;
	aux=cab;
	int marcoYPag=0;
	if(cab!=NULL){

		while(aux!=NULL){
			if(aux->idProceso==idProceso){
				marcoYPag=aux->idMarco * 100 + aux->paginaProceso;
			}
			aux=aux->siguiente;
		}
	}
	return marcoYPag;
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

string getNombreProceso(listaProcesos cab, int idProceso){
	listaProcesos aux;
	string nombre="";
	aux=cab;
	if(cab==NULL){
		cout<<"Lista vacia"<<endl;
	}else{

		while(aux!=NULL){

			if(aux->idProceso==idProceso){
				nombre=aux->nombre;
				}
					aux=aux->siguiente;
			}

		}
		return nombre;
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

//lo mismo que modificarPaginaProceso, pero aplica para todas las páginas
void modificarProceso(listaProcesos cab,int idProceso,bool enUso,bool enEspera){
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


						aux1->enUso=enUso;
						aux1->enEspera=enEspera;
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
if(cab==NULL){

	cab=nuevo;
}else{
	aux=cab;
	while(aux->siguiente!=NULL){
	aux=aux->siguiente;
	}

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

 //-------pagTabla------------
 //numPagina,marcoUbicacion
 void ingresarPaginaTabla(listaTablas&cab,int idProceso,int numPagina,int marcoUbicacion){
	 nodoPagTabla*nuevo,*auxp;
	 listaTablas aux;
	 nuevo=crearNodoPagTabla(numPagina,marcoUbicacion);

	 if(cab==NULL){
		 cout<<"No existen tablas de paginacion"<<endl;
	 }else{
		 aux=cab;

		 while(aux->idProceso!=idProceso){
			 aux=aux->siguiente;
		 }

		 if(aux->paginasTablaPag==NULL ){
			 aux->paginasTablaPag=nuevo;



		 }else{
			 auxp=aux->paginasTablaPag;

			 while(auxp->siguiente!=NULL){
				 auxp=auxp->siguiente;
			 }

			 auxp->siguiente=nuevo;
		 }

	 }
 }

void modificarPaginaTabla(listaTablas cab, int idProceso,int numPagina,int marcoUbicacion){
	nodoPagTabla*aux1;
	listaTablas aux;
	aux=cab;
	if(cab==NULL){
		cout<<"No existen tablas de paginacion"<<endl;
	}else{

		while(aux!=NULL){

			if(aux->idProceso==idProceso){

				aux1=aux->paginasTablaPag;
				while(aux1!=NULL){

					if(aux1->numPagina==numPagina){
						aux1->marcoUbicacion=marcoUbicacion;
					}
					aux1=aux1->siguiente;
				}
			}
			aux=aux->siguiente;
		}
	}
}


//----------listaSwap--------------
void ingresarPaginaSwap(listaSwap&cab,int idProceso, int paginaProceso,double memoriaUsada){
	nodoSwap*nuevo;
	listaSwap aux;
	nuevo=crearNodoSwap(memoriaUsada,idProceso,paginaProceso);

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


listaSwap sacarPaginaSwap(listaSwap&cab){
	listaSwap aux;

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

listaSwap eliminarProcesoSwap(listaSwap&cab, int idProceso){
	listaSwap aux,aux2;
	if(cab==NULL){
		cout<<"No hay paginas en memoria swap"<<endl;
	}else{
		aux=cab;

		if(aux->idProceso==idProceso ){

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

	bool paginaSwapExiste(listaSwap cab, int idProceso){
		bool existe=false;
		listaSwap aux;
		aux=cab;

		while(aux!=NULL){

			if(aux->idProceso==idProceso){
				existe=true;
			}

			aux=aux->siguiente;
		}
		return existe;
	}

//------Métodos de vista-------------
void verListaMarcos(listaMarcos cab){
	listaMarcos aux;
	aux=cab;
	string uso;
	double memTotal=0;
	if(cab==NULL){
		cout<<"Memoria corrupta"<<endl;

	}else{
		cout<<"Lista de marcos de memoria"<<endl;
		cout<<"Marco	Memoria		En uso"<<endl;
	 while(aux!=NULL)	{

	 	if(aux->enUso==true){
	 		uso="Si";
		 }else{
		 	uso="No";
		 }
		cout<<aux->idMarco<<"	"<<aux->memTotal<<" MB"<<"		"<<uso<<endl;
	 	cout<<""<<endl;
	 	memTotal=memTotal+aux->memTotal;

	 	aux=aux->siguiente;
	 }
	 cout<<"Memoria total:"<<memTotal<<" MB"<<endl;
	}
}

void verColaUsoMarcos(colaUso cab){
	colaUso aux;
	aux=cab;
	double memUso=0;
	if(cab==NULL){
		cout<<"La memoria no esta siendo usada"<<endl;
	}else{
		cout<<"	Lista de marcos en uso"<<endl;
		cout<<"Marco	Proceso:Pagina 		Memoria en uso"<<endl;
		cout<<""<<endl;
		while(aux!=NULL){
				memUso=memUso+aux->memoriaUsada;
			cout<<aux->idMarco<<"	"<<aux->idProceso<<":"<<aux->paginaProceso<<"			"<<aux->memoriaUsada<<" MB"<<endl;


			cout<<""<<endl;

			aux=aux->siguiente;
		}

		cout<<"Memoria en uso: "<<memUso<<" MB"<<"/1024 MB"<<endl;
	}
}

void verProcesos(listaProcesos cab){

	listaProcesos aux;
	nodoPaginaProceso*aux1;
	aux=cab;
	string uso;
	string espera;
	if(cab==NULL){
		cout<<"Lista vacia"<<endl;
	}else{
		cout<<"				Lista de procesos"<<endl;
		cout<<"ID	Nombre		Memoria		IDPag	EspacioDisco	EnMemoria	EnSwap"<<endl;

		cout<<""<<endl;
		while(aux!=NULL){

			cout<<aux->idProceso<<"	"<<aux->nombre<<"	"<<aux->memTotal<<" MB"<<endl;
			cout<<""<<endl;

			aux1=aux->paginas;
			while(aux1!=NULL){

				if(aux1->enUso==true){
					uso="Si";
				}else{
						uso="No";
				}

				if(aux1->enEspera==true){
						espera="Si";
				}else{
						espera="No";
				}
				cout<<"					"<<aux1->idPagina<<"	"<<aux1->memoria<<" MB"<<"		"<<uso<<"		"<<espera<<endl;
				cout<<""<<endl;
					aux1=aux1->siguiente;
			}
			cout<<""<<endl;
			aux=aux->siguiente;
		}
	}
}

void verlistaSwap(listaSwap cab){
	listaSwap aux;
	aux=cab;
	double memUso=0;
	if(cab==NULL){
		cout<<"La memoria swap no esta siendo usada"<<endl;
	}else{

		cout<<"	Lista de paginas en swap"<<endl;
		cout<<"Proceso:Pagina   	Memoria en uso"<<endl;
		cout<<""<<endl;

		while(aux!=NULL){
				memUso=memUso+aux->memoriaUsada;
			cout<<aux->idProceso<<":"<<aux->paginaProceso<<"			"<<aux->memoriaUsada<<" MB"<<endl;
			cout<<""<<endl;
			aux=aux->siguiente;
		}
		cout<<"swap en uso: "<<memUso<<" MB"<<"/2048 MB"<<endl;
	}
}

void verTablasPag(listaTablas cab){
	listaTablas aux;
	nodoPagTabla*aux1;
	aux=cab;
	if(cab==NULL){
		cout<<"No existen tablas de paginacion"<<endl;
	}else{
		cout<<"	Lista de tablas"<<endl;
		cout<<"ID	 #Pagina	Marco	"<<endl;
		cout<<""<<endl;

		while(aux!=NULL){

			cout<<aux->idProceso<<endl;
			cout<<""<<endl;
			aux1=aux->paginasTablaPag;

			while(aux1!=NULL){
				cout<<"	"<<aux1->numPagina<<"		"<<aux1->marcoUbicacion<<endl;
				cout<<""<<endl;
				aux1=aux1->siguiente;
			}
			cout<<""<<endl;
			aux=aux->siguiente;
		}
	}
}
//---------------Misc-------------------------....
bool getProcesoEstaAbierto(listaTablas cab,int idProceso){
	bool estaAbierto=false;
	listaTablas aux;
	aux=cab;
	if(cab=NULL)	{
	return estaAbierto;
	}else{

		while(aux!=NULL){

			if(idProceso==aux->idProceso){
				estaAbierto=true;
			}
			aux=aux->siguiente;
		}


	}
	return estaAbierto;
}

bool getPaginaEstaAbierta(listaTablas cab, int idProceso, int numPagina){
	bool estaAbierto=false;
	listaTablas aux;
	nodoPagTabla* auxp;
	aux=cab;
	if(cab=NULL){
		return estaAbierto;
	}else{

		while(aux!=NULL){

			if(aux->idProceso==idProceso){
				auxp=aux->paginasTablaPag;

				while(auxp!=NULL){

					if(auxp->numPagina==numPagina){
						estaAbierto=true;
					}
					auxp=auxp->siguiente;
				}
			}
			aux=aux->siguiente;

		}
	}
	return estaAbierto;
}


int marcosDisponibles(listaMarcos cab){
	listaMarcos aux;
	aux=cab;
	int cantMarcos=0;
	if(cab==NULL){
		cout<<"No hay marcos registrados";
	}else{
		while(aux!=NULL){
			if(aux->enUso==false){
				cantMarcos++;
			}
			aux=aux->siguiente;
		}
	}
	return cantMarcos;
}

int getMarcoDisponible(listaMarcos marcos){
	listaMarcos aux;
	int idMarco=0;
	aux=marcos;
	while(aux!=NULL){
		if(aux->enUso==false){
			idMarco=aux->idMarco;

			break;
		}

		aux=aux->siguiente;
	}

	return idMarco;
}

int getCantidadPaginasProceso(listaProcesos cab,int idProceso){
listaProcesos aux;
	nodoPaginaProceso*aux1;
	aux=cab;
	int cantPaginas=0;
	if(cab==NULL){
		cout<<"Lista vacía"<<endl;
	}else{

		while(aux!=NULL){

			if(aux->idProceso==idProceso){

				aux1=aux->paginas;
				while(aux1!=NULL){
					cantPaginas++;



					aux1=aux1->siguiente;
				}

			}


			aux=aux->siguiente;
		}

	}
	return cantPaginas;
}


bool procesoExiste(listaProcesos cab,int proceso){
	listaProcesos aux;
	bool existe=false;

	aux=cab;

	while(aux!=NULL){
		if(proceso==aux->idProceso){
			existe=true;
		}
		aux=aux->siguiente;
	}




	return existe;
}


double memoriaUsadaPagina(listaProcesos cab,int idProceso,int idPagina){

	listaProcesos aux;
	nodoPaginaProceso*aux1;
	aux=cab;
	string uso;
	string espera;
	double memoriaUsada=0;
	if(cab==NULL){
	}else{

		while(aux!=NULL){

		if(aux->idProceso==idProceso){


				aux1=aux->paginas;
				while(aux1!=NULL){

					 if(aux1->idPagina==idPagina){
					 	memoriaUsada=aux1->memoria;
					 }



					aux1=aux1->siguiente;
				}


			cout<<""<<endl;
		}




			aux=aux->siguiente;
		}

	}
	return memoriaUsada;
}

double  memoriaUsoSwap(listaSwap cab){

	listaSwap aux;
	aux=cab;
	double memUso=0;
	if(cab!=NULL){

		while(aux!=NULL){
			memUso=memUso+aux->memoriaUsada;
			aux=aux->siguiente;
		}
	}
	return memUso;
}

listaProcesos procesos=NULL;
colaUso marcosEnUso=NULL;
listaMarcos marcos=NULL;
listaSwap colaSwap=NULL;
listaTablas tablas=NULL;

//----------------Opciones Menu-------------------
void abrirProceso(){
	int procesoAbrir;
	bool existe;
	bool abierto;
	int cantPaginasProceso;
	srand(time(0));
	int cantPaginasAbrir;
	int marcosVacios;
	bool marcosSuficientes;
	int paginaBorrar;
	int procesoBorrar;
	int marcoBorrar;
	colaNumeros numeros=NULL;
	int paginasPorGenerar;
	double memUsoSwap;
	double memoriaPaginaBorrar;
	int procesoCabezaSwap;
	bool existeSwap;
	bool existeEnMarco;
	int marcoYPag;
	int marcoCrash;
	int paginaCrash;
	int numPagina;
	string nombreCrash;
	//¿Cual quiere abrir?
	cout<<"Ingrese el codigo del proceso que desea abrir"<<endl;
	cin>>procesoAbrir;


	//¿El que quiere abrir existe?
	existe=procesoExiste(procesos,procesoAbrir);

	if(existe){
		//¿El que quiere abrir ya está abierto?
		abierto=getProcesoEstaAbierto(tablas,procesoAbrir);

		if(abierto)	{
			cout<<"El proceso ya se encuentra abierto"<<endl;
		}else{
				//¿Cuántas paginas tiene el proceso?
			cantPaginasProceso=getCantidadPaginasProceso(procesos,procesoAbrir);

				//¿Cuántas páginas se van a abrir?
		  cantPaginasAbrir=(rand()%cantPaginasProceso)+1;

			  do{

			  	//¿Cuántos marcos hay disponibles?
					marcosVacios=marcosDisponibles(marcos);

				//¿Hay espacio para abrir esa cantidad de paginas?
			  	if(cantPaginasAbrir>marcosVacios){
			  		marcosSuficientes=false;
					}else{
						marcosSuficientes=true;

					}

			  	//Liberar espacio si no hay marcos libres para abrirlas
			  	if(marcosSuficientes==false){

			  		marcoBorrar=marcosEnUso->idMarco;
			  		paginaBorrar=marcosEnUso->paginaProceso;
			  		procesoBorrar=marcosEnUso->idProceso;
						memoriaPaginaBorrar=marcosEnUso->memoriaUsada;

			  		//Borrar de marcosUso
			  		marcosEnUso=sacarUsoMarco(marcosEnUso);

						memUsoSwap=memoriaUsoSwap(colaSwap) + memoriaPaginaBorrar;

						//Si la pagina que se debe mover a swap no cabe
						//Es necesario crashear un proceso
						if(memUsoSwap>2048){
							procesoCabezaSwap=colaSwap->idProceso;


							//Libera páginas de swap mientras siga habiendo coincidencias
							//del proceso a cerrar
							do{
								existeSwap=paginaSwapExiste(colaSwap,procesoCabezaSwap);
								colaSwap=eliminarProcesoSwap(colaSwap,procesoCabezaSwap);

							}while(existeSwap);

							//Revisa si existen páginas del proceso a cerrar en memoria principal
							//y las cierra si es el caso
							do{
								existeEnMarco=usoMarcoExiste(marcosEnUso,procesoCabezaSwap);
								if(existeEnMarco){
									marcoYPag=getMarcoyPagColaUso(marcosEnUso,procesoCabezaSwap);
									marcosEnUso=eliminarUsoMarco(marcosEnUso,procesoCabezaSwap);
									marcoCrash=(int) marcoYPag/100;
									paginaCrash=(marcoYPag % 100)*100;

									modificarMarcoPagina(marcos,marcoCrash,false);
									modificarPaginaProceso(procesos,procesoCabezaSwap,paginaCrash,false,false);
								}

							}while(existeEnMarco);

							//Actualizamos el estado de todas las páginas del proceso
							modificarProceso(procesos,procesoCabezaSwap,false,false);
							//Liberamos la tabla de páginas
							tablas=eliminarTabla(tablas,procesoCabezaSwap);

							nombreCrash=getNombreProceso(procesos,procesoCabezaSwap);
							cout<<"El proceso "<<nombreCrash<< " se ha detenido"<<endl;

						}

						ingresarPaginaSwap(colaSwap,procesoBorrar,paginaBorrar,memoriaPaginaBorrar);


						numPagina=procesoBorrar*1000+paginaBorrar;
							//----Modificar pagina en listaTablas----
						modificarPaginaTabla(tablas, procesoBorrar,numPagina,-1);




			  		//Informar:se borró la pagina x del proceso x
			  		cout<<"La pagina "<<paginaBorrar<< " del proceso "<<procesoBorrar<< " ha sido enviada a la memoria swap"<<endl;


						//Modificar estado de marco
						modificarMarcoPagina(marcos,marcoBorrar,false);


						//Modificar estado de la pagina enviada a swap en listaProcesos(cerrada y en espera)
						modificarPaginaProceso(procesos,procesoBorrar,paginaBorrar,false,true);
				  }



			  }while(marcosSuficientes==false);
				double memoria;
				int paginaNueva;
				int marcoDisponible;
				bool existe;


				paginasPorGenerar=cantPaginasAbrir;
				do{

					//¿Página generada es única?
					do{
						//¿Cuales paginas se van a abrir?
						paginaNueva=(rand()%cantPaginasProceso)+1;
						existe=numExiste(numeros,paginaNueva);
					}while(existe);

					ingresarColaNum(numeros,paginaNueva);
					paginasPorGenerar--;

				}while(paginasPorGenerar!=0);

//------Crear tabla de paginas---------
ingresarTabla(tablas,procesoAbrir);


				do{

					paginaNueva=numeros->num;
					numeros=sacarColaNum(numeros);
						//¿Cuanta memoria usan?
					memoria=memoriaUsadaPagina(procesos,procesoAbrir,paginaNueva);

						//¿Cual marco está disponible?
					marcoDisponible=getMarcoDisponible(marcos);

						//Abrir páginas
					ingresarUsoMarco(marcosEnUso,marcoDisponible,procesoAbrir,paginaNueva,memoria);

						//Modificar estado de marco
					modificarMarcoPagina(marcos,marcoDisponible,true);
						//Modificar estado de la pagina abierta en listaProcesos
					modificarPaginaProceso(procesos,procesoAbrir,paginaNueva,true,false);


					//------------Ingresar pagina a listaTablas-------
					numPagina=procesoAbrir*1000+paginaNueva;
					 ingresarPaginaTabla(tablas,procesoAbrir,numPagina,marcoDisponible);

					cantPaginasAbrir--;
				}while(cantPaginasAbrir!=0);

			cout<<"Se ha abierto el proceso"<<endl;

		}
	}else{
		cout<<"El proceso ingresado no existe"<<endl;
	}
}

//-----------Menú principal--------------------..
int main(){

	double memoria;
	int memInt;
	int ingresados=0;
	double memoriaExtra;
	int memDeMas;
	double paginasNecesita;
	int paginaActual=0;

	do{
		memoriaExtra=0;
		ingresados++;

			switch(ingresados){
				case 1:
				memoria=450;
				ingresarProceso(procesos,1,"Spotify.exe",memoria);
				break;

				case 2:
				memoria=450;
				ingresarProceso(procesos,2,"Word.exe",memoria);
				break;

				case 3:
				memoria=450;
				ingresarProceso(procesos,3,"Excel.exe",memoria);
				break;

				case 4:
				memoria=775;
				ingresarProceso(procesos,4,"Photoshop.exe",memoria);
				break;

				case 5:
	 	    memoria=825;
				ingresarProceso(procesos,5,"League of Legends.exe",memoria);
				break;

				case 6:
				memoria=850;
				ingresarProceso(procesos,6,"Valorant.exe",memoria);
				break;

				case 7:
				memoria=600;
				ingresarProceso(procesos,7,"Chrome.exe",memoria);
				break;

				case 8:
				memoria=800;
				ingresarProceso(procesos,8,"OBS Studio.exe",memoria);
				break;

				case 9:
				memoria=450;
				ingresarProceso(procesos,9,"FileZilla.exe",memoria);
				break;

				case 10:
				memoria=800;
				ingresarProceso(procesos,10,"Audacity.exe",memoria);
				break;

				case 11:
				memoria=750;
				ingresarProceso(procesos,11,"Discord.exe",memoria);
				break;

				case 12:
				memoria=850;
				ingresarProceso(procesos,12,"Calibre.exe",memoria);
				break;

				case 13:
				memoria=825;
				ingresarProceso(procesos,13,"Zoom.exe",memoria);
				break;

				case 14:
				memoria=825;
				ingresarProceso(procesos,14,"vs code.exe",memoria);
				break;


				case 15:
				memoria=850;
				ingresarProceso(procesos,15,"Microsoft Teams.exe",memoria);
				break;

	  }
		memInt=memoria;
		memoriaExtra=memInt % 64;
		memoria-memoriaExtra;
		paginasNecesita=memoria/64;
		paginaActual=1;

		do{

			ingresarPaginaProceso(procesos,paginaActual,ingresados,64,false,false);
			paginasNecesita=paginasNecesita-1;
			paginaActual++;
		}while(paginasNecesita>1);

		if(memoriaExtra!=0){
			ingresarPaginaProceso(procesos,paginaActual,ingresados,memoriaExtra,false,false);
		}


	}while(ingresados!=15);

	ingresados=0;

	do{
		ingresados++;
		ingresarMarcoPagina(marcos,ingresados,64,false);

	}while(ingresados!=16);

	int opcion;

	do{
		system("cls");
		cout<<"Ingrese una opcion"<<endl;
		cout<<"1.Abrir un proceso"<<endl;
		cout<<"2.Ver procesos"<<endl;
		cout<<"3.Ver marcos de memoria"<<endl;
		cout<<"4.Ver marcos en uso"<<endl;
		cout<<"5.Ver Swap"<<endl;
		cout<<"6. Ver tablas de paginas"<<endl;
		cout<<"7. Ver procesos en ejecucion"<<endl;
		cout<<"8.Salir"<<endl;

		cin>>opcion;

		switch(opcion){
			case 1:
				system("cls");
				abrirProceso();
				system("pause");
				break;

			case 2:
				system("cls");
			  verProcesos(procesos);
				system("pause");
				break;

			case 3:
				system("cls");
			 verListaMarcos(marcos);
				system("pause");
				break;

			case 4:
				system("cls");
			 verColaUsoMarcos(marcosEnUso);
				system("pause");
				break;

			case 5:
				system("cls");
				verlistaSwap(colaSwap);
				system("pause");
				break;

			case 6:
				system("cls");
			 verTablasPag(tablas);
				system("pause");
				break;

			case 7:
				system("cls");
				//Método
				system("pause");
				break;
		}

	}while(opcion!=8);

	return 0;
}
