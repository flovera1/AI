#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "math.h" 
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;
 
class Red {
 
  double ** weigth_input_layer ;
  double ** weigth_output_layer;
  int numNodosEntrada;
  int numNodosSalida;
  
  int num_nodes;
  double tasaAprendizaje;

  public:
		Red(int num_nodes,int numNodosSalida, int numNodosEntrada, double tasaAprendizaje);
		~Red();
		
		void feed_forward(double * valor_entrada, double * valores_intermedios, double * valor_salida);
		
		double net(double* weight, double* input, int n);
		inline double sigmoid(double y);
		
		double error_output(double output, double target);
		
		void resolve_case(double * input ,  double * target);
		void resolve_set_cases(double ** input, double** target, int size_arrays);
		
		void runTestCase(double X, double Y, double T);
		void calcularSalida(double * input, double * salida );
		
};

double Red::sigmoid(double y){
	return 1/(1+exp(-y));
}


double Red::error_output(double output, double target){
	return output*(1-output)*(target-output);
}

Red::Red(int num_nodes_layer, int numNodosSalida, int numNodosEntrada, double tasaAprendizaje){ //constructor
	this->num_nodes = num_nodes_layer;
	this-> tasaAprendizaje = tasaAprendizaje;
	this->numNodosEntrada = numNodosEntrada;
	this->numNodosSalida = numNodosSalida;

	
	weigth_input_layer = new double* [numNodosEntrada+1];
	
	const long max_rand = 1000000;
	srandom(time(NULL));
	
	for (int i =0; i<numNodosEntrada+1;i++){
		weigth_input_layer[i] = new double[num_nodes];
		
		for (int j = 0; j < num_nodes; j++){
			weigth_input_layer[i][j] = -0.05+ ((double) (rand() % max_rand) / max_rand)/10; 
		}
	}

	weigth_output_layer = new double *[num_nodes+1];
	for (int i =0; i<num_nodes+1;i++){
		weigth_output_layer[i] = new double[numNodosSalida];
		
		for (int j = 0; j < numNodosSalida; j++){
			weigth_output_layer[i][j] = -0.05+ ((double) (rand() % max_rand) / max_rand)/10; 
		}
	}
		
}

Red::~Red() //destructor
{
	for (int i =0; i<numNodosEntrada+1;i++){
		delete [] weigth_input_layer[i];
	}
	
	for (int i =0; i<num_nodes+1;i++){
		delete [] weigth_output_layer[i];
	}
	delete [] weigth_input_layer;
	delete [] weigth_output_layer;
};

void  Red:: feed_forward(double * valor_entrada, double * valores_intermedios, double * valor_salida){
	double acum;
	
	//Calculo de los valores intermedios.
	for(int i = 0; i < num_nodes; i++){
		//Calculo de net
		acum =0;
	
		for (int j = 0 ; j < numNodosEntrada; j++){
			acum+=weigth_input_layer[j][i]*valor_entrada[j];
		}
		
		// Aplicacion de la funcion sigmoidal. 
		valores_intermedios[i] = sigmoid(acum+weigth_input_layer[numNodosEntrada][i]);
	}
	
		//Calculo de los valores intermedios.
	for(int i = 0; i < numNodosSalida; i++){
		//Calculo de net
		acum =0;
	
		for (int j = 0 ; j < num_nodes; j++){
			acum+=weigth_output_layer[j][i]*valor_entrada[j];
		}
		
		// Aplicacion de la funcion sigmoidal. 
		valor_salida[i] = sigmoid(acum+weigth_output_layer[num_nodes][i]);
	}
}

