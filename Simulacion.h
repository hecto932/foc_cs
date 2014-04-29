#ifndef _SIMULACION_
#define _SIMULACION_

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

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

void Simulacion::ejecutar( double a, double b, double replicas, double tTrans, double tSim)
{
	//DECLARAMOS LAS VARIABLES NECESARIAS PARA LA SIMULACION
 	int Nt=0;//Cantidad actual de clientes en sistema
 	int servidores=0;//Usado para llevar el control de los servidores disponibles
 	float tLlegada=0;//Usado para calcular el Siguiente tiempo entre llegadas -- LOCALES --
 	float tSalida=0;//Usado para calcular el Siguiente tiempo entre salidas    -- LOCALES -- 
 	double tiempo=0;//Usado para tiempo t de simulacion
 	//DECLARAMOS UNA VARIABLE ASISTENCIAL PARA ASIGNAR LOS NUMEROS ALEATORIOS GENERADOS EN CADA ITERACION DE LA SIMULACION
 	float aleatorio=0;//Llegada
 	//DECLARAMOS LA VARIABLE NECESARIA PARA CONOCER LOS TIEMPOS DE SALIDA PARA CADA SERVIDOR
 	float salidasServ[4] = {0,0,0,0};//Cada posicion representa el tiempo de salida para el servidor N
 	//DECLARAMOS UN BOOLEANO QUE NOS PERMITA CONOCER LOS EVENTOS SIGUIENTES EN LA SIMULACION, DONDE TRUE ES ENTRADA Y FALSE ES SALIDA
 	bool sigEven=true;
 	//---------------------------------------INICIO DE LA SIMULACION--------------------------------------
 	cout << "| tiempo t (m)\t| N(t)\t| r_llegada\t\t| t_llegada\t\t| r_servicio\t| t_servicio\t| s_llegada\t\t| s_salida\t\t| s_evento" << endl;
 	cout << "----------------------------------------------------------------------------------------------------------------------------------" << endl;
	srand (static_cast <unsigned> (time(0)));//Inicializamos la semilla aleatoria

	aleatorio = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
 	tLlegada = (-a)*(log(aleatorio));
 	cout << "| " << tiempo <<"\t\t| " << Nt << "\t| " << aleatorio <<"\t\t| " << tLlegada << "\t\t|------\t\t| -------\t\t| " << (tiempo + tLlegada) << "\t\t| -------\t\t| Llegada" << endl;
 	tiempo+=tLlegada;

 	while(tiempo <= tSim)//Mientras haya tiempo para continuar la simulacion...
 	{
 		//COMPROBAMOS QUE OCURRIRA EN ESTA ITERACION
 		if (sigEven==true)//Esta ocurriendo una entrada
 		{
 			aleatorio = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
 			tLlegada = (-a)*(log(aleatorio));
 			if (servidores < 4)//Si al menos un servidor esta disponible, Podemos estimar un tiempo de salida para alguien que puede ser atendido en esta iteracion
 			{
 				aleatorio = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
 				tSalida = (-b)*(log(aleatorio));
 				/*
				OIDO AL TAMBOR: Aqui debemos realizar una busqueda para saber cual servidor esta disponible para recibir a una entrada y guardar en la posicion correspondiente a ese vector
				el tiempo en el que esa salida ocurrira

				salidasServ[servidores]=tSalida;

 				*/
 				servidores+=1;
 			}
 		}
 		else//Esta ocurriendo una salida
 		{
 			/*
 			OIDO AL TAMBOR: Aqui debemos realizar un ciclo para saber cual servidor estara disponible para albergar el tiempo que tomara en salir el siguiente cliente a ser atendido
 			
 			salidasServ[servidores]=0;
 			servidores-=1
			aleatorio = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			tSalida = (-b)*(log(aleatorio));
			salidasServ[servidores]=tSalida;
 			*/
 		}
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
 	L=0;
	Lq=0;
	W=0;
	Wq=0;
	X=0;
}

#endif