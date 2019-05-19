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
void ReporteInscripcion(int);
void InscripcionMateria(int);
void ImprimirPensum(int);
void marco();

int main(int argc, char** argv) {
	
	int cedula;
	int codigo;
	int opcion;

/*	
//	LISTA DE ALUMNOS INSCRITOS EN UNA MATERIA LISTO

	cout<<"Ingrese el codigo de la materia: ";
	cin>>codigo;
	InscripcionMateria(codigo);
*/	

	
/*	
//	REPORTE DE INSCRIPCION LISTO

	cout<<"Ingrese el numero de cedula del Alumno: ";
	cin>>cedula;
	ReporteInscripcion(cedula);
*/	

	
/*
//	INSCRIPCION LISTO
	
	cout<<"Ingrese el numero de cedula del Alumno a inscribir: ";
	cin>>cedula;
	Inscripcion(cedula);
*/

	
	
//	IMPRIMIR PENSUM LISTO
	
	cout<<"Ingrese el codigo de la carrera: ";
	cin>>codigo;
	ImprimirPensum(codigo);
	

	
/*	
//	CONSULTAR LISTO
//	FALTA AGREGAR ALUMNO NUEVO Y MATERIA NUEVA
	
	cout<<"1: Consultar alumno"<<endl;
	cout<<"2: Consultar Materia"<<endl;
	cout<<"Opcion: ";
	cin>>opcion;
	if(opcion==1)
		Consultar(true);
	else
		Consultar(false);
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
					
					if(maxUC<3 && opcion==2){
						cout<<"Debe tener al menos 3 unidades de credito inscritas"<<endl;
						opcion=3;
					}
					
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
		pensum.close();
		exit(1);
	}
	else{
		gotoxy(1,2);
		cout<<"Semestre";
		gotoxy(12,2);
		cout<<"Codigo";
		gotoxy(35,2);
		cout<<"Materia";
		gotoxy(55,2);
		cout<<"Unidades de Credito";
		
		while(true){
			Materia mat;
			pensum.read((char*)&mat,sizeof(Materia));
			if(pensum.eof()) break;
			gotoxy(5,y);
			cout<<mat.numSemestre;
			gotoxy(12,y);
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
				break;
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

void ReporteInscripcion(int cedula){	
	system("cls");
	
	char archivo[10];
	
	int codMaterias;
	int aux=1;
	int salto=100;
	
	fstream inscripcion,alumno,carrera,materia;
	
	Alumnos a;
	Carrera c;
	Materia m;
	Inscritos i;
	
	alumno.open("Alumnos.dat",ios::binary | ios::in);
	while(true){
		alumno.read((char*)&a,sizeof(Alumnos));
		if(alumno.eof()){
			cout<<".....Alumno no encontrado.....";
			getch();
			break;
		}
		if(a.cedula == cedula){
			cout<<"Reporte de Inscripcion"<<endl<<endl;
			cout<<"Cedula: "<<a.cedula<<endl;
			cout<<"Nombre: "<<a.nombre<<endl;
			carrera.open("Carreras.dat",ios::binary | ios::in);
			while(true){
				carrera.read((char*)&c,sizeof(Carrera));
				if(carrera.eof()){
					cout<<"Carrera: NULL"<<endl;
					break;
				}
				if(c.codigoCarrera == a.codigoCarrera){
					cout<<"Carrera: "<<c.nombreCarrera<<endl;
					break;
				}
			}
			carrera.close();
			inscripcion.open("Inscritos.dat",ios::binary | ios::in);
			while(true){
				inscripcion.read((char*)&i,sizeof(Inscritos));
				if(inscripcion.eof() || inscripcion==NULL){
					cout<<"Total UC Inscritas: NULL";
					break;
				}
				if(a.cedula == i.cedula){
					cout<<"Codigo de materias: "<<i.codMaterias<<endl;
					cout<<"Total UC Inscritas: "<<i.totalUC<<endl;
					codMaterias = atoi(i.codMaterias);
					cout<<endl<<"Materias Inscritas"<<endl<<endl;
					itoa(a.codigoCarrera,archivo,10);
					strcat(archivo,".dat");
					while(true){
						if(aux!=0){
							aux=codMaterias%salto;
							codMaterias/=salto;
						}
						if(aux==0)
							break;
						materia.open(archivo,ios::binary | ios::in);
						while(true){
							materia.read((char*)&m,sizeof(Materia));
							if(materia.eof()){
								cout<<"Codigo: NULL"<<endl;
								cout<<"Materia: NULL"<<endl;
								cout<<"UC: NULL"<<endl;
								cout<<"Semestre: NULL"<<endl<<endl;
								break;
							}
							if(m.codMateria%100 == aux){
								cout<<"Codigo: "<<m.codMateria<<endl;
								cout<<"Materia: "<<m.nomMareria<<endl;
								cout<<"UC: "<<m.UC<<endl;
								cout<<"Semestre: "<<m.numSemestre<<endl<<endl;
								break;
							}
						}
						materia.close();
					}
					break;
				}
			}
			inscripcion.close();
			break;
		}
	}
	alumno.close();

}

void InscripcionMateria(int codigo){

	int codCarrera;
	char file[11];
	int codMaterias;
	int aux;
	
	fstream ins,mat,alum;

	Inscritos i;
	Materia m;
	Alumnos a;
	
	codCarrera = codigo/100;
	itoa(codCarrera,file,10);
	strcat(file,".dat");
	
	mat.open(file,ios::binary | ios::in);
	if(mat.fail()){
		cout<<".....ERROR AL ABRIR EL ARCHIVO.....";
		mat.close();
		getch();
	}
	else
		while(true){
			mat.read((char*)&m,sizeof(Materia));
			if(mat.eof()){
				cout<<".....MATERIA SIN ALUMNOS INSCRITOS....."<<endl;
				getch();
				break;
			}
			if(m.codMateria == codigo){
				cout<<"Alumnos que inscribieron la materia "<<m.nomMareria<<endl<<endl;
				ins.open("Inscritos.dat",ios::binary | ios::in);
				while(true){
					ins.read((char*)&i,sizeof(Inscritos));
					if(ins.eof()) break;
					codMaterias = atoi(i.codMaterias);
					aux=1;
					while(true){
						if(aux!=0){
							aux=codMaterias%100;
							codMaterias/=100;
						}
						if(aux==0)
							break;
						if(m.codMateria%100 == aux){
							alum.open("Alumnos.dat",ios::binary | ios::in);
							while(true){
								alum.read((char*)&a,sizeof(Alumnos));
								if(alum.eof()){
									cout<<"Cedula: NULL"<<endl;
									cout<<"Nombre: NULL"<<endl<<endl;
									break;
								}
								if(i.cedula == a.cedula && a.codigoCarrera == m.codMateria/100){
									cout<<"Cedula: "<<a.cedula<<endl;
									cout<<"Nombre: "<<a.nombre<<endl<<endl;
									break;
								}
							}
							alum.close();
						}
					}
				}
				ins.close();
			break;
			}
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
