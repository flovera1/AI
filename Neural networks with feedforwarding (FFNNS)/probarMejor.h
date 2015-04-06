/**
* @description:probarMejor is a program in which is implemented a neural network to solve a problem.
*              The number of neurons vary from 2 to 10 in order to stablish some tests.
*			   ONE OF THE OBJECTIVES OF THIS is that you can vary the number of neurons and the 
*              the number of iterations in your program, once you do that, you know the optimus
*              quantity of neurons and iterations to your problem.
* @authored: Fernando Lovera flovera1@gmail.com
* @date and place: Thu 2 Apr 
*/
#ifndef __probarMejor
#define __probarMejor
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
	#define NUM_CASOS_PRUEBA 500
	#define NOMBRE_ARCHIVO_CASOS_PRUEBA NUM_CASOS_PRUEBA.txt
	using namespace std;
	class Red {
	  double ** weigth_input_layer; //Basically the first index refers to the hidden neuron and the second to the input layer
	  double * weigth_output_layer; //So, we need several resoluts, a vector is required then
	  int num_nodes;
	  double tasaAprendizaje;
	  public:
			Red(int num_nodes, double tasaAprendizaje);//constructor
			~Red();//destructore
			/*
			* @desc: implementation of the back-prop learning algorithm 
			*        in which backpropagation is used. See T. Mitchell's book
			* @param valor_entrada: 
			* @param valores_intermedios: 
			*/
			double feed_forward(double * valor_entrada, double * valores_intermedios);
			
			double net(double* weight, double* input, int n);
			inline double sigmoid(double y);
			double error_output(double output, double target);
			double resolve_case(double x_in, double y_in, double target);
			void resolve_set_cases(double* x, double* y, double* target, int size_arrays);
			void runTestCase(double X, double Y, double T);
			double calcularSalida(double x, double y);
	};
#endif