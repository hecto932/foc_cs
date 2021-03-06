#ifndef _SIMULACION_
#define _SIMULACION_

#include <iostream>
#include <cstdlib>
#include <cstdio>
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
	 	void tiempos_vector(vector<double> &t_salidas, double &s_salida, double tiempo_sig_salida, double ts, bool estado_actual);
	 	bool comprobarSig_estado(vector<double> &t_salidas, double &siguiente_salida, double tiempo_sig_salida,double siguiente_entrada, double ts, bool estado_actual,int Nt);
	 	//EJECUCIÓN DE LA SIMULACIÓN
	 	void ejecutar(int i, ofstream& out_simulacion, double a, double b, double cr, double tt, double ts);
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

//FUNCION AUXILIAR PARA ENCONTRAR EL MENOR ELEMENTO DEL VECTOR DE SALIDAS
void Simulacion::tiempos_vector(vector<double> &t_salidas, double &s_salida, double tiempo_sig_salida, double ts, bool estado_actual)
{
	double aux = 0;
	int pos_menor=0;
	if (estado_actual && tiempo_sig_salida!=ts)//ESTADO ACTUAL ES ENTRADA Y HAY UN SERVIDOR DISPONIBLE
	{
		aux=t_salidas[0];
		pos_menor=0;
		for (int i=1;i<t_salidas.size();i++)
		{
			if (t_salidas[i]==0 || t_salidas[i]<aux)
			{
					aux=t_salidas[i];
					pos_menor=i;
			}
		}
		t_salidas[pos_menor] = tiempo_sig_salida;
	}
	else //ESTADO ACTUAL ES SALIDA
	{
		aux=0;
		pos_menor=0;
		for (int i=0;i<t_salidas.size();i++)
		{
			if (t_salidas[i]!=0 && t_salidas[i]==s_salida)
				pos_menor=i;
		}
		if (tiempo_sig_salida==ts)
			t_salidas[pos_menor]=0;
		else
			t_salidas[pos_menor]=tiempo_sig_salida;
	}
	//BUSCAR SIGUIENTE SALIDA MENOR
	aux = t_salidas[0];
	for (int i=1;i<t_salidas.size();i++)
	{
		if (t_salidas[i]!=0)
		{
			if (aux == 0)
			{
				aux=t_salidas[i];
			}
			else
			{
				if (t_salidas[i] < aux)
				{
					aux=t_salidas[i];
				}
			}
		}
	}
	s_salida = aux;
}

//FUNCION QUE NOS AYUDA A ENCONTRAR LA POSICION PARA ALMACENAR siguiente_salida EN t_salidas Y CONOCER EL SIGUIENTE EVENTO
bool Simulacion::comprobarSig_estado (vector<double> &t_salidas, double &siguiente_salida, double tiempo_sig_salida,double siguiente_entrada, double ts, bool estado_actual,int Nt)
{
	if (Nt<=4) tiempos_vector(t_salidas,siguiente_salida,tiempo_sig_salida,ts,estado_actual);
	if (siguiente_salida != 0)																	//SI PRIMERO OCURRE UNA ENTRADA Y HAY SUFICIENTE TIEMPO PARA ELLA RETORNAR
	{
		if (siguiente_entrada != 0)
			return (siguiente_entrada < siguiente_salida);
		else
			return false;
	}
	else
	{
		if (siguiente_entrada == 0)
			return false;
		else
			return true;
	}
}

