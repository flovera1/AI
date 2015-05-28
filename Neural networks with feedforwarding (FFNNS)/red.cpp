#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "math.h" 
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#define NumNodosEntrada 2
#define NOMBRE_ARCHIVO_CASOS_PRUEBA NUM_CASOS_PRUEBA.txt

using namespace std;
class Red {
  double ** weigth_input_layer ;
  double * weigth_output_layer;
  int num_nodes;
  double tasaAprendizaje;

  public:
		Red(int num_nodes, double tasaAprendizaje);
		~Red();
		double feed_forward(double * valor_entrada, double * valores_intermedios);
		double net(double* weight, double* input, int n);
		inline double sigmoid(double y);
		double error_output(double output, double target);
		double resolve_case(double x_in, double y_in, double target);
		void resolve_set_cases(double* x, double* y, double* target, int size_arrays);
		void runTestCase(double X, double Y, double T);
		double calcularSalida(double x, double y);
};
double Red::sigmoid(double y){
	return 1/(1 + exp(-y));
}
double Red::error_output(double output, double target){
	return output*(1-output)*(target-output);
}
Red::Red(int num_nodes, double tasaAprendizaje){ //constructor
	this->num_nodes        = num_nodes;
	this-> tasaAprendizaje = tasaAprendizaje;
	weigth_output_layer    = new double[ num_nodes + 1 ];
	weigth_input_layer     = new double* [ NumNodosEntrada + 1];
	const long max_rand    = 1000000;
	srandom(time(NULL));
	for (int i =0; i<NumNodosEntrada+1;i++){
		weigth_input_layer[i] = new double[num_nodes];
		for (int j = 0; j < num_nodes; j++){
			weigth_input_layer[i][j] = -0.05+ ((double) (rand() % max_rand) / max_rand)/10; 
		}
	}
	for (int i =0; i<num_nodes+1;i++)
		weigth_output_layer[i] = -0.05+ ((double) (rand() % max_rand) / max_rand)/10; 
	
	
}
//destructor
Red::~Red(){
	for (int i =0; i<NumNodosEntrada+1;i++){
		delete(weigth_input_layer[i]);
	}
	delete(weigth_input_layer);
	delete(weigth_output_layer);
};
/**
* feed forward function
*/
double  Red:: feed_forward(double * valor_entrada, double * valores_intermedios){
	double acum;
	for(int i = 0; i < num_nodes; i++){
		//calculus for the whole net
		acum =0;
		for (int j = 0 ; j < NumNodosEntrada; j++){
			acum += weigth_input_layer[j][i]*valor_entrada[j];
		}
		//sigmoid function in action
		valores_intermedios[i] = sigmoid( acum + weigth_input_layer[NumNodosEntrada][i]);
	}
	//calculate the final value
	acum = 0;
	for(int k = 0; k < num_nodes; k++){	
		acum += weigth_output_layer[k]*valores_intermedios[k];			
	}

	return sigmoid(acum + weigth_output_layer[num_nodes]);	
}

