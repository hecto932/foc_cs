#include <iostream>
#include <cmath>
#include "Teoria.h"

using namespace std;

//CONSTRUCTOR
Teoria::Teoria()
{
	L 	= 0;
	Lq 	= 0;
	Wq 	= 0;
	W 	= 0;
	X 	= 0;
	Ro 	= 0;
	Po 	= 0;
	Ps 	= 0;
}

//CALCULA EL FACTORIAL DE UN NUMERO
long long int Teoria::factorial(long long int numero)
{
	long long int resultado=1;
	for(long long int i=numero;i>1;i--)
		resultado*=i;
	return resultado;
}

//INICIALIZA EL MODELO CALCULANDO CIERTOS PARAMETROS
void Teoria::Inicializar(double Lambda, double Miu)
{
	double Pc = 0;
	Ro = Lambda/Miu;//CALCULAMOS RO
	for(int i=0;i<4;i++)
		Pc += (pow(Ro,i)/factorial(i)); 
	Pc += ( pow(Ro, 4) / ( 24 * ( 1 - Ro/4 ) ) );
	Po = pow(Pc,-1);
	Ps = ( pow(Ro,4) / 24 ) * Po;
}

//RESOLVEMOS PARTE DEL MODELO 
void Teoria::Resolver(double Lambda, double Miu)
{
	Lq = ( (4 * Ro) / pow((4 - Ro),2) ) * Ps;
	
	L = Lq + Ro;
	
	Wq = Lq / Lambda;
	
	W = Wq + (1/Miu);
	
	X = ( (L - Lq) / 4 ) * 100; 
}

//METODOS GET
double Teoria::Get_L()
{
	return L;
}
double Teoria::Get_Lq()
{
	return Lq;
}
double Teoria::Get_W()
{
	return W;
}
double Teoria::Get_Wq()
{
	return Wq;
}
double Teoria::Get_X()
{
	return X;
}
//METODO LIMPIAR
void Teoria::limpiar()
{
	L 	= 0;
	Lq 	= 0;
	Wq 	= 0;
	W 	= 0;
	X 	= 0;
	Ro 	= 0;
	Po 	= 0;
	Ps 	= 0;
}