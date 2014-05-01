#ifndef _SIMULACION_
#define _SIMULACION_

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <list>

using namespace std;

class Simulacion 
{

	private:
	 	//DECLARAMOS LAS VARIABLES NECESARIAS PARA LA COMPARACION ENTRE LOS VALORES DE SIMULACION Y TEORIA
	 	double L;
		double Lq;
		double W;
		double Wq;
		double X;
	public:
	 	//CONSTRUCTOR
	 	Simulacion();
	 	//EJECUCIÓN DE LA SIMULACIÓN
	 	void ejecutar(double a, double b, double replicas, double tTrans, double tSim);
	 	//OBSERVADORES
	 	double Get_L();
		double Get_Lq();
		double Get_W();
		double Get_Wq();
		double Get_X();
		//LIMPIAR
	 	void limpiar();

};

//CONSTRUCTOR
Simulacion::Simulacion()
{
 	L=0;
	Lq=0;
	W=0;
	Wq=0;
	X=0;
}

//FUNCION QUE NOS AYUDA A ENCONTRAR LA POSICION PARA ALMACENAR tSalida Y CONOCER EL SIGUIENTE EVENTO
bool Simulacion::comprobarSig (list<double> &salidasServ, double &salidaCercana, double tiempo, double tSalida, double entradaCercana, double tSim)
{
	/*En esta funcion se realizan las siguientes tareas
	1.- Buscar cual posicion de la lista esta disponible para almacenar (tSalida + tiempo)
	2.- Comprobar cual salida en la lista ocurrirá primero y asignarle ese valor a salidaCercana
	3.- Si (entradaCercana < salidaCercana) Y ((entradaCercana + tiempo) < tSim) retorna true (siguiente evento es entrada)
		sino retorna false (siguiente evento es salida).
	*/
}

void Simulacion::ejecutar( double a, double b, double replicas, double tTrans, double tSim)
{
	//DECLARAMOS LAS VARIABLES NECESARIAS PARA LA SIMULACION
 	int Nt=0;//Cantidad actual de clientes en sistema (en cola y en servidores)
 	float tLlegada=0;//Usado para calcular el Siguiente tiempo entre llegadas
 	float tSalida=0;//Usado para calcular el Siguiente tiempo entre salidas
 	float salidaCercana=0;//Usado para conocer localmente cual es la menor salida que ocurrirá
 	float entradaCercana=0;//Usado para conocer localmente cuando ocurrirá la siguiente entrada
 	double tiempo=0;//Usado para tiempo t de simulacion
 	//DECLARAMOS UNA VARIABLE ASISTENCIAL PARA ASIGNAR LOS NUMEROS ALEATORIOS GENERADOS EN CADA ITERACION DE LA SIMULACION
 	float aleatorio=0;//Llegada
 	//DECLARAMOS LA LISTA NECESARIA PARA CONOCER LOS TIEMPOS DE SALIDA PARA CADA SERVIDOR
 	list<double> salidasServ;//Donde la primera posicion corresponde al servidor 1 y asi para los demás
 	//DECLARAMOS UN BOOLEANO QUE NOS PERMITA CONOCER LOS EVENTOS SIGUIENTES EN LA SIMULACION, DONDE true ES ENTRADA Y false ES SALIDA
 	bool sigEven=true;
 	//---------------------------------------INICIO DE LA SIMULACION--------------------------------------
 	//Primera línea
 	//cout << "| tiempo t (m)\t| N(t)\t| r_llegada\t\t| t_llegada\t\t| r_servicio\t| t_servicio\t| s_llegada\t\t| s_salida\t\t| s_evento" << endl;
 	//cout << "----------------------------------------------------------------------------------------------------------------------------------" << endl;
	srand (static_cast <unsigned> (time(0)));//Inicializamos la semilla aleatoria

	aleatorio = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
 	tLlegada = (-a)*(log(aleatorio));
 	cout << "| " << tiempo <<"\t\t| " << Nt << "\t| " << aleatorio <<"\t\t| " << tLlegada << "\t\t|------\t\t| -------\t\t| " << (tiempo + tLlegada) << "\t\t| -------\t\t| Llegada" << endl;
 	tiempo+=tLlegada;

 	while((tiempo <= tSim) || (Nt > 0))//Mientras haya tiempo para continuar la simulacion O queden personas en sistema
 	{
 		//COMPROBAMOS QUE OCURRIRA EN ESTA ITERACION
 		if (sigEven==true)//Esta ocurriendo una entrada
 		{
 			Nt+=1;
 			aleatorio = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
 			tLlegada = (-a)*(log(aleatorio));
 			entradaCercana = tiempo + tLlegada;
 			if (Nt <= 4)//Si al menos un servidor esta disponible, Podemos estimar un tiempo de servicio para esta entrada
 			{
 				aleatorio = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
 				tSalida = (-b)*(log(aleatorio));
 				/*
				OIDO AL TAMBOR: Aqui debemos realizar una busqueda para saber cual servidor esta disponible para recibir a una entrada y guardar en la posicion correspondiente a ese vector
				el tiempo en el que esa salida ocurrira
 				*/
 				sigEvent = comprobarSig(salidasServ,salidaCercana,tiempo,tSalida,entradaCercana,tSim);
 			}
 		}
 		else//Esta ocurriendo una salida
 		{
 			Nt-=1;
 			aleatorio = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
 			tSalida = (-b)*(log(aleatorio));
 			/*
			OIDO AL TAMBOR: Aqui debemos realizar una busqueda para saber cual servidor esta disponible para recibir a una entrada y guardar en la posicion correspondiente a ese vector
			el tiempo en el que esa salida ocurrira
 			*/
 			sigEvent = comprobarSig(salidasServ,salidaCercana,tiempo,tSalida,entradaCercana,tSim);
 		}
 		//ANTES DE LA SIGUIENTE ITERACION, DEBEMOS IMPRIMIR LA SALIDA CORRESPONDIENTE A ESTA

 		//LUEGO INCREMENTAMOS tiempo DE ACUERDO AL SIGUIENTE EVENTO
 		if (sigEvent)
 			tiempo+=entradaCercana;
 		else
 			tiempo+=salidaCercana;
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
 	L=0;
	Lq=0;
	W=0;
	Wq=0;
	X=0;
}

/*ANOTACIONES IMPORTANTES:
 		GENERACION DE NUMEROS ALEATORIOS
 		//Inicializamos la semilla aleatoria, POR CADA SIMULACION
 		srand (static_cast <unsigned> (time(0)));
 		//Por evento de llegada
 		aleatorio = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
 		tLlegada = (-a)*(log(aleatorio));
 		//por evento de servicio
 		aleatorio = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
 		tSalida = (-b)*(log(aleatorio));
*/

#endif