/**
* New parameters, intermediate values are 'hidden' in the function
* 
*/
double  Red:: calcularSalida(double x, double y){
	double acum;
	double valor_entrada [2];
	valor_entrada[0] = x;
	valor_entrada[1] = y;
	double valores_intermedios [num_nodes];
	for(int i = 0; i < num_nodes; i++){
		//calculate the whole net
		acum = 0;
		for (int j = 0 ; j < NumNodosEntrada; j++){
			acum+=weigth_input_layer[j][i] * valor_entrada[j];
		}
		// Apply sigmoid function
		valores_intermedios[i] = sigmoid(acum+weigth_input_layer[NumNodosEntrada][i]);
	}
	//calculate the output values
	acum =0;
	for(int k = 0; k < num_nodes; k++){	
		acum += weigth_output_layer[k]*valores_intermedios[k];			
	}
	
	return sigmoid(acum + weigth_output_layer[num_nodes]);
}    
double Red:: resolve_case(double x_in, double y_in, double target){
	double valor_entrada[NumNodosEntrada];
	double valores_intermedios[num_nodes];
	double valor_salida;
	double error_intermedios[num_nodes];
	double error_salida;
	valor_entrada[0] = x_in;
	valor_entrada[1] = y_in;
	// Feed forward.
	valor_salida = feed_forward(valor_entrada, valores_intermedios);
	//calculate the error in every output
	error_salida = error_output(valor_salida, target);
	double acum;
	//calculate the error in every hidden neuron 
	for(int i = 0; i < num_nodes; i++){
		acum = 0; 
		for(int j=0; j < num_nodes+1; j++){
			acum += weigth_output_layer[j] * error_salida;
		}
		error_intermedios[i] =  valores_intermedios[i] * (1 - valores_intermedios[i]) * acum;
	}
	//Update values from hidden layer to output layer
	for(int i = 0 ; i < num_nodes; i++){
		weigth_output_layer[i] += tasaAprendizaje * error_salida * valores_intermedios[i];
	}
	weigth_output_layer[num_nodes] += tasaAprendizaje*error_salida;
	//Update weights in the input layer 
	for(int i = 0; i<num_nodes; i++){
		for (int j = 0; j<NumNodosEntrada; j++){
			weigth_input_layer[j][i] += tasaAprendizaje*
										error_intermedios[i]*
										valor_entrada[j];	
		}
		weigth_input_layer[NumNodosEntrada][i]+=tasaAprendizaje*
										error_intermedios[i];
	}
	return valor_salida;
};
//training
void Red::resolve_set_cases(double* x, double* y, double* target, int size_arrays){
	for(int i = 0; i<size_arrays; i++){		
		resolve_case(x[i], y[i], target[i]);//el target se inicializa en el main
	}
}
double pertenece(double a, double b){
	if ((10-a)*(10-a) + (8-b)*(8-b) <= 9)
		return 1;
	return 0;
}
int main(){	
	string line;
	string numIt [6]      = {"500.txt","1000.txt","2000.txt","500b.txt","1000b.txt","2000b.txt",};
	string afueraA [6]    = {"500a.dat","1000a.dat","2000a.dat","500ba.dat","1000ba.dat","2000ba.dat",};
	string adentroA [6]   = {"500b.dat","1000b.dat","2000b.dat","500bb.dat","1000bb.dat","2000bb.dat",};
	int numCasosPrueba[6] = {500,1000,2000,500,1000,2000};
	ofstream resultados;
	resultados.open("meh.txt");
	for (int numArchivo = 0; numArchivo<6;numArchivo++){
		ifstream myfile ( numIt [numArchivo].c_str());
		cout << "Con archivo: " << numIt [numArchivo] << endl;
		resultados << "Con archivo: " << numIt [numArchivo] << endl;
		ofstream adentros;
		ofstream afuera;
		afuera.open (afueraA[numArchivo].c_str());
		adentros.open (adentroA[numArchivo].c_str());
 		double x [numCasosPrueba[numArchivo]];
		double y [numCasosPrueba[numArchivo]];
		double t [numCasosPrueba[numArchivo]];
		if (myfile.is_open()){
			for (int i = 0; i< numCasosPrueba[numArchivo];i++){
				getline (myfile,line);
				stringstream str(line);
				string a, b, c;
				str >> a >> b >> c;
				x[i] = atof(a.c_str());
				y[i] = atof(b.c_str());
				switch (c.c_str()[0]){
					case 'A':
						t[i]=0;
						break;
					case 'B':
						t[i]=1;
						break;
				}
			}
			myfile.close();
		}
		else 
			cout << "Unable to open file"; 
		double result    = 0;	
		int numCorrectos = 0;
		Red red          = Red(8, 0.005);
		for(int u = 0; u < 50000; u++){
			red.resolve_set_cases(x, y, t, numCasosPrueba[numArchivo]);
		}
		int cont  = 0;
		int cont2 = 0;
		for(int u = 0; u < numCasosPrueba[numArchivo]; u++){
			if (pertenece(x[u], y[u])!=t[u]){
				cont++;
			}
			if (t[u]==0)
				cont2++;
		}
		cout << " ejemplos mal clasificados: " << cont <<endl;
		cout << " numero de elementos fuera del circulo: " << cont2 <<endl;
		resultados << " ejemplos mal clasificados: " << cont <<endl;
		resultados << " numero de elementos fuera del circulo: " << cont2 <<endl;
		numCorrectos = 0;
		for(int cx = 0; cx < 100; cx++){
				for(int cy = 0; cy<100; cy++){
				double coorX = (double) cx/100*20;
				double coorY = (double) cy/100*12;
				result = red.calcularSalida(coorX,coorY);
				if (result>.5){
					result =1;
					adentros<<coorX<< " " << coorY <<endl;
				}
				else{
					result =0;
					afuera<<coorX<< " " << coorY <<endl;
				}	
				if (pertenece(coorX,coorY)==result){
					numCorrectos++;
				}
			}	
		}
		adentros.close ();
		afuera.close ();		
		cout << " tasa aciertos:"<< (double) numCorrectos/10000 <<endl;
		cout << " aciertos:"<< numCorrectos <<endl;
		resultados << " tasa aciertos:"<< (double) numCorrectos/10000 <<endl;
		resultados << " aciertos:"<< numCorrectos <<endl;
	}	
return 0;
}
