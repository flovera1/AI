struct SNeuron
{
	// the number of inputs into the neuron
	int m_NumInputs;
	// the weights for each input
	vector<double> m_vecWeight;
	//constructor
	SNeuron(int NumInputs);
};