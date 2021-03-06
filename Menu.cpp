#include "Menu.h"
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


void Menu::menu(){
	int opcion=-1;
	while(opcion<0 || opcion>9){
	system("cls");
	cout<<".....BIENVENIDO....."<<endl<<endl;
	cout<<"1. Inscribir Alumno"<<endl;
	cout<<"2. Consultar Alumno"<<endl;
	cout<<"3. Consultar Materia"<<endl;
	cout<<"4. Reporte de Inscripcion de Alumnos"<<endl;
	cout<<"5. Reporte de Inscritos en Materia"<<endl;
	cout<<"6. Registrar Alumno a data"<<endl;
	cout<<"7. Registrar Materia a data"<<endl;
	cout<<"8. Imprimir Pensum"<<endl;
	cout<<"9. Imprimir Lista de Alumnos"<<endl;
	cout<<"0. SALIR"<<endl<<endl;
	cout<<"OPCION: ";
	cin>>opcion;
	}
	
	switch(opcion){
		
		case 1:{
			system("cls");
			int cedula;
			cout<<"Ingrese la cedula del alumno a inscribir: ";
			cin>>cedula;
			Inscripcion(cedula);
			break;
		}
		case 2:{
			system("cls");
			Consultar(true);
			break;
		}
		case 3:{
			system("cls");
			Consultar(false);
			break;
		}
		case 4:{
			system("cls");
			int cedula;
			cout<<"Ingrese la cedula del alumno: ";
			cin>>cedula;
			ReporteInscripcion(cedula);
			break;
		}
		case 5:{
			system("cls");
			int codigo;
			cout<<"Ingrese el codigo de la materia (6 Digitos): ";
			cin>>codigo;
			InscripcionMateria(codigo);
			break;
		}
		case 6:{
			system("cls");
			Agregar(true);
			break;
		}
		case 7:{
			system("cls");
			Agregar(false);
			break;
		}
		case 8:{
			int codigo;
			system("cls");
			cout<<"Ingrese el codigo de la carrera: ";
			cin>>codigo;
			ImprimirPensum(codigo);
			break;
		}
		case 9:{
			system("cls");
			ListaAlumnos();
			break;
		}
		default:{
			exit(1);
			break;
		}
	}
}

void Menu::Agregar(bool alumno ){
	
	if(alumno){
		fstream file1;
		
		Alumnos a;		
		file1.open("Alumnos.dat",ios::binary | ios::app);
		
		cout<<"ingrese la cedula del alumno a inscribir"<<endl;
		cin>>a.cedula;
		cout<<"ingrese el nombre del alumno"<<endl;
		fflush(stdin);
		gets(a.nombre);
		cout<<"ingrese el codigo de la carrera del alumno"<<endl;
		fflush(stdin);
		cin>>a.codigoCarrera;
		file1.write((char*)&a,sizeof(Alumnos));
		file1.close();
		cout<<endl<<"Alumno agregado con Exito . . ."<<endl<<endl;
		system("pause");
	}else{
		int codigo;
		Materia m;
		fstream file2;
		fstream file3;
		int codMateria;
		char aux[30];
		char aux2[30];
		char aux3[30];
		char cod[30];
		strcpy(cod,"");
		
		file2.open("Carreras.dat", ios::binary | ios::in);		
		cout<<"ingrese el codigo de la carrera: ";
		cin>>codigo;
		itoa(codigo,aux,10);
		itoa(codigo,aux2,10);
		strcat(aux,".dat");
		while(true){
			Carrera c;
			
			file2.read((char*)&c,sizeof(Carrera));
			if(file2.eof()){
				cout<<endl<<"Esta carrera no existe, no se puede inscribir la materia . . ."<<endl;
				system("pause");
				break;
			}
			if(c.codigoCarrera == codigo){
				file3.open(aux,ios::binary | ios::app);
				cout<<"ingrese el numero de semestre de la materia: ";
				cin>>m.numSemestre;
				cout<<"ingrese el codigo de la materia (2 Digitos): ";
				cin>>codMateria;
				itoa(codMateria,aux3,10);
				strcat(cod,aux2);
				strcat(cod,aux3);
				m.codMateria = atoi(cod);
				cout<<"ingrese el nombre de la materia: ";
				fflush(stdin);
				cin>>m.nomMareria;
				cout<<"ingrese el numero de UC: ";
				fflush(stdin);
				cin>>m.UC;
								
				file3.write((char*)&m,sizeof(Materia));
				file3.close();
				cout<<endl<<"Materia agregada con Exito . . ."<<endl;
				system("pause");
				break;
			}
		}
		file2.close();		
	}
	menu();	
}

