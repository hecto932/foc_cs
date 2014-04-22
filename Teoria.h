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
		double Ro;//Constante
		double Po;//Constante
		double Ps;//Constante
		
	public:

		double factorial(double numero);
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
