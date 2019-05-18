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

int main(int argc, char** argv) {
	
	fstream file;
	
	file.open("Alumnos.dat", ios::binary | ios::in);
	
	while(true){
		Alumnos a;
		file.read((char*)&a,sizeof(Alumnos));
		if(file.eof()) break;
		cout<<"nombre: "<<a.nombre<<endl<<"cedula: "<<a.cedula<<endl<<"codigo: "<<a.codigoCarrera<<endl<<endl;
	}
	
	return 0;
}
