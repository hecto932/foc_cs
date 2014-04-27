/* 
	-- FOC: Proyecto 2: Simulación -- 
	
	Integrantes:

	Nombres:			Cedulas:		Username LoL

	Alvarado, Moises 	C.I 20.700.696 - m0ises2
	Flores, Hector 		C.I 20.162.504 - D4rkslink
	Laya, David			C.I 20.315.979 - None
	Tovar, Carlos		C.I 20.193.114 - DarkGabriel1991

*/

//LIBRERIAS PROPIAS DE C++
#include <iostream>
#include <cstdio>
#include <fstream>
#include <iomanip> 
#include <string> 

//LIBERIAS CREADAS 
#include "Teoria.h"
#include "Simulacion.h"

using namespace std;

int main(){

	long long int n;//CANTIDAD DE MODELOS A PROCESAR
	double a;//LAMBDA
	double b;//MIU
	double cr;//CANTIDAD DE REPLICAS
	double tt;//TIEMPO DE TRANSICIÓN 
	double ts;//TIEMPO DE SIMULACIÓN

	Simulacion S;//SIMULACION
	Teoria T;//MODELO TEORICO

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

		for(int i=0;i<n;++i)//PARA CADA MODELO
		{
			in_modelo >> a >> b >> cr >> tt >> ts;//LEEMOS SUS DATOS
  		 	//EN ESTA PARTE DEL CODIGO REALIZAMOS LA SIMULACION CORRESPONDIENTE AL MODELO ACTUAL

		 	//AHORA CALCULAMOS LA PARTE TEORICA
			T.Inicializar(1/a,1/b);
			T.Resolver(1/a,1/b);

			//ESCRIBIMOS LOS RESULTADOS EN EL ARCHIVO DE SALIDA
			out_performance << "Modelo " << i+1 << ":" << endl;
			out_performance << "\t\t\t" << "Utilización" << "\t\t" << "L" << "\t\t"  << "Lq" << "\t\t" << "W" << "\t\t" << "Wq" << endl;
			out_performance << "Teórico" << "\t\t"  << T.Get_X() << "\t\t\t"  << T.Get_L() << "\t"  << T.Get_Lq() << "\t"  << T.Get_W() << "\t"  << T.Get_Wq() << endl;
			out_performance << endl;

			T.limpiar();//LIMPIAMOS LAS VARIABLES
		}

		in_modelo.close();//CERRAMOS EL ARCHIVO DE ENTRADA
		out_performance.close();//CERRAMOS EL ARCHIVO DE SALIDA

	}
	
	return 0;
}