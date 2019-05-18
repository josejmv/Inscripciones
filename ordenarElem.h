#include <time.h>
#include <stdlib.h>

// desorden
template <class Tipo>
void desordenNum(int *,int);
// intercambio: v[i] cambia por v[i+-n]
template <class Tipo>
void intercambio(Tipo *,int,int);
// ordenar
template <class Tipo>
void oBurbuja(Tipo *,int);
template <class Tipo>
void oBurbujaPlus(Tipo *, int);
template <class Tipo>
void oSeleccion(Tipo *,int);
template <class Tipo>
void oShell(Tipo *,int);
template <class Tipo>
void oShaker(Tipo *,int);
template <class Tipo>
void oQuick(Tipo *,int,int); // nuevo
template <class Tipo>
void oInsercionDir(Tipo *,int);
template <class Tipo>
void oInsercionBin(Tipo *,int);
// buscar
template <class Tipo>
int bMixta(Tipo,Tipo *,int);
template <class Tipo>
int bBinaria(Tipo,Tipo *,int);
template <class Tipo>
int bSecuencial(Tipo,Tipo *,int);

// generar una seguidilla de numeros pero de forma desordenada, ejm: vector[4]={3,1,2,4};

template <class Tipo>
void desordenNum(Tipo *vector,int tam){
	int stop;
	int random;
	srand(time(NULL));
	for(int i=0;i<tam;i++){
		stop=0;
		random=0;
		while(stop==0){
			stop = 1;
			random=rand()%(tam+1);	
			for(int j=0;j<tam;j++){
				if(random==vector[j]){
					stop=0;
				}
			}
		};	
		vector[i] = random;
	}		
}


template <class Tipo>
void intercambio(Tipo *vector,int a,int b){
	Tipo aux = vector[a];
	vector[a] = vector[b];
	vector[b] = aux;
}


// metodos de ordenamiento

template <class Tipo>
void oBurbuja(Tipo *vector,int tam){
	for(int i=0;i<tam;i++){
		for(int j=0;j<tam-i-1;j++){
			if(vector[j]>vector[j+1]){
				intercambio(vector,j,j+1);
			}	
		}
	}
}

template <class Tipo>
void oBurbujaPlus(Tipo *vector,int tam){
	int band;
	for(int i=0;i<tam;i++){
		band = 0;
		for(int j=0;j<tam-i-1;j++){
			if(vector[j]>vector[j+1]){
				intercambio(vector,j,j+1);
				band=1;
			}
		}
		if(band==0){
			break;
		}
	}
}

template <class Tipo>
void oSeleccion(Tipo *vector,int tam){
	int min;
	for(int i=0;i<tam;i++){
		min=i;
		for(int j=i+1;j<tam;j++){
			if(vector[j]<vector[min]){
				min=j;
			}
		}
		intercambio(vector,i,min);
	}
}

template <class Tipo>
void oShell(Tipo *vector,int tam){
	bool band;
	int i;
	int salto = tam/2;
	while(salto>0){
		band = false;
		for(i=0;(i+salto)<tam;i++)
		if(vector[i]>vector[i+salto]){
			intercambio(vector,i,i+salto);
			band=true;
		}
		if(!band)
		salto/=2;
	}
}

template <class Tipo>
void oShaker(Tipo *vector,int tam){
	int li=0,ls=tam-1,pos=tam-2;
	while(li<ls){
		for(int i=ls;i>li;i--)
			if(vector[i]<vector[i-1]){
				intercambio(vector,i,i-1);
				pos=i;
			}
		li=pos;
		for(int i=li;i<ls;i++)
			if(vector[i]>vector[i+1]){
				intercambio(vector,i,i+1);
				pos=i;
			}
		ls=pos;
	}
}

template <class Tipo>
void oQuick(Tipo *vector,int limInf,int limSup){
	int i,j,piv,aux;
	piv=vector[(int)(limInf+limSup)/2];
	i=limInf;j=limSup;
	do{
		while(vector[i]<piv)
			i++;
		while(vector[j]>piv)
			j--;
		if(i<=j){
			intercambio(vector,i,j);
			i++;
			j--;
		}
	} while(i<j);
	if(limInf<j)
		oQuick(vector,limInf,j);
	if(i<limSup)
		oQuick(vector,i,limSup);
}

template <class Tipo>
void oInsercionDir(Tipo *vector,int tam){
	int mov;
	for(int i=1;i<tam;i++){
		mov = i;
		while(vector[mov]<vector[mov-1] && mov>0){
			intercambio(vector,mov-1,mov);
			mov--;
		};
	}
}

template <class Tipo>
void oInsercionBin(Tipo *vector,int tam){
	int cen,izq,der,mov;
	for(int i=1;i<tam;i++){
		mov = i;
		Tipo aux=vector[i];
		izq=0;
		der=i-1;
		while(izq<=der){
			cen=(izq+der)/2;
			if(aux<=vector[cen])
			der=cen-1;
			else
			izq=cen+1;
		};
		while(mov>izq){
			vector[mov] = vector[mov-1];
			mov --;
		}
		vector[mov] = aux;
	}
}

// metodos de busqueda

// para buscar elementos en vectores que NO SE SABE si estan ordenados, RECOMENDACION: ordenar y utilizar bBinaria() (MAS eficiente)
template <class Tipo>
int bMixta(Tipo dato,Tipo *vector,int tam){
	bool sel=false;
	for(int i=0;i<tam-1;i++){
		if(vector[i]<vector[i+1] && i==tam-2){
			sel = true;
		} else if(vector[i]>vector[i+1]){
			sel = false;
			break;
		}
	}
	switch(sel){
		case false:{
			return bSecuencial(dato,vector,tam);
			break;
		}
		case true:{
			return bBinaria(dato,vector,tam);
			break;
		}
	}
}

// para buscar elementos en vectores desordenados y ordenados (MENOS eficiente)
template <class Tipo>
int bSecuencial(Tipo dato,Tipo *vector,int tam){ 
	bool band=false;
	int i=0;
	while((band==false) && (i<tam)){
		if(vector[i]==dato){
			band=true;
		}
		i++;
	};
	if(band){
		return i;
	} else{
		return -1;
	}
}

// Para buscar elementos en vectores ya ordenados (MAS eficiente)
template <class Tipo>
int bBinaria(Tipo dato,Tipo *vector,int tam){ 
	int mitad;
	int inf=0;
	int sup=tam;
	int stop=0;
	bool band=false;
	while(inf<=sup){
		mitad=(inf+sup)/2;
		stop++;
		if(vector[mitad] == dato){
			band=true;
			return mitad+1;
		}
		if(stop==tam){
			return -1;
		}
		if(vector[mitad]>dato){
			sup=mitad;
			mitad=(inf+sup)/2;
		}
		if(vector[mitad]<dato){
			inf=mitad;
			mitad=(inf+sup)/2;
		}
	}
}
