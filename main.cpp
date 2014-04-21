#include <iostream>
#include <cstdio>
#include <cmath>
#include "Formulas.h"

using namespace std;

int main(){

	long long int n; //Cantidad de modelos a tratar
	double a; //lambda
	double b; //miu
	double cr; // Cantidad de replicas
	double tt; //Tiempo de transicion 
	double ts; //Tiempo de simulacion

	cin >> n;
	while(n--)//Mientras el numero de casos sea distinto de 0
	{
	
		scanf("%lg %lg %lg %lg %lg", &a, &b, &cr, &tt, &ts);
		printf("%lg %lg %lg% lg %lg\n",a,b,cr,tt,ts);
	}

	return 0;
}

