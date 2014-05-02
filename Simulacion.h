#ifndef _SIMULACION_
#define _SIMULACION_

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <list>
#include <vector>
#include <algorithm>

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
	 	//DETECTOR DE ESTADOS DENTRO DE LA SIMULACION
	 	bool comprobarSig_estado(vector<double> &t_salidas, double &siguiente_salida, double siguiente_entrada, double ts, int Nt);
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

//COMPARE DEL MIN_ELEMENT
bool compare(double i, double j)
{
	return (i<j && i!=0 && j!=0);
}

//FUNCION QUE NOS AYUDA A ENCONTRAR LA POSICION PARA ALMACENAR siguiente_salida EN t_salidas Y CONOCER EL SIGUIENTE EVENTO
bool Simulacion::comprobarSig_estado (vector<double> &t_salidas, double &siguiente_salida, double siguiente_entrada, double ts, int Nt)
{
	int min_position = min_element(t_salidas.begin(),t_salidas.end(), compare)-t_salidas.begin();	//OBTENGO LA POSICION DEL MENOR TIEMPO
	t_salidas[min_position] = siguiente_salida;													//REGISTRO EL NUEVO TIEMPO DE SALIDA
	siguiente_salida = *min_element(t_salidas.begin(),t_salidas.end(), compare);				//OBTENGO EL MENOR TIEMPO REGISTRADO, SI TODOS SON 0, SE TOMA 0
		//SI PRIMERO OCURRE UNA ENTRADA Y HAY SUFICIENTE TIEMPO PARA ELLA RETORNAR
	if (siguiente_salida != 0)
	{
		if (siguiente_entrada != 0)
			return (siguiente_entrada < siguiente_salida);
	}
	else
	{
		if (siguiente_entrada == 0)
			return false;
		else
			return true;
	}
}

void Simulacion::ejecutar( double a, double b, double cr, double tt, double ts)
{
	srand (static_cast <unsigned> (time(0)));	//INICIALIZANDO UNA SEMILLA RANDOM

	int Nt = 0; 					//CANTIDAD DE CLIENTES EN EL SISTEMA
	double r; 						//NUMERO ALEATORIO
	double t_llegada;				//TIEMPO PARA LA SIGUIENTE LLEGADA
	double t_servicio; 				//TIEMPO PARA EL SIGUIENTE SERVICIO
	double s_llegada;				//TIEMPO EN SIMULACION PARA LA SIGUIENTE LLEGADA
	double s_salida;				//TIEMPO EN SIMULACION PARA LA SIGUIENTE SALIDA
	double tiempo = 0;				//TIEMPO ACTUAL DE LA SIMULACION EN CADA ITERACION
	bool s_evento;					//SIGUIENTE EVENTO A OCURRIR true: entrada, false: salida
	vector<double> t_salidas(4,0);	//ALMACENADOR DE LOS TIEMPOS DE SALIDA DE CADA SERVIDOR

	//1ERA ITERACION
	r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	t_llegada = -a*log(r);
	s_llegada = t_llegada;
	s_evento = true;
	cout << tiempo << "\t" << Nt << "\t" << r << "\t" << t_llegada << "\t0\t0\t" << s_llegada << "\t0\tLlegada" << endl;
	tiempo+=t_llegada;

	while( (tiempo<=ts) || (Nt>0) )
	{
		cout << tiempo << "\t";
		if(s_evento)//SIGUIENTE EVENTO ES UNA ENTRADA
		{
			++Nt;																//INCREMENTA LA CANTIDAD DE CLIENTES EN SISTEMA EN 1
			cout << Nt << "\t";
			r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);	//GENERAMOS UN NUMERO ALEATORIO PARA LA SIGUIENTE ENTRADA
			t_llegada = -a*log(r);												//ESTIMAMOS EL TIEMPO QUE PASARÀ PARA LA SIGUIENTE ENTRADA
			s_llegada = tiempo + t_llegada;										//ESTIMAMOS EL TIEMPO EN SIMULACION QUE OCURRIRA LA LLEGADA
			if (s_llegada >= ts)												//SI LA SIGUIENTE LLEGADA SOBREPASA EL TIEMPO DE LA SIMULACION, NO SE DEBE CONSIDERAR
			{
				r = 0;
				t_llegada = 0;
				s_llegada = 0;
			}
			cout << r << "\t" << t_llegada << "\t";
			if(Nt<=4)															//SI HAY SERVIDORES LIBRES PARA ATENDER UNA ENTRADA
			{
				r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);	//GENERAMOS UN NUMERO ALEATORIO PARA LA SALIDA
				cout << r << "\t";
				t_servicio = -b*log(r);												//ESTIMAMOS EL TIEMPO EN QUE OCURRIRA LA SALIDA
				cout << t_servicio << "\t";
				s_salida = tiempo + t_servicio;										//ESTIMAMOS EL TIEMPO EN SIMULACION QUE OCURRIRA LA SALIDA
				s_evento = comprobarSig_estado(t_salidas,s_salida,s_llegada,ts, Nt);	//LLAMAMOS A comprobarSig_estado
			}else{
				r = 0;
				t_servicio = 0;
			}
		}
		else //SIGUIENTE EVENTO ES UNA SALIDA, NO SE GENERA UNA ENTRADA EN ESTA ITERACION
		{
			--Nt;
			cout << Nt << "\t0\t0\t";
			if (Nt >=4)
			{
				r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);	//GENERAMOS UN NUMERO ALEATORIO PARA LA SALIDA
				t_servicio = -b*log(r);												//ESTIMAMOS EL TIEMPO EN QUE OCURRIRA LA SALIDA
				s_salida = tiempo + t_servicio;										//ESTIMAMOS EL TIEMPO EN SIMULACION QUE OCURRIRA LA SALIDA
			}else{
				r = 0;
				t_servicio = 0;
			}
			cout << r << "\t" << t_servicio << "\t";
			if (Nt < 4) s_salida = 0;
			s_evento = comprobarSig_estado(t_salidas,s_salida,s_llegada,ts, Nt);	//LLAMAMOS A comprobarSig_estado
		}
		cout << s_llegada << "\t" << s_salida << "\t";
		if (s_evento)
		{
			tiempo = s_llegada;	//SI LA SIGUIENTE ITERACIÓN SERÁ UNA ENTRADA, EL TIEMPO ACTUAL DE SIMULACIÓN INCREMENTA HASTA EL MOMENTO DE LA LLEGADA
			cout << "Llegada" << endl;
		}
		else
		{
			tiempo = s_salida;			//SI LA SIGUIENTE ITERACIÓN SERÁ UNA SALIDA, EL TIEMPO ACTUAL DE SIMULACIÓN INCREMENTA HASTA EL MOMENTO DE LA SALIDA
			cout << "Salida" << endl;
		}
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