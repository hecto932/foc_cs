#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "Simulacion.h"

using namespace std;

//CONSTRUCTOR
Simulacion::Simulacion()
{
	Nt=0;
 	servidores=0;
 	tLlegada=0;
 	tSalida=0;
 	tiempo=0;
 	aleatorio=0;
 	L=0;
	Lq=0;
	W=0;
	Wq=0;
	X=0;
}

void Simulacion::ejecutar(int numero_sim, double a, double b, double replicas, double tTrans, double tSim)
{
 	srand (static_cast <unsigned> (time(0)));//Inicializamos la semilla aleatoria
 	while(tiempo <= tSim)//Mientras haya tiempo para simulacion
 	{
 		//GENERAMOS LOS NUMEROS ALEATORIOS DE ACUERDO A LOS ESTADOS PARA LUEGO REALIZAR LAS OPERACIONES PERTINENTES
 		//Por evento de llegada
 		aleatorio = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
 		tLlegada = (-a)*(log(aleatorio));
 		//por evento de servicio
 		aleatorio = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
 		tSalida = (-b)*(log(aleatorio));
 		//AHORA EFECTUAMOS LAS COMPROBACIONES LÓGICAS PARA LA SIGUIENTE ITERACION
 	}
}

//OBSERVADORES
double Simulacion::Get_L()
{
	return L;
}
double Simulacion::Get_Lq()
{
	return Lq;
}
double Simulacion::Get_W()
{
	return W;
}
double Simulacion::Get_Wq()
{
	return Wq;
}
double Simulacion::Get_X()
{
	return X;
}

void Simulacion::limpiar()
{
	Nt=0;
 	servidores=0;
 	tLlegada=0;
 	tSalida=0;
 	tiempo=0;
 	aleatorio=0;
 	L=0;
	Lq=0;
	W=0;
	Wq=0;
	X=0;
}