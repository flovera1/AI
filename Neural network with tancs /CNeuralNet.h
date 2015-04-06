/**
  * @author      : Fernando Lovera flovera1@gmail.com
  * @description : Class for creating a feedforward neural net.
  * @date        : Mon 6 April     
  */
#ifndef CNEURALNET_H
#define CNEURALNET_H
	#include <vector>
	#include <fstream>
	#include <math.h>
	#include "utils.h"
	#include "CParams.h"
	#include "SNeuronLayer.h"
	#include "SNeuron.h"
	using namespace std;
	class CNeuralNet{
		private:
			int					m_NumInputs;
			int					m_NumOutputs;
			int					m_NumHiddenLayers;
			int					m_NeuronsPerHiddenLyr;
			//storage for each layer of neurons including the output layer
			vector<SNeuronLayer>	m_vecLayers;
		public:
			/**
				@description: Creates a ANN based on the default values in params.ini
							  The way to think about it is to do this:
							  1. create the input layers
							  2. create the hidden layers
							  3. create the output layers
			**/
			CNeuralNet();
			void CreateNet();
			/** 
			*	@description: gets the weights from the NN.
			*	              it returns a vector containing the weights.
			*/
			vector<double>	GetWeights()const;
			/**
			*   @description: returns total number of weights in net
			*/
			int	GetNumberOfWeights()const;
			/**
			*	@desciption: replaces the weights with new ones
			*				 given a vector of doubles this function 
			*				 replaces the weights in the NN with the new ones
			*/
			void			      PutWeights(vector<double> &weights);
			/**
			*   @description: After this method has checked  the validity of the 
			*                 input vector it enters a loop which examines each 
			*                 layer in turn. For each layer, it steps through the 
			*                 neurons in that layer and sums all the inputs multiplied 
			*                 by the corresponding weights. The last weight added in 
			*                 for each neuron is the bias (remember the bias is simply 
			*                 a weight always tied to the value -1.0).  
			*                 This value is then put through the sigmoid function to give 
			*                 that neurons output and then added to a vector which is fed 
			*                 back into the next iteration of the loop and so on until we 
			*                 have our output proper.
			*/
			vector<double>	Update(vector<double> &inputs);
			//sigmoid response curve
			inline double	  Sigmoid(double activation, double response);
	};
#endif