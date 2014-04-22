#include <iostream>
#include <cstdio>
//#include <cmath>
//#include "Formulas.h"
#include "Teoria.h"
#include <fstream>

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
		cout << "Existe un probolema con el archivo o no Existe" << endl;

	}else
	{

		ent >> n;
		cout << "puto n_ "<<n<<endl;

		for(int i =0;i<n;i++)
		{
			ent>> a >> b >> cr >> tt >> ts;
			//cout<< a << " "<<  b << " " << cr << " " << tt << " " << ts << " " << "\n";
		 	
		 	//Inicio de la parte Teorica:
			T.Inicializar(a,b);
			T.Resolver(a,b);
			cout << "Modelo " << i+1 << endl;
			cout << "\t \t" << " Utilizaciòn " << "\t" << "\t" << " L " << "\t"  << "\t" << " Lq " << "\t" << "\t" << " W " << "\t" << "\t" << " Wq " << endl;
			cout << "\t" << "\t" << T.Get_X() << " " <<  "\t" << T.Get_Lq() << " " << "\t" << T.Get_W() << " " << "\t" << T.Get_Lq() << " " << "\t" << T.Get_L() << endl;

			T.limpiar();
		}


		ent.close();

	}
	
/*
	cin >> n;
	while(n--)//Mientras el numero de casos sea distinto de 0
	{
	
		scanf("%lg %lg %lg %lg %lg", &a, &b, &cr, &tt, &ts);
		printf("%lg %lg %lg% lg %lg\n",a,b,cr,tt,ts);
	}*/

	return 0;
}

