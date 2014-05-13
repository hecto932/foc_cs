#ifndef _MODELO_
#define _MODELO_

#include <iostream>
#include <cstdio> 
#include <fstream>
#include <string>

#include "Teoria.h"
#include "Simulacion.h"

using namespace std;

class Modelo 
{
	private:
		double lambda;//Parámetro a
		double miu;//Parámetro b
		long long int cr;//Cantidad de réplicas
		long long int tt;//Tiempo de transición
		long long int ts;//Tiempo de simulación
		Teoria T;
		Simulacion S;

	public:
		Modelo();
		Modelo(double l, double m, long long int pcr, long long int ptt, long long int pts);

		//SOBRECARGAS
		friend ostream& operator << (ostream& out,const Modelo& m);
		void leer_modelo(ifstream& in_modelo);

		//METODOS
		void resolver_teoria();
		void realizar_simulacion(int i, ofstream& out_simulacion);
		void show_results(int i, ofstream& out_performance);

		void limpiar();
};

//CONSTRUCTOR
Modelo::Modelo()
{
	lambda 	= 0;
	miu 	= 0;
	cr 		= 0;
	tt 		= 0;
	ts 		= 0;
}

//CONSTRUCTOR CON PARAMETROS
Modelo::Modelo(double l, double m, long long int pcr, long long int ptt, long long int pts)
{
	lambda 	= l;
	miu 	= m;
	cr 		= pcr;
	tt 		= ptt;
	ts 		= pts;
}

ostream& operator << (ostream& out,const Modelo& m)
{
	out << "Lambda: " << m.lambda << endl;
	out << "miu: " << m.miu << endl;
	out << "Cantidad de replicas" << m.cr << endl;
	out << "Tiempo de transición: " << m.tt << endl;
	out << "Tiempo de simulación: " << m.ts << endl;
 
	return out;
}

void Modelo::leer_modelo(ifstream& in_modelo)
{
	in_modelo >> lambda >> miu >> cr >> tt >> ts;
}

void Modelo::resolver_teoria()
{
	T.Inicializar(1/lambda,1/miu);
	T.Resolver(1/lambda,1/miu);
}

void Modelo::realizar_simulacion(int i, ofstream& out_simulacion)
{
	S.ejecutar(i,out_simulacion,lambda,miu,cr,tt,ts);
}

void Modelo::show_results(int i, ofstream& out_performance)
{
	//ESCRIBIMOS LOS RESULTADOS EN EL ARCHIVO DE SALIDA
	out_performance << "Modelo " << i+1 << ":" << endl;
	out_performance << "\t\t\t" << "Utilización" << "\t\t" << "L" << "\t\t"  << "Lq" << "\t\t" << "W" << "\t\t" << "Wq" << endl;
	out_performance << "Simulación" << "\t"  << S.Get_X() << "\t\t\t"  << S.Get_L() << "\t"  << S.Get_Lq() << "\t"  << S.Get_W() << "\t"  << S.Get_Wq() << endl;
	out_performance << "Teórico" << "\t\t"  << T.Get_X() << "\t\t\t"  << T.Get_L() << "\t"  << T.Get_Lq() << "\t"  << T.Get_W() << "\t"  << T.Get_Wq() << endl;
	out_performance << endl;
}

void Modelo::limpiar()
{
	lambda 	= 0;
	miu 	= 0;
	cr 		= 0;
	tt 		= 0;
	ts 		= 0;
	T.limpiar();
}

#endif