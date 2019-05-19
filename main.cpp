#include <iostream>
#include <fstream>
#include <cstring>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

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
struct Materia{
	int numSemestre;
	int codMateria;
	char nomMareria[40];
	int UC;
};
struct Inscritos{
	int cedula;
	char codMaterias[120];
	int totalUC;
};

void gotoxy(int,int);
void Inscripcion(int);
void ImprimirPensum(int);
void marco();

int main(int argc, char** argv) {
	
	/*
	int cedula;

	cout<<"Ingrese la cedula de un alumno que quiera inscribir: ";
	cin>>cedula;
	Inscripcion(cedula);
	*/
	
	
	Inscritos i;
	fstream file;
	
	file.open("Inscritos.dat",ios::binary | ios::in);
	while(true){
		file.read((char*)&i,sizeof(Inscritos));
		if(file.eof())break;	
		cout<<endl<<"Cedula: "<<i.cedula<<endl<<"CodigoMaterias: "<<i.codMaterias<<endl<<"Total UC: "<<i.totalUC<<endl;
	}
	


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


void Inscripcion(int cedula){
	
	int materia;
	char mat[3];
	char cod[10];
	int maxUC=0;
	
	int opcion;
	
	fstream alumnos;
	fstream carrera;
	fstream materias;
	fstream inscritos;
	
	alumnos.open("Alumnos.dat",ios::binary | ios::in);
	
	while(true){
		Alumnos a;
		alumnos.read((char*)&a,sizeof(Alumnos));
		if(alumnos.eof())break;
		if(a.cedula == cedula){
			Inscritos inscrito;
			while(true){
				cout<<endl<<"En que materia desea Inscribir al alumno "<<a.nombre<<endl<<"Materia: ";
				strcpy(mat,"");
				cin>>materia;
				itoa(a.codigoCarrera,cod,10);
				strcat(cod, ".dat");
				materias.open(cod,ios::binary | ios::in);
				while(true){
					Materia m;
					materias.read((char*)&m,sizeof(Materia));				
					if(materias.eof()) break;
					if(m.codMateria%100 == materia){
						itoa(materia,mat,10);
						maxUC+=m.UC;
						if(maxUC<=12){
							cout<<endl<<"inscrito en la materia: "<<m.nomMareria<<endl;
							cout<<maxUC<<endl;
							strcat(inscrito.codMaterias,mat);
							break;
						}
						else if(maxUC>12){
							cout<<endl<<"...Limite de UC Excedido..."<<endl;
							maxUC-=m.UC;
							break;
						}
					}
				}
				materias.close();
				do{
					cout<<endl<<"Desea Inscribir otra Materia? 1[SI] | 2[NO]"<<endl<<"Opcion: ";
					cin>>opcion;
				} while(opcion<1||opcion>2);
				if(opcion==2){
					
					inscrito.cedula=a.cedula;
					inscrito.totalUC=maxUC;
					
					inscritos.open("Inscritos.dat",ios::binary | ios::app);
					inscritos.write((char*)&inscrito,sizeof(Inscritos));
					inscritos.close();
					
					cout<<endl<<"Cedula: "<<inscrito.cedula<<endl<<"CodigoMaterias: "<<inscrito.codMaterias<<endl<<"Total UC: "<<inscrito.totalUC<<endl;
					cout<<endl<<".....Inscripcion realizada Exitosamente, pulse cualquier tecla....."<<endl;
					getch();
					break;
				}
			}
			break;
		}
	}	
}

void ImprimirPensum(int codigo){
	
	system("cls");
	
	fstream pensum;
	int y=4;
	
	char cod[4];
	
	itoa(codigo,cod,10);
	strcat(cod, ".dat");
	pensum.open(cod,ios::binary | ios::in);
	
	
	gotoxy(1,2);
	cout<<"Semestre";
	gotoxy(11,2);
	cout<<"Codigo";
	gotoxy(30,2);
	cout<<"Materia";
	gotoxy(55,2);
	cout<<"Unidades de Credito";
	
	while(true){
		Materia mat;
		pensum.read((char*)&mat,sizeof(Materia));
		if(pensum.eof()) break;
		gotoxy(5,y);
		cout<<mat.numSemestre;
		gotoxy(11,y);
		cout<<mat.codMateria;
		gotoxy(22,y);
		cout<<mat.nomMareria;
		gotoxy(65,y);
		cout<<mat.UC;
		y++;
	}
	marco();
	gotoxy(0,48);
}

void marco(){
	for(int i=0;i<42;i++){
		gotoxy(0,i+2);
		cout<<"|";
	}
	for(int i=0;i<42;i++){
		gotoxy(10,i+2);
		cout<<"|";
	}
	for(int i=0;i<42;i++){
		gotoxy(20,i+2);
		cout<<"|";
	}
	for(int i=0;i<42;i++){
		gotoxy(54,i+2);
		cout<<"|";
	}
	for(int i=0;i<42;i++){
		gotoxy(74,i+2);
		cout<<"|";
	}
}

void gotoxy(int x,int y){
	HANDLE hcon = GetStdHandle (STD_OUTPUT_HANDLE);
	COORD dwpos;
	dwpos.X=x;
	dwpos.Y=y;
	SetConsoleCursorPosition(hcon,dwpos);
}