void Menu::Inscripcion(int cedula){
	
	int materia;
	char mat[3];
	char cod[10];
	int maxUC=0;
	
	int opcion;
	
	fstream alumnos;
	fstream materias;
	fstream inscritos;
	
	alumnos.open("Alumnos.dat",ios::binary | ios::in);
	
	while(true){
		Alumnos a;
		alumnos.read((char*)&a,sizeof(Alumnos));
		if(alumnos.eof()){
			cout<<endl<<"Alumno no encontrado . . ."<<endl;
			system("pause");
			break;
		}		
		if(a.cedula == cedula){
			Inscritos inscrito;
			while(true){
				cout<<endl<<"Ingrese el codigo de la materia a inscribir (2 Digitos): ";
				strcpy(mat,"");
				cin>>materia;
				itoa(a.codigoCarrera,cod,10);
				strcat(cod, ".dat");
				materias.open(cod,ios::binary | ios::in);
				while(true){
					Materia m;
					materias.read((char*)&m,sizeof(Materia));				
					if(materias.eof()){
						cout<<endl<<"Materia no encontrada . . ."<<endl;
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
							cout<<endl<<"Limite de UC Excedido . . ."<<endl;
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
						cout<<"Debe tener al menos 3 unidades de credito inscritas . . ."<<endl;
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
					cout<<endl<<"Inscripcion realizada Exitosamente . . ."<<endl;
					system("pause");
					break;
				}
			}
			break;
		}
	}
	alumnos.close();
	menu();	
}

void Menu::ImprimirPensum(int codigo){
	
	system("cls");
	
	fstream pensum;
	int y=4;
	
	char cod[10];
	
	itoa(codigo,cod,10);
	strcat(cod, ".dat");
	pensum.open(cod,ios::binary | ios::in);
	if(pensum.fail())
	{
		cout<<"Carrera NO encontrada . . ."<<endl;
		system("pause");
		pensum.close();
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
		marco(cod,2);
		system("pause");
	}
	pensum.close();
	menu();
}

void Menu::Consultar(bool alumno ){
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
				cout<<endl<<"Alumno no encontrado . . ."<<endl;
				system("pause");
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
				if(insc.fail()){
					cout<<endl;
					system("pause");
					break;
				}
				while(true){
					insc.read((char*)&i,sizeof(Inscritos));
					if(insc.eof()){
						cout<<"Codigo de Materias: NULL"<<endl;
						cout<<"Total UC Inscritas: NULL"<<endl<<endl;
						system("pause");
						break;
					}
					if(a.cedula == i.cedula){
						cout<<"Codigo de Materias: "<<i.codMaterias<<endl;
						cout<<"Total UC Inscritas: "<<i.totalUC<<endl<<endl;
						system("pause");
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
		
		cout<<"ingrese el codigo de la materia (6 Digitos): ";
		cin>>codigo;
		codigoAux=codigo;
		codigoAux/=100;
		itoa(codigoAux,aux,10);
		strcat(aux,".dat");
		
		mat.open(aux,ios::binary | ios::in);
		if(mat.fail()){
			cout<<endl<<"Materia no Encontrada . . ."<<endl;
			mat.close();
			system("pause");
		}
		else{
			while(true){
				Materia m;
				mat.read((char*)&m,sizeof(Materia));
				if(mat.eof()) break;
				if(m.codMateria==codigo){
					cout<<endl<<"Materia: "<<m.nomMareria<<endl;
					cout<<"Semestre: "<<m.numSemestre<<endl;
					cout<<"UC: "<<m.UC<<endl;
					car.open("Carreras.dat",ios::binary | ios::in);
					while(true){
						Carrera c;
						car.read((char*)&c,sizeof(Carrera));
						if(car.eof()){
							cout<<"Carrera: NULL"<<endl<<endl;
							system("pause");
							break;
						}
						if(c.codigoCarrera == codigo/100){
							cout<<"Carrera: "<<c.nombreCarrera<<endl<<endl;
							system("pause");
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
	menu();	
}

void Menu::ReporteInscripcion(int cedula){	
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
			cout<<"Alumno no encontrado . . ."<<endl;
			system("pause");
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
					cout<<"Total UC Inscritas: NULL"<<endl<<endl;
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
			system("pause");
			break;
		}
	}
	alumno.close();
	menu();
}

void Menu::InscripcionMateria(int codigo){

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
		cout<<"CARRERA NO ENCONTRADA . . ."<<endl;
		mat.close();
		system("pause");
	}
	else
		while(true){
			mat.read((char*)&m,sizeof(Materia));
			if(mat.eof()){
				cout<<"MATERIA NO ENCONTRADA . . ."<<endl;
				system("pause");
				break;
			}
			if(m.codMateria == codigo){
				cout<<"Alumnos que inscribieron la materia \""<<m.nomMareria<<"\""<<endl<<endl;
				ins.open("Inscritos.dat",ios::binary | ios::in);
				if(ins.fail()){
					cout<<"MATERIA SIN ALUMNOS INSCRITOS . . ."<<endl;
					system("pause");
					break;
				}
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
			system("pause");
			break;
			}
		}
		mat.close();
	menu();
}

void Menu::ListaAlumnos(){
	
	system("cls");
	
	fstream alumnos;
	char salir;
	int y=4;
	
	alumnos.open("Alumnos.dat",ios::binary | ios::in);
	if(alumnos.fail())
	{
		cout<<"ERROR AL ABRIR EL ARCHIVO ALUMNOS . . .";
		system("pause");
		alumnos.close();
	}
	else{
		gotoxy(1,2);
		cout<<"cedula";
		gotoxy(12,2);
		cout<<"Codigo";
		gotoxy(30,2);
		cout<<"Nombre";
		
		while(true){
			Alumnos alum;
			alumnos.read((char*)&alum,sizeof(Alumnos));
			if(alumnos.eof()){
				marco("Alumnos.dat",1);
				system("pause");
				break;
			}
			gotoxy(2,y);
			cout<<alum.cedula;
			gotoxy(13,y);
			cout<<alum.codigoCarrera;
			gotoxy(22,y);
			cout<<alum.nombre;
			y++;
			if(y==50){
				marco("Alumnos.dat",1);
				gotoxy(0,y);
				cout<<"  .\n  .\n  ."<<endl<<endl<<"Pulse 0 para Volver al menu"<<endl;
				fflush(stdin);
				salir = getch();
				if(salir == '0')
					break;
				system("cls");
				
				y=4;
				
				gotoxy(1,2);
				cout<<"cedula";
				gotoxy(12,2);
				cout<<"Codigo";
				gotoxy(30,2);
				cout<<"Nombre";
			}
		}
		alumnos.close();
	}
	menu();	
}

void Menu::marco(char *archivo, int caso){
	
	fstream file;
	int cont=0;
	
	Materia m;
	Alumnos a;
	
	if(caso==2){	
		file.open(archivo,ios::binary | ios::in);
		while(true){
			file.read((char*)&m,sizeof(Materia));
			if(file.eof()) break;
			cont++;
		}
	
		for(int i=0;i<cont+2;i++){
			gotoxy(0,i+2);
			cout<<"|";
		}
		for(int i=0;i<cont+2;i++){
			gotoxy(10,i+2);
			cout<<"|";
		}
		for(int i=0;i<cont+2;i++){
			gotoxy(20,i+2);
			cout<<"|";
		}
		for(int i=0;i<cont+2;i++){
			gotoxy(54,i+2);
			cout<<"|";
		}
		for(int i=0;i<cont+2;i++){
			gotoxy(74,i+2);
			cout<<"|";
		}
		gotoxy(0,cont+5);
	}
	else{
		file.open(archivo,ios::binary | ios::in);
		while(true){
			file.read((char*)&a,sizeof(Alumnos));
			if(file.eof()) break;
			cont++;
			if(cont==46) break;
		}
		for(int i=0;i<cont+2;i++){
			gotoxy(0,i+2);
			cout<<"|";
		}
		for(int i=0;i<cont+2;i++){
			gotoxy(10,i+2);
			cout<<"|";
		}
		for(int i=0;i<cont+2;i++){
			gotoxy(20,i+2);
			cout<<"|";
		}
		for(int i=0;i<cont+2;i++){
			gotoxy(44,i+2);
			cout<<"|";
		}
		gotoxy(0,cont+4);
	}
	
}

void Menu::gotoxy(int x,int y){
	HANDLE hcon = GetStdHandle (STD_OUTPUT_HANDLE);
	COORD dwpos;
	dwpos.X=x;
	dwpos.Y=y;
	SetConsoleCursorPosition(hcon,dwpos);
}