void  Red:: calcularSalida(double * valor_entrada, double* valor_salida ){
	double acum;
	
	double valores_intermedios [num_nodes];
	
	//Calculo de los valores intermedios.
	for(int i = 0; i < num_nodes; i++){
		//Calculo de net
		acum =0;
	
		for (int j = 0 ; j < numNodosEntrada; j++){
			acum+=weigth_input_layer[j][i]*valor_entrada[j];
		}
		
		// Aplicacion de la funcion sigmoidal. 
		valores_intermedios[i] = sigmoid(acum+weigth_input_layer[numNodosEntrada][i]);
	}
	
		//Calculo de los valores intermedios.
	for(int i = 0; i < numNodosSalida; i++){
		//Calculo de net
		acum =0;
	
		for (int j = 0 ; j < num_nodes; j++){
			acum+=weigth_output_layer[j][i]*valor_entrada[j];
		}
		
		// Aplicacion de la funcion sigmoidal. 
		valor_salida[i] = sigmoid(acum+weigth_output_layer[num_nodes][i]);
	}
	
}    

void Red:: resolve_case(double * valor_entrada, double * target){
	
	double valores_intermedios[num_nodes];
	double valor_salida[numNodosSalida];
	
	double error_intermedios[num_nodes];
	double error_salida[numNodosSalida];

	// Feed forward.
	feed_forward(valor_entrada, valores_intermedios,valor_salida);
	
	
	//Calculo del error de la capa de salida.
	for (int i = 0 ; i< numNodosSalida; i++){
		error_salida[i] = error_output(valor_salida[i], target[i]);
	}
	
	
	double acum;
	
	//Calculo de error de cada neurona intermedia
	for(int i = 0; i < num_nodes; i++){
		acum = 0; 
		for(int j=0; j < numNodosSalida; j++){
			acum += weigth_output_layer[i][j]*error_salida[j];
		}
		error_intermedios[i] =  valores_intermedios[i]*(1-valores_intermedios[i])*acum;
	}
	
	
	//Actualizar pesos de la capa intermedia a la de salida
	for(int j=0; j < numNodosSalida; j++){
	
		for(int i = 0 ; i < num_nodes; i++){
			weigth_output_layer[i][j] += tasaAprendizaje*error_salida[j]*valores_intermedios[i];
		}
		weigth_output_layer[num_nodes][j] += tasaAprendizaje*error_salida[j];
	}
	
	
	
	//Actualizar pesos de la capa de entrada a la capa de salida. 
	for(int i = 0; i<num_nodes; i++){
		for (int j = 0; j<numNodosEntrada; j++){
			weigth_input_layer[j][i] += tasaAprendizaje*
										error_intermedios[i]*
										valor_entrada[j];	
		}
		weigth_input_layer[numNodosEntrada][i]+=tasaAprendizaje*
										error_intermedios[i];
	}
	
};

//entrenamiento
void Red::resolve_set_cases(double** input, double** target, int size_arrays){
	
	for(int i = 0; i<size_arrays; i++){		
		resolve_case(input[i], target[i]);//el target se inicializa en el main
	}
}
#define NUM_VALORES_SALIDA 3
#define NUM_VALORES_ENTRADA 9

void pasarTArreglo(int t, double arreglo [NUM_VALORES_SALIDA]){
	switch (t){
	
	case 0:
		arreglo[0]=1; arreglo[1]=0;arreglo[2]=0;
	case 1:
		arreglo[0]=0; arreglo[1]=1;arreglo[2]=0;
	case 2:
		arreglo[0]=0; arreglo[1]=0;arreglo[2]=1;
	
	}
}

int pasarArregloT(double arreglo[NUM_VALORES_SALIDA]){

	for (int i = 0; i<NUM_VALORES_SALIDA; i++){
		if (arreglo[i]==1){
			for (int j = i+1; j<NUM_VALORES_SALIDA; j++){
				if (arreglo[j]==1){
					return -1;
				}
			}
			return i;
		}
	}
	
	return -1;
}
#define NOMBRE_ARCHIVO_CASOS_PRUEBA cmd.data
#define SIZE_SET 1473

