#include <vector>
#import "SNeuron.h"
struct SNueronLayer{
	//the number of neurons in this layer
	int m_NumNeurons;
	//the layer of neurons
	vector<SNeuron> m_vecNeurons;
	SNeuronLayer(int NumNeurons, int NumInputsPerNeuron);
};