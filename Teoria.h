#ifndef _TEORIA_
#define _TEORIA_

using namespace std;


class Teoria {
	
	private:
		double L;
		double Lq;
		double W;
		double Wq;
		double X;
		double Ro;
		double Po;
		double Ps;
		
	public:

		Teoria();
		long long int factorial(long long int numero);
		double potencia(double base,double exponente);
		void Inicializar(double Lambda, double Miu); //Define los valores para cada constante
		void Resolver(double Lambda, double Miu);
		double Get_L();
		double Get_Lq();
		double Get_W();
		double Get_Wq();
		double Get_X();

		void limpiar();
		
};

#endif