int main(int argc, char* argv[])
{	
	if (argc != 5){
		cout << "Num invalido de parametros" <<endl;
		cout << "anticonceptivo <num-neuronas> <proporcion> <entrada> <salida>" <<endl;
		return (0);

	}

	double prop = atof(argv[2]);
	int numNeuronas =atoi(argv[1]);
	string entrada = argv[3];
	string archSalida = argv[4];
	
	int numIteraciones =50000;
	
	ifstream myfile (entrada.c_str());
	string line;
	
	ofstream fsalida;
	fsalida.open (archSalida.c_str());
  
  
	int set[SIZE_SET][NUM_VALORES_ENTRADA];
	int target[SIZE_SET];
	
	if (myfile.is_open()){
		for (int i = 0; i < SIZE_SET; i++){
			getline (myfile,line);
			stringstream str(line);
			string s[10];
			str >> s[0] >> s[1] >> s[2] >> s[3] >> s[4] >> s[5] >> s[6]
				>> s[7] >> s[8] >> s[9];
			for (int j = 0; j < NUM_VALORES_ENTRADA; j++){
				set[i][j] = atoi(s[j].c_str());
			}
			target[i] = atoi(s[9].c_str());
						
		}
		myfile.close();
	}
	else 
		cout << "Unable to open file \n"; 
	
	
	Red red = Red(numNeuronas,NUM_VALORES_SALIDA,NUM_VALORES_ENTRADA, 0.005);
					
	// Generar training y testset
					
	int sizeTrainingSet = floor(prop*SIZE_SET);
	int sizeTestSet = SIZE_SET- sizeTrainingSet;
					
	double ** trainingSet = new double * [sizeTrainingSet];
	double ** targetTrainingSet = new double * [sizeTrainingSet];
			
	double ** testSet = new double * [sizeTestSet];
	double ** targetTestSet = new double * [sizeTestSet];
					
					
	for (int i =0; i<sizeTrainingSet; i++){
		trainingSet[i] = new double [NUM_VALORES_ENTRADA];
		targetTrainingSet[i] = new double [NUM_VALORES_SALIDA];
						
			for (int j = 0; j<NUM_VALORES_ENTRADA; j++){
				trainingSet[i][j] = set[i][j];
			}
						
			pasarTArreglo(target[i],targetTrainingSet[i]);	
						
	}
					
	for (int i =0; i<sizeTestSet; i++){
		testSet[i] = new double [NUM_VALORES_ENTRADA];
		targetTestSet[i] = new double [NUM_VALORES_SALIDA];	
				
		for (int j = 0; j<NUM_VALORES_ENTRADA; j++){
			testSet[i][j] = set[i+sizeTrainingSet][j];
		}
		pasarTArreglo(target[i+sizeTrainingSet],targetTestSet[i]);	
	}

				
	// Entrenamiento.
					
	for(int i = 0; i < numIteraciones; i++){
		red.resolve_set_cases(trainingSet,targetTrainingSet,sizeTrainingSet);
	}
	
	int numCorrectos = 0;
	for(int i = 0; i < sizeTestSet; i++){
		double salida [NUM_VALORES_SALIDA];
		red.calcularSalida(testSet[i],salida);

		int t = pasarArregloT(salida);
		for (int j = 0; j<NUM_VALORES_ENTRADA; j++){
			fsalida  << testSet[i][j] << ',';
			
		}	
		fsalida << t;
		fsalida <<endl;
		
		int t2 = pasarArregloT(targetTestSet[i]);
						
						//cout << t << " " << t2 << endl;
						
		if (t==t2){
			numCorrectos++;
		}
	}				
	
	cout << "Tasa de aciertos: " << (double) numCorrectos / sizeTestSet << endl;
	for (int i =0; i<sizeTrainingSet; i++){			
		delete[] trainingSet[i];
		delete [] targetTrainingSet[i] ;
	}
					
	for (int i =0; i<sizeTestSet; i++){
		delete[]testSet[i];
		delete[]targetTestSet[i];
	}
	
	delete [] trainingSet;
	delete [] targetTrainingSet;
				
	delete [] testSet;
	delete [] targetTestSet;
			
	fsalida.close();
}