void Simulacion::ejecutar(int i, ofstream& out_simulacion, double a, double b, double cr, double tt, double ts)
{
	srand (static_cast <unsigned> (time(0)));	//INICIALIZANDO UNA SEMILLA RANDOM

	int Nt = 0; 					//CANTIDAD DE CLIENTES EN EL SISTEMA
	double r; 						//NUMERO ALEATORIO
	double t_llegada;				//TIEMPO PARA LA SIGUIENTE LLEGADA
	double t_servicio; 				//TIEMPO PARA EL SIGUIENTE SERVICIO
	double s_llegada;				//TIEMPO EN SIMULACION PARA LA SIGUIENTE LLEGADA
	double s_salida = 0;			//TIEMPO EN SIMULACION PARA LA SIGUIENTE SALIDA
	double tiempo = 0;				//TIEMPO ACTUAL DE LA SIMULACION EN CADA ITERACION
	bool s_evento;					//SIGUIENTE EVENTO A OCURRIR true: entrada, false: salida
	vector<double> t_salidas(4,0);	//ALMACENADOR DE LOS TIEMPOS DE SALIDA DE CADA SERVIDOR

	//VARIABLES NECESARIAS PARA TOMA DE OBSERVACIONES
	bool tomar_obs = false; 				//INDICA SI SE PUEDEN TOMAR LAS OBSERVACIONES DE ACUERDO A SI SE CUMPLIÓ EL TIEMPO TRANSITORIO
	int clientes_atendidos = 0; 			//CUENTA DE LA CANTIDAD DE CLIENTES QUE INGRESAN AL SISTEMA
	long double compara_T = 0;				//AYUDA A ALMACENAR EN CADA ITERACION (tiempo_siguiente - tiempo_actual)
	long double suma_L = 0;					//AYUDA A ALMACENAR EN CADA ITERACION (suma_T * Nt) PARA EL CALCULO DE L
	long double suma_Lq = 0;				//AYUDA A ALMACENAR EN CADA ITERACION (suma_T * (Nt - 4)) PARA EL CALCULO DE Lq SII (Nt - 4) > 0
	long double tiempos_sal = 0;			//AYUDA A GUARDAR TODOS LOS TIEMPOS DE SALIDA
	long double tiempos_lle = 0;			//AYUDA A GUARDAR TODOS LOS TIEMPOS DE LLEGADA
	long double tiempos_ser = 0;			//AYUDA A GUARDAR TODOS LOS TIEMPOS DE SERVICIO
	long double tt_sim = 0;

	//VARIABLES AUXILIARES, POR REPLICA, PARA OBSERVACIONES FINALES
	long double aux_L=0;
	long double aux_Lq=0;
	long double aux_W=0;
	long double aux_Wq=0;
	long double aux_X=0;

	int replica = 1;

	while (replica <= cr)
	{
		//EJECUCION DE LA SIMULACION
		//1ERA ITERACION
		r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		t_llegada = -a*log(r);
		s_llegada = t_llegada;
		s_evento = true; 

		out_simulacion << "SIMULACION PARA EL MODELO - REPLICA #" << replica << endl << endl;
		out_simulacion << "Tiempo_t\tN(t)\tr_llegada\tste_llegas\tr_servicio \tst_servicio\ts_llegada\ts_salida\ts_evento" << endl;
		out_simulacion << tiempo << "\t" << Nt << "\t" << r << "\t" << t_llegada << "\t-------\t-------\t" << s_llegada << "\t-------\tLlegada" << endl;
		
		tiempo+=t_llegada;

		//RESTO DE LA SIMULACION
		while( tiempo!=0 && (tiempo<=ts || Nt>0))
		{
			//out_simulacion << "( ";
			if (tiempo >= tt) tomar_obs = true;			//SI YA PASO EL TIEMPO TRANSITORIO, SE PUEDE INICIAR LA TOMA DE OBSERVACIONES
			out_simulacion << tiempo << "\t";
			if(s_evento)//SIGUIENTE EVENTO ES UNA ENTRADA
			{
				//out_simulacion << "(1)";
				clientes_atendidos += 1;
				++Nt;																//INCREMENTA LA CANTIDAD DE CLIENTES EN SISTEMA EN 1
				out_simulacion << Nt << "\t";
				r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);	//GENERAMOS UN NUMERO ALEATORIO PARA LA SIGUIENTE ENTRADA
				t_llegada = -a*log(r);												//ESTIMAMOS EL TIEMPO QUE PASARÀ PARA LA SIGUIENTE ENTRADA
				s_llegada = tiempo + t_llegada;										//ESTIMAMOS EL TIEMPO EN SIMULACION QUE OCURRIRA LA LLEGADA
				if (s_llegada >= ts)//SI LA SIGUIENTE LLEGADA SOBREPASA EL TIEMPO DE LA SIMULACION, NO SE DEBE CONSIDERAR
				{
					s_llegada = 0;
				}
				out_simulacion << r << "\t" << t_llegada << "\t";
				if(Nt<=4)//SI HAY SERVIDORES LIBRES PARA ATENDER UNA ENTRADA
				{
					r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);	//GENERAMOS UN NUMERO ALEATORIO PARA LA SALIDA
					t_servicio = -b*log(r);												//ESTIMAMOS EL TIEMPO EN QUE OCURRIRA LA SALIDA
					//out_simulacion << r << "\t\t" << t_servicio << "\t\t\t";
					out_simulacion << r << "\t" << t_servicio << "\t";
					
				}else{
					r = 0;
					t_servicio = 0;
					out_simulacion << "-------\t-------\t";
				}
				
				if (tomar_obs)
				{
					if (s_llegada != tiempo) tiempos_lle += s_llegada;
					if ((tiempo + t_servicio)!= tiempo) tiempos_sal += (tiempo + t_servicio);
					tiempos_ser += t_servicio;
				}
				s_evento = comprobarSig_estado(t_salidas,s_salida,tiempo + t_servicio,s_llegada,tiempo,s_evento,Nt);	//LLAMAMOS A comprobarSig_estado
			}
			else //SIGUIENTE EVENTO ES UNA SALIDA, NO SE GENERA UNA ENTRADA EN ESTA ITERACION
			{
				//out_simulacion << "(2)";
				--Nt;
				out_simulacion << Nt << "\t-------\t-------\t";
				if (Nt >=4)
				{
					r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);	//GENERAMOS UN NUMERO ALEATORIO PARA LA SALIDA
					t_servicio = -b*log(r);												//ESTIMAMOS EL TIEMPO EN QUE OCURRIRA LA SALIDA
					out_simulacion << r << "\t" << t_servicio << "\t";
				}else{
					r = 0;
					t_servicio = 0;
					out_simulacion << "-------\t-------" << "\t";
				}
				
				if (tomar_obs)
				{
					if ((tiempo + t_servicio)!= tiempo) tiempos_sal += (tiempo + t_servicio);
					tiempos_ser += t_servicio;

				}
				s_evento = comprobarSig_estado(t_salidas,s_salida,tiempo + t_servicio,s_llegada,tiempo,s_evento,Nt);	//LLAMAMOS A comprobarSig_estado
			}
			if(s_llegada == 0 && s_salida == 0){
				out_simulacion << "-------\t-------" << "\t";
			}
			else if(s_llegada == 0){
				out_simulacion << "-------\t" << s_salida << "\t";
			}
			else if(s_salida == 0){
					out_simulacion << s_llegada << "\t" << "-------" << "\t";
						
			}
			else
			{
				if(s_llegada < 100)
					out_simulacion << s_llegada << "\t" << s_salida << "\t";
				else
					out_simulacion << s_llegada << "\t" << s_salida << "\t";
					
			}

			if (s_evento)
			{
				compara_T = s_llegada - tiempo;
				tiempo = s_llegada;	//SI LA SIGUIENTE ITERACIÓN SERÁ UNA ENTRADA, EL TIEMPO ACTUAL DE SIMULACIÓN INCREMENTA HASTA EL MOMENTO DE LA LLEGADA
				out_simulacion << "Llegada" << endl;
				
			}
			else
			{
				compara_T = s_salida - tiempo;
				tiempo = s_salida;			//SI LA SIGUIENTE ITERACIÓN SERÁ UNA SALIDA, EL TIEMPO ACTUAL DE SIMULACIÓN INCREMENTA HASTA EL MOMENTO DE LA SALIDA
				//if (s_llegada==0 && s_salida==0) out_simulacion << "----" << endl;
				//else out_simulacion << "Salida" << endl;
				out_simulacion << "Salida" << endl;
				
			}
			//TOMA DE OBSERVACIONES
			if (tomar_obs)
			{
				suma_L += (compara_T * Nt);
				if ((Nt-4) > 0) suma_Lq += (compara_T * (Nt - 4));
			}
			if (tiempo !=0) tt_sim = tiempo;
			//out_simulacion << ")" << endl;
		}
		//ASIGNAMOS OBSERVACIONES TEMPORALES
		out_simulacion << endl << "--------------------------------------------------------------------------------------------------------------------" << endl << endl;
		
		aux_X += (((tiempos_ser / tt_sim) / 4) * 100);
		aux_L += suma_L / tt_sim;
		aux_Lq += suma_Lq / tt_sim;
		aux_W += (tiempos_sal - tiempos_lle)/clientes_atendidos;
		aux_Wq += ((tiempos_sal - tiempos_lle) - tiempos_ser)/clientes_atendidos;//ORIGINAL
		replica++;
		//RESTABLECEMOS VARIABLES
		tomar_obs = false;			
		clientes_atendidos = 0; 	
		compara_T = 0;				
		suma_L = 0;				
		suma_Lq = 0;				
		tiempos_sal = 0;			
		tiempos_lle = 0;			
		tiempos_ser = 0;
		tiempo = 0;
		tt_sim = 0;
		s_llegada = 0;
	}
	//ASIGNACIONES A VARIABLES DE COMPARACION
	L = aux_L / cr;
	Lq = aux_Lq / cr;
	W = aux_W / cr;
	Wq = aux_Wq / cr;
	X = aux_X / cr;
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
