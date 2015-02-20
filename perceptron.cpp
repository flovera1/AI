#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_PRUEBAS 1000
#define NUM_ITERACIONES 30
#define NUM_TASAS_APRENDIZAJE 8

using namespace std;
//########################### PERCEPTRON
class Perceptron {
		double tasaAprendizaje;
		double w0, w1, w2; //pesos
		#define x0 1;
  public:
		Perceptron(double tasaAprendizaje, double w1, double w2, double umbral);
		int procesarEntradaConEntrenamiento(double x1, double x2, int target);
		int procesarEntradaSinEntrenamiento(double x1, double x2);
		int calcularO(double x1, double x2);
		void cambiarPesos(int o, int target, double x1, double x2);
};
//revisado
Perceptron::Perceptron(double tasaAprendizaje, double w1, double w2, double umbral){
	this->tasaAprendizaje = tasaAprendizaje;
	this->w1 = w1;
	this->w2 = w2;
	this->w0 = umbral;
}
//revisado
int Perceptron:: calcularO(double x1, double x2){
	double suma;
	suma = (x1 * this->w1 )+(x2 * this->w2);
		if( suma > -1*this->w0)
			return 1;
		else 
			return -1;
}
/*
 * Devuelve un entero: 1 si el o calculado es 1; 0 si el valor calculado
 * es -1.
 * 
 * Modifica los pesos de la neurona para hacer el entrenamiento. 
 */
int Perceptron:: procesarEntradaConEntrenamiento(double x1, double x2, int target){
	int o = calcularO(x1,x2);
	cambiarPesos(o,target,x1,x2);	
	return o;
}	
/*
 * Devuelve un entero: 1 si el o calculado es 1; 0 si el valor calculado
 * es -1 
 */
int Perceptron:: procesarEntradaSinEntrenamiento(double x1, double x2){
	return calcularO(x1,x2);
}	
void Perceptron:: cambiarPesos(int o, int target, double x1, double x2){
	this->w0 = this->w0 + this->tasaAprendizaje * (target - o) * x0; 
	this->w1 = this->w1 + this->tasaAprendizaje * (target - o) * x1; 
	this->w2 = this->w2 + this->tasaAprendizaje * (target - o) * x2;
}
//###########################
//###########################GENERADOR
#define AND 0
#define OR 1
#define XOR 2
#define X1 0
#define X2 1
#define T 2


int main(){
	// Generar training set y pesos.
	const long max_rand = 1000000;
	// Training sets y TestSet.
	int trainingSet [4][3][3];
	for (int i = 0; i <3; i++){
		trainingSet[0][i][X1]  = 0;
		trainingSet[1][i][X1]  = 0;
		trainingSet[2][i][X1]  = 1;
		trainingSet[3][i][X1]  = 1;
		trainingSet[0][i][X2]  = 1;
		trainingSet[1][i][X2]  = 0;
		trainingSet[2][i][X2]  = 1;
		trainingSet[3][i][X2]  = 0;
	}	
	for (int i =0; i<4; i++){
		if (trainingSet[i][AND][X1]&&trainingSet[i][AND][X2])
			trainingSet[i][AND][T]  = 1;
		else
			trainingSet[i][AND][T]  = -1;
		if (trainingSet[i][OR][X1]||trainingSet[i][OR][X2])
			trainingSet[i][OR][T]   = 1;
		else
			trainingSet[i][OR][T]   = -1;
		if (trainingSet[i][XOR][X1]!=trainingSet[i][XOR][X2])
			trainingSet[i][XOR][T]  = 1;
		else
			trainingSet[i][XOR][T]  = -1;			
	}
	srandom(time(NULL));
	int numIteraciones [NUM_ITERACIONES];
	for (int i = 0; i< NUM_ITERACIONES; i++)
		numIteraciones[i] = i;
		
	double tasaAprend [NUM_TASAS_APRENDIZAJE] = { 0.01, 0.05, 0.1, 0.2, 0.3, 0.4, 0.5, 0.99 };
	double resultadoPruebas [3][NUM_TASAS_APRENDIZAJE][NUM_ITERACIONES][NUM_PRUEBAS] ;
	for (int numPrueba = 0; numPrueba< NUM_PRUEBAS; numPrueba++){
		double w1      = (double) (random() % max_rand) / max_rand;
		double w2      = (double) (random() % max_rand) / max_rand;
		double umbral  = (double) (random() % max_rand) / max_rand;
		//i itera sobre las operaciones: AND=0, OR=1,XOR=2.
		for(int i = 0; i < 3; i++){
			// Entrenamiento	
			for (int j = 0; j<NUM_ITERACIONES;j++){
				for (int itTasaAprend = 0 ; itTasaAprend <8; itTasaAprend++) {
					Perceptron p      = Perceptron(tasaAprend[itTasaAprend], w1, w2, umbral);
					for (int numIter  = 0 ; numIter < numIteraciones[j] ; numIter++){	
						for(int k = 0; k< 4;k++){
							p.procesarEntradaConEntrenamiento(trainingSet[k][i][X1], 
															 trainingSet[k][i][X2],
															 trainingSet[k][i][T]);
						}
					}
					// Prueba.
					int clasificadosCorrectamente = 0;
					for(int k = 0; k< 4;k++){
						if (trainingSet[k][i][T] == p.procesarEntradaSinEntrenamiento(
															trainingSet[k][i][X1], 
															trainingSet[k][i][X2]))
							clasificadosCorrectamente++;
					}	
					resultadoPruebas[i][itTasaAprend][j][numPrueba] = (double) (4-clasificadosCorrectamente)/4	;	
				}
			}		
		}
	}	
	//	double resultadoPruebas [3][NUM_TASAS_APRENDIZAJE][NUM_ITERACIONES][NUM_PRUEBAS] ;
	for (int i = 0; i< 3; i++){
		cout << "------------------------------" <<endl;
		cout << "Operacion:" << i <<endl;
		for (int k = 0; k < NUM_ITERACIONES; k++){
			cout << numIteraciones[k];
			for (int j = 0; j< NUM_TASAS_APRENDIZAJE; j++){
				double sum = 0;
				for (int numPrueba = 0 ; numPrueba< NUM_PRUEBAS; numPrueba++){
					sum += resultadoPruebas[i][j][k][numPrueba];
				}
				sum = sum/NUM_PRUEBAS;
				cout << " " << sum;
			}	
			cout << endl;
		}
	}
	return 0;
	
	}
