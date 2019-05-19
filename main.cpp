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
void Consultar(bool);
void ImprimirPensum(int);
void marco();

int main(int argc, char** argv) {

	Inscripcion(1110);		

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
					if(materias.eof()){
						cout<<endl<<".....Materia no encontrada....."<<endl;
						break;
					}
					
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
	if(pensum.fail())
	{
		cout<<".....Carrera NO encontrada.....";
		getch();
	}
	else{
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

void Consultar(bool alumno ){
	system("cls");
	int cedula;
	int codigo;
	
	if(alumno){	
		fstream alum,insc,car;
		Alumnos a;
		Inscritos i;
		Carrera c;

		alum.open("Alumnos.dat",ios::binary | ios::in);
		cout<<"ingrese la cedula del alumno: ";
		cin>>cedula;
		while(true){
			alum.read((char*)&a,sizeof(Alumnos));
			if(alum.eof()){
				cout<<".....Alumno no encontrado.....";
				getch();
			}
			if(a.cedula==cedula){
				cout<<endl<<"Informacion del Alumno: "<<endl<<endl;
				cout<<"Cedula: "<<a.cedula<<endl;
				cout<<"Nombre: "<<a.nombre<<endl;
				car.open("Carreras.dat",ios::binary | ios::in);		
				while(true){
					car.read((char*)&c,sizeof(Carrera));
					if(car.eof()){
						cout<<"Carrera: NULL"<<endl;
						break;
					}
					if(a.codigoCarrera == c.codigoCarrera){
						cout<<"Carrera: "<<c.nombreCarrera<<endl;
						break;
					}
				}
				car.close();
				insc.open("Inscritos.dat",ios::binary | ios::in);
				while(true){
					insc.read((char*)&i,sizeof(Inscritos));
					if(insc.eof()){
						cout<<"Codigo de Materias: NULL"<<endl;
						cout<<"Total UC Inscritas: NULL"<<endl<<endl;
						break;
					}
					if(a.cedula == i.cedula){
						cout<<"Codigo de Materias: "<<i.codMaterias<<endl;
						cout<<"Total UC Inscritas: "<<i.totalUC<<endl<<endl;
						break;
					}
				}
				insc.close();
				break;
			}
		}	
		alum.close();	
	}else{
		
		int codigoAux;
		char aux[10];
		fstream mat,car;
		
		cout<<"ingrese el codigo de la materia: ";
		cin>>codigo;
		codigoAux=codigo;
		codigoAux/=100;
		itoa(codigoAux,aux,10);
		strcat(aux,".dat");
		
		mat.open(aux,ios::binary | ios::in);
		if(mat.fail()){
			cout<<".....Materia no Encontrada.....";
			mat.close();
			getch();
		}
		else{
			while(true){
				Materia m;
				mat.read((char*)&m,sizeof(Materia));
				if(mat.eof()) break;
				if(m.codMateria==codigo){
					cout<<"Materia: "<<m.nomMareria<<endl;
					cout<<"Semestre: "<<m.numSemestre<<endl;
					cout<<"UC: "<<m.UC<<endl;
					car.open("Carreras.dat",ios::binary | ios::in);
					while(true){
						Carrera c;
						car.read((char*)&c,sizeof(Carrera));
						if(car.eof()) break;
						if(c.codigoCarrera == codigo/100){
							cout<<"Carrera: "<<c.nombreCarrera<<endl<<endl;
							break;
						}
					}
					car.close();
					break;
				}
			}
			mat.close();
		}
	}	
}
