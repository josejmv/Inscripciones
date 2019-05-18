#include <iostream>
#include <fstream>
#include <cstring>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include "ordenarElem.h"

using namespace std;

struct Alumnos{
	char nombre[45];
};

int main(int argc, char** argv) {
	
	
	fstream file,codigo,alumnos,cedulas;
	string textoCodigo;
	string textoNombres;
	string textoCedulas;
	char *token1;
	char cod[20];
	int escoger;
	int cont=1;
	
	alumnos.open("Alumnos.txt",ios::out);
	file.open("DataNombres.txt",ios::in);
	cedulas.open("Cedulas.txt",ios::in);
	srand(time(NULL));
	
	while(true){
		getline(file,textoNombres);
		getline(cedulas,textoCedulas);
		escoger = 1+rand()%3;
		codigo.open("Carreras.txt",ios::in);
		while(true){
			getline(codigo,textoCodigo);
			strcpy(cod,textoCodigo.c_str());
			token1 = strtok(cod,",");
			if(cont==escoger){
				codigo.close();
				break;
			}
			cont++;
		}
		alumnos<<textoCedulas<<"-"<<textoNombres<<"-"<<token1<<endl;
		if(file.eof()) break;
		cont=1;
	}		
		

/*	string texto;
	file.open("DataNombres.txt",ios::in);
	
	while(!file.eof()){
		Alumnos a;
		getline(file,texto);
		strcpy(a.nombre,texto.c_str());
		bin.write((char*)&a,sizeof(Alumnos));
	}
*/
	return 0;
}
