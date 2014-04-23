#include <iostream>
#include <cstdio>
//#include <cmath>
//#include "Formulas.h"
#include "Teoria.h"
#include <fstream>
#include <iomanip>  

using namespace std;

int main(){

	long long int n; //Cantidad de modelos a tratar
	double a; //lambda
	double b; //miu
	double cr; // Cantidad de replicas
	double tt; //Tiempo de transicion 
	double ts; //Tiempo de simulacion

	Teoria T;

	ifstream ent;//archivo de entrada(lectura)
	ofstream sal;//archivo de salida (escritura)

	ent.open("modelo.in",ios::in);

	if(!ent)
	{
		cout << "Existe un problema con el archivo o no Existe" << endl;

	}else
	{
		ent >> n;

		for(int i =0;i<n;i++)
		{
			ent >> a >> b >> cr >> tt >> ts;
			//cout << a << " " << b << " " << cr << " " << tt << " " << ts << endl;
  		 	
		 	//Inicio de la parte Teorica:
			T.Inicializar(a,b);
			T.Resolver(a,b);
			std::cout << std::fixed; 
			cout << "Modelo " << i+1 << ":" << endl;
			cout << "\t\t\t" << "Utilización" << "\t\t" << "L" << "\t\t"  << "Lq" << "\t\t" << "W" << "\t\t" << "Wq" << endl;
			cout << "Teórico" << "\t\t" << setprecision(2) << T.Get_X() << "\t\t\t" << setprecision(2) << T.Get_L() << "\t" << setprecision(2) << T.Get_Lq() << "\t3" << setprecision(2) << T.Get_W() << "\t4" << setprecision(2) << T.Get_Wq() << endl;
			T.limpiar();
			cout << endl;
		}

		ent.close();

	}
	
	return 0;
}

