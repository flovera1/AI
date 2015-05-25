#include <iostream>
#include <cmath>
#include <ctime>
#include <cstdlib>
using namespace std;
const int numInputs          = 3;    // Number of input nodes, + the bias input
const int numPatterns        = 4;    // Input patterns for XOR experiment
const int numHidden          = 4;
const int numEpochs          = 200;
const double LR_IH           = 0.7;  // learning rate, input to hidden weights.
const double LR_HO           = 0.07; // learning rate, hidden to output weights.
int patNum                   = 0;
double errThisPat            = 0.0;
double outPred               = 0.0; // "Expected" output values
double RMSerror              = 0.0; // Root mean squared error.
double hiddenVal[numHidden]  = {0.0}; // hidden node outputs
double weightsIH[numInputs][numHidden]; // input to Hidden weights the x's are the input an y's are the weights
double weightsHO[numHidden]  = {0.0}; // Hidden to Output weights.
int trainInputs[numPatterns][numInputs];
int trainOutput[numPatterns]; // "actual" output values
//Functions prototypes
void initWeights();
void calcNet();
void WeightChangesHO();
void WeightChangesIH();
void calcOverallError();
void initData();
void displayResults();
double getRand();
int main(){
	srand((unsigned)time(0)); //seed the generator with system time.
	initWeights();
	initData();
	// train the Network
	for(int j = 0; j <= numEpochs; j++){
		for(int i = 0; i <= numPatterns; i++){
			// select a pattern at random
			patNum = rand() % numPatterns;
			// calculate the output and error for this pattern
			calcNet();
			//Adjust network weights
			WeightChangesHO();
			WeightChangesIH();
		}
		calcOverallError();
		// display the overall network error after each epoch
		cout << "epoch = " << j << "RMS Error = " << RMSerror << endl;
	}
	// training has finished
	displayResults();
	return 0;
}

void initWeights(){
	// initialize weights to random values
	for(int j = 0; j < numHidden; j++){
		weightsHO[j] = (getRand() - 0.5 / 2);
		for(int i = 0; i < numInputs; i++){
			weightsIH[i][j] = (getRand() - 0.5) / 5;
			cout << "Weight = " << weightsIH[i][j] << endl;
		}
	}
}
void initData(){
	/*
	*	the data here is XOR data which has been
	*   rescaled to the range -1 to 1
	* 	An extra input vale of 1 is also added to act as
	*   the bias.
	* 	The output must lie in the range -1 to 1.
	*	The 0 is like -1
	*	1 xor 1   = -1 = 0
	*	1 xor -1  = 1 
	*	-1 xor -1 = -1
	*	-1 xor 1  = 1
	*/
	trainInputs[0][0]   =  1;
    trainInputs[0][1]   = -1;
    trainInputs[0][2]   =  1; // Bias
    trainOutput[0]      =  1;

    trainInputs[1][0]   = -1;
    trainInputs[1][1]   =  1;
    trainInputs[1][2]   =  1; // Bias
    trainOutput[1]      =  1;

    trainInputs[2][0]   =  1;
    trainInputs[2][1]   =  1;
    trainInputs[2][2]   =  1; // Bias
    trainOutput[2]      = -1;

    trainInputs[3][0]   = -1;
    trainInputs[3][1]   = -1;
    trainInputs[3][2]   =  1; // Bias
    trainOutput[3]      = -1;
}
void calcNet(){
	// Calculates values for Hidden and Output nodes.
	//numHidden is the number of neurons hidden (4 in this case).
	//hiddenVal is the output of the neuron.
	/*
	* first calculate the output of the hidden neuron
	*/
    for(int i = 0; i < numHidden; i++){
	  hiddenVal[i] = 0.0;
        for(int j = 0; j < numInputs; j++){
	        hiddenVal[i] = hiddenVal[i] + (trainInputs[patNum][j] * weightsIH[j][i]);
        }
        hiddenVal[i] = tanh(hiddenVal[i]); // tangent with x radians
    }
    outPred = 0.0;
    for(int i = 0; i < numHidden; i++){
        outPred = outPred + hiddenVal[i] * weightsHO[i];
    }
    //Calculate the error: "Expected" - "Actual"
    errThisPat = outPred - trainOutput[patNum];
}
void WeightChangesHO(){
//Adjust the Hidden to Output weights.
    for(int k = 0; k < numHidden; k++){
        double weightChange = LR_HO * errThisPat * hiddenVal[k];
        weightsHO[k] = weightsHO[k] - weightChange;

        // Regularization of the output weights.
        if (weightsHO[k] < -5){
            weightsHO[k] = -5;
        }else if (weightsHO[k] > 5){
            weightsHO[k] = 5;
        }
    }
}
void WeightChangesIH(){
	// Adjust the Input to Hidden weights.
    for(int i = 0; i < numHidden; i++){
        for(int k = 0; k < numInputs; k++){
            double x            = 1 - (hiddenVal[i] * hiddenVal[i]);
            x                   = x * weightsHO[i] * errThisPat * LR_IH;
            x                   = x * trainInputs[patNum][k];
            double weightChange = x;
            weightsIH[k][i]     = weightsIH[k][i] - weightChange;
        }
    }
}
void calcOverallError(){
    RMSerror = 0.0;

    for(int i = 0; i < numPatterns; i++){
         patNum = i;
         calcNet();
         RMSerror = RMSerror + (errThisPat * errThisPat);
    }

    RMSerror = RMSerror / numPatterns;
    RMSerror = sqrt(RMSerror);
}
void displayResults(){
    for(int i = 0; i < numPatterns; i++){
        patNum = i;
        calcNet();
        cout << "pat = " << patNum + 1 << 
                " actual = " << trainOutput[patNum] << 
                " neural model = " << outPred << endl;
    }
}
double getRand(){
	return double(rand() / double(RAND_MAX));
}


