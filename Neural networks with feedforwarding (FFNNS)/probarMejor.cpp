#include "probarMejor.h"
double Red::sigmoid(double y){
	return 1/(1+exp(-y));
}
double Red::error_output(double output, double target){
	return output*(1-output)*(target-output);
}
Red::Red(int num_nodes, double tasaAprendizaje){ //constructor
	this->num_nodes = num_nodes;
	this-> tasaAprendizaje = tasaAprendizaje;
	
	weigth_output_layer = new double[num_nodes+1];
	weigth_input_layer = new double* [NumNodosEntrada+1];
	
	const long max_rand = 1000000;
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
Red::~Red(){
	for (int i =0; i<NumNodosEntrada+1;i++){
		delete(weigth_input_layer[i]);
	}
	delete(weigth_input_layer);
	delete(weigth_output_layer);
};
double  Red:: feed_forward(double * valor_entrada, double * valores_intermedios){
	double acum;
	for(int i = 0; i < num_nodes; i++){
		//Calculo de net
		acum = 0;
		for (int j = 0 ; j < NumNodosEntrada; j++){
			/**
			*i refers to the hidden neuron (hidden neuron).
			*j refers to the neurons in the input layer (input neuron).
			*/
			acum += weigth_input_layer[j][i]*valor_entrada[j]; 
		}	
		// Aplicacion de la funcion sigmoidal. 
		valores_intermedios[i] = sigmoid(acum+weigth_input_layer[NumNodosEntrada][i]);
	}
	//calculo del valor final
	acum = 0;
	for(int k = 0; k < num_nodes; k++){	
		acum += weigth_output_layer[k]*valores_intermedios[k];
	}
	return sigmoid(acum + weigth_output_layer[num_nodes]);
}  
double  Red:: calcularSalida(double x, double y){
	double acum;
	double valor_entrada [2];
	valor_entrada[0] = x;
	valor_entrada[1] = y;
	double valores_intermedios [num_nodes];
	for(int i = 0; i < num_nodes; i++){
		//Calculo de net
		acum =0;
		for (int j = 0 ; j < NumNodosEntrada; j++){
			acum+=weigth_input_layer[j][i]*valor_entrada[j];
		}	
		// Aplicacion de la funcion sigmoidal. 
		valores_intermedios[i] = sigmoid(acum+weigth_input_layer[NumNodosEntrada][i]);
	}
	//calculo del valor final
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
	//Calculo del error de la capa de salida.
	error_salida = error_output(valor_salida, target);
	double acum;
	//Calculo de error de cada neurona intermedia
	for(int i = 0; i < num_nodes; i++){
		acum = 0; 
		for(int j=0; j < num_nodes+1; j++){
			acum += weigth_output_layer[j]*error_salida;
		}
		error_intermedios[i] =  valores_intermedios[i]*(1-valores_intermedios[i])*acum;
	}
	//Actualizar pesos de la capa intermedia a la de salida
	for(int i = 0 ; i < num_nodes; i++){
		weigth_output_layer[i] += tasaAprendizaje*error_salida*valores_intermedios[i];
	}
	weigth_output_layer[num_nodes] += tasaAprendizaje*error_salida;
	//Actualizar pesos de la capa de entrada a la capa de salida. 
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
//entrenamiento
void Red::resolve_set_cases(double* x, double* y, double* target, int size_arrays){	
	for(int i = 0; i<size_arrays; i++){		
		resolve_case(x[i], y[i], target[i]);//el target se inicializa en el main
	}
}
double pertenece(double a, double b){
	if ((10-a)*(10-a) + (8-b)*(8-b)<=9)
		return 1;
	return 0;
}
int main(){	
	string line;
	ifstream myfile ("500b.txt");
	double x [NUM_CASOS_PRUEBA];
	double y [NUM_CASOS_PRUEBA];
	double t [NUM_CASOS_PRUEBA];
	if (myfile.is_open()){
		for (int i = 0; i< NUM_CASOS_PRUEBA;i++){
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
	else{ 
		cout << "Unable to open file"; 
	}
	double result          = 0;
	double tasaCorrecto    = 0;
	double tasaCorrectoMax =0;
	int numNeuronasMax     =0;
	int numIteracionesMax  = 0;
	int numCorrectos       = 0;
	int numIt [5]          = {100,1000,5000,10000,50000};		
	for (int numNeuronas = 2; numNeuronas<=10;numNeuronas++){
		cout << "Probando con: " << numNeuronas << " neuronas." << endl;
		for (int numIteraciones = 0; numIteraciones<5; numIteraciones++){
			cout << "Probando con: " << numIt[numIteraciones]<< " iteraciones." << endl <<endl;
			Red red = Red(numNeuronas, 0.005);
			for(int u = 0; u < numIt[numIteraciones]; u++){
				red.resolve_set_cases(x, y, t, NUM_CASOS_PRUEBA);
			}
			numCorrectos = 0;
		for(int cx = 0; cx < 100; cx++){
				for(int cy = 0; cy<100; cy++){		
				double coorX = (double) cx/100*20;
				double coorY = (double) cy/100*12;
				result = red.calcularSalida(coorX,coorY);
				if (result>.5){
					result =1;
				}
				else{
					result =0;
				}	
				if (pertenece(coorX,coorY)==result){
					numCorrectos++;
				}
			}	
		}
		tasaCorrecto = (double) numCorrectos/10000;
			
		if (tasaCorrecto>tasaCorrectoMax){
			tasaCorrectoMax = tasaCorrecto;
			numIteracionesMax = numIt[numIteraciones];
			numNeuronasMax = numNeuronas;
			cout << "Tasa correctos max:"<<tasaCorrecto <<endl;
			cout << "Num iteraciones max:"<<numIteracionesMax <<endl;
			cout << "Num neuronas max:"<< numNeuronasMax <<endl;				
			cout << endl;
		}
	}
}
	cout << "FINAL"<<endl;
	cout << "Tasa correctos max:"<<tasaCorrectoMax <<endl;
	cout << "Num iteraciones max:"<<numIteracionesMax <<endl;
	cout << "Num neuronas max:"<< numNeuronasMax <<endl;
return 0;
}


