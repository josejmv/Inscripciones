#include <iostream>
#include <fstream>
#include <cstring>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

struct Alumnos{
	int cedula;
	char nombre[45];
	int codigoCarrera;
};
struct Carrera{
	int codigoCarrera;
	char nombreCarrera[25];
};
struct CodigoCarrera{
	int numSemestre;
	int codMateria;
	char nomMareria[40];
	int UC;
};

int main(int argc, char** argv) {
	
	fstream file,bin;
	string texto;
	char linea[40];
	char *token;
	
//	file.open("4312.txt",ios::in);
	bin.open("4178.dat",ios::binary | ios::in);
	
	
	while(true){
		CodigoCarrera cod;
		
		bin.read((char*)&cod,sizeof(CodigoCarrera));
		
		if(bin.eof()) break;
		cout<<cod.numSemestre<<endl<<cod.codMateria<<endl<<cod.nomMareria<<endl<<cod.UC<<endl<<endl;
		getch();
	}
	
	/*
	while(true){
		CodigoCarrera cod;
		getline(file,texto);
		strcpy(linea,texto.c_str());
		
		token=strtok(linea,",");
		cod.numSemestre=atoi(token);
//		if(cod.numSemestre == 0) cod.numSemestre=1;
		token=strtok(NULL,",");
		cod.codMateria = atoi(token);
		token=strtok(NULL,",");
		strcpy(cod.nomMareria,token);
		token=strtok(NULL,",");
		cod.UC = atoi(token);
		
		bin.write((char*)&cod,sizeof(CodigoCarrera));
		
		if(file.eof()) break;
	}
	file.close();
	bin.close();
	*/
	/*
	fstream file1,file2;
	
	file1.open("Alumnos.dat",ios::binary | ios::in);
	
	while(true){
		Alumnos a;
		file1.read((char*)&a,sizeof(Alumnos));
		if(file1.eof()) break;
		cout<<"Nombre: "<<a.nombre<<endl<<"Cedula: "<<a.cedula<<endl<<"CodigoCarrera: "<<a.codigoCarrera<<endl;
		file2.open("Carreras.dat", ios::binary | ios::in);
		while(true){
			Carrera c;
			file2.read((char*)&c,sizeof(Carrera));
			if(file2.eof()) break;
			if(a.codigoCarrera == c.codigoCarrera)
				cout<<"NombreCarrera: "<<c.nombreCarrera<<endl<<endl;
		}
		file2.close();
	}
	file1.close();
	*/
	return 0;
}
