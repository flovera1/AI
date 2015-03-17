/*
* Adaline neuron.
* Note: the difference between adaline and perceptron is the way 
* in which adaline change the weights, with this method, the weight is changed
* in according to the sum of the weighted sum of inputs(the net), in perceptron
* the net is passed to the function and the function's output is the one used
* to changed the weights.
* @Fernando Lovera.
* @Caracas, Venezuela.
* 17 Marzo 2014.
*/
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;
//########################### Adaline
#define X1 0
#define X2 1
#define T 2
#define ITERACIONES_MAXIMAS 10000000
//###########################
#define EPSILON  0.01
#define AND 0
#define OR 1
#define XOR 2
#define ABS(X) (((X)<0)?(-(X)):(X))
class Adaline {
		double tasaAprendizaje;
		#define x0 1;
		int numCambiosPeso;
  public:
		double w0, w1, w2; //weights
		Adaline(double tasaAprendizaje, double w1, double w2, double umbral);
		int procesarEntradaSinEntrenamiento(double x1, double x2);
		void entrenarLotes(int trainingSet [][3], int tamano,double epsilon, bool cambiarTasa);//batch training
		void entrenarIncremental(int trainingSet [][3], int tamano,double epsilon, bool cambiarTasa);//
		double calcularO(double x1, double x2);
		void cambiarPesos(double o, double target, double x1, double x2);
		int getNumCambiosPeso();
};
int Adaline::getNumCambiosPeso(){
			return numCambiosPeso;
}
//checked constructor
Adaline::Adaline(double tasaAprendizaje, double w1, double w2, double umbral){
	this->tasaAprendizaje = tasaAprendizaje;
	this->w1              = w1;
	this->w2              = w2;
	this->w0              = umbral;
	numCambiosPeso        = 0;
}
//checked. O function, weights and inputs values.
double Adaline:: calcularO(double x1, double x2){
	return (x1 * this->w1 )+(x2 * this->w2) +w0;
}
void Adaline:: entrenarIncremental(int trainingSet [][3], int tamano, 
								double epsilon, bool cambiarTasaAprendizaje){
	double error       = 0;
	double deltaW [3];
	int numIteraciones = 0;
	int o,gradiente;
	double tasaAprend  = this->tasaAprendizaje;
	do{
			numIteraciones++;
			if (numIteraciones > ITERACIONES_MAXIMAS){
				cout << "  Se ha alcanzado el numero maximo de iteraciones" << endl;
				break;
			}
			if (cambiarTasaAprendizaje){
				tasaAprend = this->tasaAprendizaje/(numIteraciones + 1);
			}
			error          = 0;
			for (int i = 0; i<3; i++){
				deltaW[i]  = 0;
			}
			/* iterate over the training set.
			*  You change the weiths in every loop.
			*/
			for (int i = 0; i<tamano; i++){
				o         = calcularO(trainingSet[i][X1], trainingSet[i][X2]);
				gradiente = trainingSet[i][T] - o;
				error    += gradiente*gradiente;
				numCambiosPeso++;
				w0       += tasaAprend*gradiente* x0;
				w1       += tasaAprend*gradiente* trainingSet[i][0];		 
				w2       += tasaAprend*gradiente* trainingSet[i][1];
			}	
		    cout << "Error en la iteracion: " << numIteraciones << error << endl;	
	} while (error>EPSILON);
}
void Adaline:: entrenarLotes(int trainingSet [][3], int tamano, double epsilon, bool cambiarTasaAprendizaje){
	double error       = epsilon + 1;
	double errorViejo;
	double deltaW [3];
	double  o,diferencia;
	int numIteraciones = 0;
	double tasaAprend  = tasaAprendizaje;
	do{
		numIteraciones++;
		if (numIteraciones > ITERACIONES_MAXIMAS){
			//cout << "  Se ha alcanzado el numero maximo de iteraciones" << endl;
			break;
		}
			if (cambiarTasaAprendizaje){
				tasaAprend = this->tasaAprendizaje/(numIteraciones);
			}
			errorViejo     = error;
			error          = 0;
			for (int i = 0; i<3; i++){
				deltaW[i]  = 0;
			}
			/** Iterar sobre el training set.
			*   You changed the weights after you found the delta error.
			*/
			for (int i = 0; i<tamano; i++){
				o          = calcularO(trainingSet[i][X1], trainingSet[i][X2]);
				diferencia = trainingSet[i][T] - o;
				error     += diferencia*diferencia/2;
				deltaW[0] += tasaAprend*diferencia;
				deltaW[1] += tasaAprend*diferencia* trainingSet[i][X1];		 
				deltaW[2] += ∫tasaAprend*diferencia* trainingSet[i][X2];
			}	
			numCambiosPeso++;
			w0 = w0 + deltaW[0];
			w1 = w1 + deltaW[1];
			w2 = w2 + deltaW[2];
	} while (ABS(error-errorViejo)>epsilon);
	cout << "Error: " << ABS(error) << ", diferencia: " << ABS(error-errorViejo) << " y " << numIteraciones << " iteraciones." << endl;
} 
/** 
 * returns an int: 1 if the o is 1; 0 if the value of o is -1
 */
