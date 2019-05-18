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

int main(int argc, char** argv) {
	
	int cont=0;
	fstream file,file2;
	
	file2.open("Alumnos.dat",ios::binary | ios::in);
	
	while(cont<10){
		Alumnos c;
		file2.read((char*)&c,sizeof(Alumnos));
		if(file2.eof()) break;
		cout<<"Nombre: "<<c.nombre<<endl<<"Cedula: "<<c.cedula<<endl<<"CodigoCarrera: "<<c.codigoCarrera<<endl;
		file.open("Carreras.dat", ios::binary | ios::in);
		while(true){
			Carrera a;
			file.read((char*)&a,sizeof(Carrera));
			if(file.eof()) break;
			if(c.codigoCarrera == a.codigoCarrera)
				cout<<"NombreCarrera: "<<a.nombreCarrera<<endl<<endl;
		}
		file.close();
		cont++;
	}
	file2.close();
	
	
	/*
	
	LEER DATA de Alumnos
	
	fstream file;
	
	file.open("Alumnos.dat", ios::binary | ios::in);
	
	while(true){
		Alumnos a;
		file.read((char*)&a,sizeof(Alumnos));
		if(file.eof()) break;
		cout<<"nombre: "<<a.nombre<<endl<<"cedula: "<<a.cedula<<endl<<"codigo: "<<a.codigoCarrera<<endl<<endl;
	}
	*/
	return 0;
}
