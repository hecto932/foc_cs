#ifndef _SIMULACION_
#define _SIMULACION_

class Simulacion {

private:
	//DECLARAMOS LAS VARIABLES NECESARIAS PARA LA SIMULACION
 	int Nt;//Cantidad actual de clientes en sistema
 	int servidores;//Usado para llevar el control de los servidores disponibles
 	float tLlegada;//Usado para calcular el Siguiente tiempo entre llegadas
 	float tSalida;//Usado para calcular el Siguiente tiempo entre salidas
 	double tiempo;//Usado para tiempo t de simulacion
 	//DECLARAMOS UNA VARIABLE ASISTENCIAL PARA ASIGNAR LOS NUMEROS ALEATORIOS GENERADOS EN CADA ITERACION DE LA SIMULACION
 	float aleatorio;//Llegada
 	//DECLARAMOS LAS VARIABLES NECESARIAS PARA LA COMPARACION ENTRE LOS VALORES DE SIMULACION Y TEORIA
 	double L;
	double Lq;
	double W;
	double Wq;
	double X;
 public:
 	//CONSTRUCTOR
 	Simulacion();
 	//EJECUCIÓN DE LA SIMULACIÓN
 	void ejecutar(int numero_sim, double a, double b, double replicas, double tTrans, double tSim);
 	//OBSERVADORES
 	double Get_L();
	double Get_Lq();
	double Get_W();
	double Get_Wq();
	double Get_X();
	//LIMPIAR
 	void limpiar();

};

#endif