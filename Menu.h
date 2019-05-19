#ifndef MENU_H
#define MENU_H

class Menu
{
	public:
		void menu();
		void Agregar(bool);
		void Inscripcion(int);
		void ImprimirPensum(int);
		void ListaAlumnos();
		void Consultar(bool);
		void ReporteInscripcion(int);
		void InscripcionMateria(int);
		void gotoxy(int,int);
		void marco(char*,int);
};

#endif
