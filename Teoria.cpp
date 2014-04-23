#include <iostream>
#include <cmath>
#include "Teoria.h"

using namespace std;

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

long long int Teoria::factorial(long long int numero)
{
	long long int resultado=1;
	for(long long int i=numero;i>1;i--)
		resultado*=i;
	return resultado;
}
double Teoria::potencia(double base,double exponente)
{
	return pow(base,exponente);
}
void Teoria::Inicializar(double Lambda, double Miu)
{
	//double Pc=0;//P0
	//this->Ro=Lambda/Miu;
	//Obtenemos la potencia de Ro necesaria para la sumatoria
	//for (int i=0;i<4;i++)
	//{
	//	Pc+=((potencia(this->Ro,i))/factorial(i));
	//}
	//Pc+=((potencia(this->Ro,4))/(24*(1-(this->Ro/4))));
	//this->Po=1/Pc;
	//this->Ps=(potencia(this->Ro,4)/24)*this->Po;

	double Pc = 0;

	Ro = Lambda/Miu;

	for(int i=0;i<4;i++)
		Pc += (potencia(Ro,i)/factorial(i));
	Pc += ( potencia(Ro, 4) / ( 24 * ( 1 - Ro/4 ) ) );
	Po = potencia(Pc,-1);
	Ps = ( potencia(Ro,4) / 24 ) * Po;
}

void Teoria::Resolver(double Lambda, double Miu)
{
	//this->Lq=((4*this->Ro)/(potencia((4-this->Ro),2)))*this->Ps;
	//this->L=this->Ro+this->Lq;
	//this->Wq=this->Lq/Lambda;
	//this->W=this->Wq + (1/Miu);
	//this->X=((this->L-this->Lq)/4)*100;

	Lq = ( (4 * Ro) / potencia((4 - Ro),2) ) * Ps;
	L = Lq + Ro;
	Wq = Lq / Lambda;
	W = Wq + (1/Miu);
	X = ( (L - Lq) / 4 ) * 100; 
}
double Teoria::Get_L()
{
	return this->L;
}
double Teoria::Get_Lq()
{
	return this->Lq;
}
double Teoria::Get_W()
{
	return this->W;
}
double Teoria::Get_Wq()
{
	return this->Wq;
}
double Teoria::Get_X()
{
	return this->X;
}
void Teoria::limpiar()
{
	this->L 	= 0;
	this->Lq 	= 0;
	this->Wq 	= 0;
	this->W 	= 0;
	this->X 	= 0;
	this->Ro 	= 0;
	this->Po 	= 0;
	this->Ps 	= 0;
}