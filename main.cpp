/* 
	-- FOC: Proyecto 2: Simulación -- 
	
	Integrantes:

	Nombres:			Cedulas:		Username LoL

	Alvarado, Moises 	C.I 20.700.696 - m0ises2
	Flores, Hector 		C.I 20.162.504 - D4rkslink
	Laya, David			C.I 20.315.979 - None
	Tovar, Carlos		C.I 20.193.114 - DarkGabriel1991

*/

#include <iostream>
#include <cstdio>
#include <fstream>
#include <iomanip> 
#include <string> 

#include "Modelo.h"

using namespace std;

int main()
{
	Modelo m;
	int n;

	ifstream in_modelo;//APUNTADOR AL ARCHIVO DE ENTRADA "modelo.in" 
	ofstream out_performance, out_simulacion;//APUNTADOR AL ARCHIVO DE SALIDA "performance.out"

	in_modelo.open("modelo.in",ios::in);
	out_performance.open("performance.out");//CREAMOS EL ARCHIVO DE SALIDA PERFORMANCE.OUT

	if(!in_modelo.is_open())//SI EL ARCHIVO NO FUE ABIERTO EXITOSAMENTE
	{
		cout << "Existe un problema con el archivo o no Existe" << endl;
	}
	else
	{
		in_modelo >> n;//LEEMOS EL NUMERO DE MODELOS A PROCESAR DEL ARCHIVO MODELO.IN
		
		out_performance.precision(2);//PRECISION A 2 DECIMALES
		out_performance.setf(ios::fixed);

		out_simulacion.precision(4);//PRECISION A 4 DECIMALES
		out_simulacion.setf(ios::fixed);

		for(int i=0;i<n;++i)//PARA CADA MODELO
		{
			m.leer_modelo(in_modelo);
			m.resolver_teoria();
			m.realizar_simulacion();
			m.show_results(i,out_performance);
			m.limpiar();
		}

		in_modelo.close();//CERRAMOS EL ARCHIVO DE ENTRADA
		out_performance.close();//CERRAMOS EL ARCHIVO DE SALIDA

		/*cout << "| tiempo t (m)\t| N(t)\t| r_llegada\t\t| t_llegada\t\t| r_servicio\t| t_servicio\t| s_llegada\t\t| s_salida\t\t| s_evento" << endl;
		cout << "----------------------------------------------------------------------------------------------------------------------------------" << endl;
 	 	cout << "| XX.XXXX\t\t| XX\t| X.XXXX\t\t| XX.XXXX\t\t| X.XXXX\t\t| XX.XXXX\t\t| XX.XXXX\t\t| XX.XXXX\t\t| Llegada" << endl;
 	 	cout << "| XX.XXXX\t\t| XX\t| X.XXXX\t\t| XX.XXXX\t\t| X.XXXX\t\t| XX.XXXX\t\t| XX.XXXX\t\t| XX.XXXX\t\t| Salida" << endl;*/

	}

	return 0;
}