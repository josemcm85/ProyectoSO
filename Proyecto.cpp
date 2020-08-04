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
			 aux->paginasTablaPag==nuevo;
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
	nuevo=crearNodoSwap(idProceso,paginaProceso,memoriaUsada);

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
		cout<<"ID	Nombre		Memoria		IDPag	EspacioDisco	EnUso	EnSwap"<<endl;

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
				cout<<"					"<<aux1->idPagina<<"	"<<aux1->memoria<<" MB"<<"		"<<uso<<"	"<<espera<<endl;
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
				cout<<"	"<<aux1->numPagina<<"	"<<aux1->marcoUbicacion<<endl;
				cout<<""<<endl;
				aux1=aux1->siguiente;
			}
			cout<<""<<endl;
			aux=aux->siguiente;
		}
	}
}


int main(){
	listaMarcos marcos=NULL;
	colaUso marcosEnUso=NULL;
	listaProcesos procesos=NULL;
	listaTablas tablas=NULL;
	listaSwap swap=NULL;
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


	}while(ingresados!=5);

	ingresados=0;

	do{
		ingresados++;
		ingresarMarcoPagina(marcos,ingresados,64,false);

	}while(ingresados!=16);
/*
Abrir proceso
ver procesos
ver marcos
ver marcos en uso
ver swap
ver tablas de paginas
ver procesos en ejecucion(marcos+swap)
salir
*/
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
				//Método
				system("pause");
				break;

			case 2:
				system("cls");
				//Método
				system("pause");
				break;

			case 3:
				system("cls");
				//Método
				system("pause");
				break;

			case 4:
				system("cls");
				//Método
				system("pause");
				break;

			case 5:
				system("cls");
				//Método
				system("pause");
				break;

			case 6:
				system("cls");
				//Método
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
