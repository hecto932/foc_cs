#include <iostream>
#include <cmath>
#include "Teoria.h"

using namespace std;

double Teoria::factorial (double numero) {
	double resultado=1;
	for(int i=numero;i>1;i--)
	{
		resultado*=i;
	}
	return resultado;

	//for(int i=numero;i>1;--i)
	//	resultado*=i;
	//return resultado;
}

double Teoria::potencia(double base,double exponente)
{
	return pow(base,exponente);
}

void Teoria::Inicializar(double Lambda, double Miu)
{
	double Pc=0;
	this->Ro=Lambda/Miu;
	//Obtenemos la potencia de Ro necesaria para la sumatoria
	for (int i=0;i<4;i++)
	{
		Pc+=((potencia(this->Ro,i))/factorial(i));
	}
	Pc+=((potencia(this->Ro,4))/(24*(1-(this->Ro/4))));
	this->Po=1/Pc;
	this->Ps=(potencia(this->Ro,4)/24)*this->Po;
}

void Teoria::Resolver(double Lambda, double Miu)
{
	this->Lq=((4*this->Ro)/(potencia((4-this->Ro),2)))*this->Ps;
	this->L=this->Ro+this->Lq;
	this->Wq=this->Lq/Lambda;
	this->W=this->Wq + (1/Miu);
	this->X=((this->L-this->Lq)/4)*100;
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
	this->L = 0;
	this->Lq = 0;
	this->Wq = 0;
	this->W = 0;
	this->X = 0;
	this->Ro = 0;
	this->Po = 0;
	this-> Ps = 0;
}