int Adaline:: procesarEntradaSinEntrenamiento(double x1, double x2)
{
	if ((x1*w1+x2*w2) > -1*w0)
		return 1;
	else
		return -1;
}	

int main()
{
	// Generar training set y pesos/Generate the training set and weights
	const long max_rand = 1000000;
	clock_t comienzo;
	comienzo            = clock();
	srandom(time(NULL));
	double w1           = (double) (random() % max_rand) / max_rand;
	double w2           = (double) (random() % max_rand) / max_rand;
	double umbral       = .5;
	// Generar trainign set.
	int trainingSet [4][3][3];
	for (int i = 0; i <3; i++){
		trainingSet[0][i][X1] = 0;
		trainingSet[1][i][X1]  = 0;
		trainingSet[2][i][X1] = 1;
		trainingSet[3][i][X1] = 1;
		trainingSet[0][i][X2] = 1;
		trainingSet[1][i][X2] = 0;
		trainingSet[2][i][X2] = 1;
		trainingSet[3][i][X2] = 0;
	}	
	for (int i =0; i<4; i++){
		if (trainingSet[i][AND][X1]&&trainingSet[i][AND][X2])
			trainingSet[i][AND][T] = 1;
		else
			trainingSet[i][AND][T] = -1;
		if (trainingSet[i][OR][X1]||trainingSet[i][OR][X2])
			trainingSet[i][OR][T]  = 1;
		else
			trainingSet[i][OR][T]    = -1;
		if (trainingSet[i][XOR][X1] !=trainingSet[i][XOR][X2])
			trainingSet[i][XOR][T]   = 1;
		else
			trainingSet[i][XOR][T]   = -1;			
	}
	cout << "-------------------------------------------" << endl
		 << "Pruebas variando las tasas de aprendizaje" << endl;	 
	const int iteraciones = 8;
	double tasaAprend [8] = { 0.01, 0.05, 0.1, 0.2, 0.3, 0.4, 0.5, 0.99 };
	//i itera sobre las operaciones: AND=0, OR=1,XOR=2 / iterate over the 
	for(int i = 0; i < 2; i++){
		cout << endl << "Para la operacion: " << i << endl <<endl;
		// Entrenamiento
		int tSet[4][3];
		for (int k = 0; k< 4; k++){
			tSet[k][X1] = trainingSet[k][i][X1];
			tSet[k][X2] = trainingSet[k][i][X2];
			tSet[k][T]  =  trainingSet[k][i][T];
		}
		for (int j = 0; j<iteraciones;j++){
			Adaline p = Adaline(tasaAprend[j], w1, w2, umbral);
			int tSet[4][3];
			for (int k = 0; k< 4; k++){
				tSet[k][X1] = trainingSet[k][i][X1];
				tSet[k][X2] = trainingSet[k][i][X2];
				tSet[k][T]  =  trainingSet[k][i][T];
			}
			p.entrenarLotes(tSet, 4, EPSILON, false);
			// Prueba.
			int clasificadosCorrectamente= 0;
			for(int k = 0; k< 4;k++){
				if (tSet[k][T] == p.procesarEntradaSinEntrenamiento(tSet[k][X1], tSet[k][X2]))
					clasificadosCorrectamente++;
			}		
			cout << " con tasa de aprendizaje: " << tasaAprend[j] 
					<< " la tasa de error fue: " << 
					(double) (4-clasificadosCorrectamente)/4 << endl;
		}
		Adaline p = Adaline(.99, w1, w2, umbral);
		// Prueba.
		int clasificadosCorrectamente = 0;
		for(int k = 0; k< 4;k++){
			if (tSet[k][T] == p.procesarEntradaSinEntrenamiento(tSet[k][X1], tSet[k][X2])){
				clasificadosCorrectamente++;
			}
		}	
		cout << " con tasa de aprendizaje decayendo: la tasa de error fue: " << 
		     (double) (4-clasificadosCorrectamente)/4 << endl;	
	}
	/*
	// Experimento 1: Cambiar las tasas de aprendizaje.
	
	cout << "-------------------------------------------" << endl
		 << "Pruebas variando la tasa de aprendizaje." << endl;
		 
	for (int k = 0; k<8;k++) {
		cout << endl << "Con tasa de aprendizaje: " << tasaAprend[k] << endl <<endl; 
		for(int i = 0; i < 3; i++){
		
			Adaline a= Adaline(tasaAprend[k],w1,w2,umbral);
			int trainingSet[SIZE_TRAININGSET_1][3];
			for (int j = 0; j< SIZE_TRAININGSET_1; j++){
	
				trainingSet[j][X1] = trainingSet1[j][i][X1];
				trainingSet[j][X2] = trainingSet1[j][i][X2];
				trainingSet[j][T] =  trainingSet1[j][i][T];
			}
	
			a.entrenarLotes(trainingSet,SIZE_TRAININGSET_1,EPSILON,false);			
			
			// Prueba.
			int clasificadosCorrectamente= 0;
			for(int j = 0; j< SIZE_TESTSET;j++){
				if (testSet[j][i][T] == a.procesarEntradaSinEntrenamiento(
												testSet[j][i][X1], 
												testSet[j][i][X2]))
					clasificadosCorrectamente++;
			 else cout << testSet[j][i][T] << "  " << a.procesarEntradaSinEntrenamiento(
												testSet[j][i][X1], 
												testSet[j][i][X2]) << endl;
			}
			cout << " Para la operacion:" << i << " la tasa de error fue: " 
				 << (double) (SIZE_TESTSET-clasificadosCorrectamente)/SIZE_TESTSET << endl;
		}
	}
	
	// Experimento 2: hacer que la tasa de aprendizaje decaiga.
	
	cout << "-------------------------------------------" << endl
		 << "Pruebas haciendo que la tasa decaiga." << endl;
		 
	for(int i = 0; i < 3; i++){
		
		Adaline a= Adaline(0.99,w1,w2,umbral);
		int trainingSet[SIZE_TRAININGSET_1][3];
		for (int j = 0; j< SIZE_TRAININGSET_1; j++){
				trainingSet[j][X1] = trainingSet1[j][i][X1];
			trainingSet[j][X2] = trainingSet1[j][i][X2];
			trainingSet[j][T] =  trainingSet1[j][i][T];
		}
			a.entrenarLotes(trainingSet,SIZE_TRAININGSET_1,EPSILON,true);			
		
		// Prueba.
		int clasificadosCorrectamente= 0;
		for(int j = 0; j< SIZE_TESTSET;j++){
			if (testSet[j][i][T] == a.procesarEntradaSinEntrenamiento(
											testSet[j][i][X1], 
											testSet[j][i][X2]))
				clasificadosCorrectamente++;
			}
		
		cout << " Para la operacion:" << i << " la tasa de error fue: " 
			 << (double) (SIZE_TESTSET-clasificadosCorrectamente)/SIZE_TESTSET << endl;
	}
	
	// Experimento 3: probar con aprendizaje incremental y por lotes.
	
	cout << "-------------------------------------------" << endl
		 << "Pruebas con aprendizaje incremental y por lote" << endl;
		 
	for(int i = 0; i < 3; i++){
		
		Adaline aLote= Adaline(0.99,w1,w2,umbral);
		Adaline aIncremental= Adaline(0.99,w1,w2,umbral);
		
		int trainingSet[SIZE_TRAININGSET_1][3];
		for (int j = 0; j< SIZE_TRAININGSET_1; j++){
				trainingSet[j][X1] = trainingSet1[j][i][X1];
			trainingSet[j][X2] = trainingSet1[j][i][X2];
			trainingSet[j][T] =  trainingSet1[j][i][T];
		}
			aLote.entrenarLotes(trainingSet,SIZE_TRAININGSET_1,EPSILON,true);			
			aIncremental.entrenarIncremental(trainingSet,SIZE_TRAININGSET_1,EPSILON,true);			
		
		// Prueba.
		int clasificadosCorrectamenteLot= 0;
		int clasificadosCorrectamenteInc= 0;
		
		for(int j = 0; j< SIZE_TESTSET;j++){
			if (testSet[j][i][T] == aLote.procesarEntradaSinEntrenamiento(
											testSet[j][i][X1], 
											testSet[j][i][X2]))
				clasificadosCorrectamenteLot++;
			if (testSet[j][i][T] == aIncremental.procesarEntradaSinEntrenamiento(
											testSet[j][i][X1], 
											testSet[j][i][X2]))
				clasificadosCorrectamenteInc++;
		}
		
		cout << " Para la operacion:" << i << " con aprendizaje por lote " 
			 << " la tasa de error fue: " << 
			 (double) (SIZE_TESTSET-clasificadosCorrectamenteLot)/SIZE_TESTSET << endl;

		cout << "Se hicieron: " << aLote.getNumCambiosPeso() << " cambios en los pesos" 
			 << endl << endl;
			 
		cout << " Para la operacion:" << i << " con aprendizaje incremental " 
			 << " la tasa de error fue: " << 
			 (double) (SIZE_TESTSET-clasificadosCorrectamenteInc)/SIZE_TESTSET << endl;

		cout << "Se hicieron " << aIncremental.getNumCambiosPeso() << " cambios en los pesos" 
			 << endl << endl;
	}
	
	   printf( "Número de segundos transcurridos desde el comienzo del programa: %f s\n", (clock()-comienzo)/(double)CLOCKS_PER_SEC );
	   * 
	   */
	   return 0;
}
