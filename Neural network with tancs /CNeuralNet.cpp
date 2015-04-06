#include "CNeuralNet.h"
#import "SNeuronLayer.h"
#import "SNeuron.h"
/**
* @descr
*/
CNeuralNet::CNeuralNet() {
	// put the values from parameters in here
	m_NumInputs	          =	CParams::iNumInputs;
	m_NumOutputs		  =	CParams::iNumOutputs;
	m_NumHiddenLayers	  =	CParams::iNumHidden;
	m_NeuronsPerHiddenLyr =	CParams::iNeuronsPerHiddenLayer;
	//create the layers of the network
	if (m_NumHiddenLayers > 0){
	  	/**
	  	* create first hidden layer
	  	* with the number of neurons(first parameter) and
	  	* the number of inputs per neuron(second parameter). But just the first layer.
	  	*/
		m_vecLayers.push_back(SNeuronLayer(m_NeuronsPerHiddenLyr, m_NumInputs));
	    for(int i=0; i<m_NumHiddenLayers-1; ++i){
	    /**
	    * create the hidden layers(You don't know how many layers are the optimal)
	    * normally 1.
	    */
				m_vecLayers.push_back(SNeuronLayer(m_NeuronsPerHiddenLyr,
	                                         m_NeuronsPerHiddenLyr));
		}
	    //create output layer
		  m_vecLayers.push_back(SNeuronLayer(m_NumOutputs, m_NeuronsPerHiddenLyr));
	}else{
	  //create output layer
	  m_vecLayers.push_back(SNeuronLayer(m_NumOutputs, m_NumInputs));
  }
}
vector<double> CNeuralNet::GetWeights() const{
	//this will hold the weights
	vector<double> weights;
	//for each layer
	for (int i=0; i<m_NumHiddenLayers + 1; ++i){
		//for each neuron
		for (int j=0; j<m_vecLayers[i].m_NumNeurons; ++j){
			//for each weight
			for (int k=0; k<m_vecLayers[i].m_vecNeurons[j].m_NumInputs; ++k){
				weights.push_back(m_vecLayers[i].m_vecNeurons[j].m_vecWeight[k]);
			}
		}
	}
	return weights;
}
void CNeuralNet::PutWeights(vector<double> &weights){
	int cWeight = 0;
	//for each layer
	for (int i = 0; i < m_NumHiddenLayers + 1; ++i){
		//for each neuron
		for (int j = 0; j < m_vecLayers[i].m_NumNeurons; ++j){
			//for each weight
			for (int k = 0; k < m_vecLayers[i].m_vecNeurons[j].m_NumInputs; ++k){
				m_vecLayers[i].m_vecNeurons[j].m_vecWeight[k] = weights[cWeight++];
			}
		}
	}
}
int CNeuralNet::GetNumberOfWeights() const{
	int weights = 0;
	//for each layer
	for (int i  = 0; i < m_NumHiddenLayers + 1; ++i){
		//for each neuron
		for (int j = 0; j < m_vecLayers[i].m_NumNeurons; ++j){
			//for each weight
			for (int k = 0; k < m_vecLayers[i].m_vecNeurons[j].m_NumInputs; ++k){
				weights++;
			}
			
		}
	}
	return weights;
}

//-------------------------------Update-----------------------------------
//
//	given an input vector this function calculates the output vector
//
//------------------------------------------------------------------------
vector<double> CNeuralNet::Update(vector<double> &inputs)
{
	//stores the resultant outputs from each layer
	vector<double> outputs;

	int cWeight = 0;
	
	//first check that we have the correct amount of inputs
	if (inputs.size() != m_NumInputs)
  {
		//just return an empty vector if incorrect.
		return outputs;
  }
	
	//For each layer....
	for (int i=0; i<m_NumHiddenLayers + 1; ++i)
	{		
		if ( i > 0 )
    {
			inputs = outputs;
    }

		outputs.clear();
		
		cWeight = 0;

		//for each neuron sum the (inputs * corresponding weights).Throw 
		//the total at our sigmoid function to get the output.
		for (int j=0; j<m_vecLayers[i].m_NumNeurons; ++j)
		{
			double netinput = 0;

			int	NumInputs = m_vecLayers[i].m_vecNeurons[j].m_NumInputs;
			
			//for each weight
			for (int k=0; k<NumInputs - 1; ++k)
			{
				//sum the weights x inputs
				netinput += m_vecLayers[i].m_vecNeurons[j].m_vecWeight[k] * 
                    inputs[cWeight++];
			}

			//add in the bias
			netinput += m_vecLayers[i].m_vecNeurons[j].m_vecWeight[NumInputs-1] * 
                  CParams::dBias;

			//we can store the outputs from each layer as we generate them. 
      //The combined activation is first filtered through the sigmoid 
      //function
			outputs.push_back(Sigmoid(netinput,
                                CParams::dActivationResponse));

			cWeight = 0;
		}
	}

	return outputs;
}

//-------------------------------Sigmoid function-------------------------
//
//------------------------------------------------------------------------
double CNeuralNet::Sigmoid(double netinput, double response)
{
	return ( 1 / ( 1 + exp(-netinput / response)));
}


