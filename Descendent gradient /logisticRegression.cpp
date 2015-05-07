/**
* @description: this code is used to demostrate the logic regression algorithm. Which is also 
*               very similar to lineal regression. 
*               The only difference is that the hypothesis change. In logic regression, the hypothesis is:
*                     h(x) = 1 / 1 + (e)^theta*x
*               In lineal regression the hypothesis was:
*                     h(x) = ThetaT(transpose) * x
*	
*	  	 	 	
* @author: Fernando Lovera flovera1@gmail.com
* @Date: Thu 7 May 2015
*/
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <stdio.h>
// basic file operations
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;
double a, b;
double theta0 = 0.0;
double theta1 = 0.0;
double e      = 2.71828;
double myrand() {
  return rand() % 10;
}
double f(double x) {
  double y = a * x + b;
  return y;
}
/*
Hypothesis function, which tries to predict
the f values.
*/
double h(double x) {
  double product = theta1 * x + theta0;
  double aux = 1 + pow (e, product);
  return 1 / aux;

}
int main() {
  srand(time(NULL));
  /*
  generate random numbers for the equation of the line
  used in f function.
  */
  a     = myrand();
  b     = myrand();
  printf("set parameters: a = %lf, b = %lf\n", a, b);
  int N = 10000;
  vector<double> xs(N);
  vector<double> ys(N);
  ofstream myfile0;
  ofstream myfile1;
  myfile0.open ("hypothesis.dat");
  myfile1.open ("gradientDescending.dat");
  for (int i = 0; i < N; ++i) {
    xs[i] = myrand();
    ys[i] = f(xs[i]);
  	myfile0 << xs[i] << " " << ys[i] << "\n";
  }
  double learninRate = 0.010;
  double d0, d1;
  for (int n = 0; n < N; ++n) {
    d0 = 0.0;
    d1 = 0.0;
    for (int i = 0; i < N; ++i) {
      d0 += h(xs[i]) - ys[i];
      d1 += (h(xs[i]) - ys[i]) * xs[i];
    }
    theta0 -= (learninRate/N) * d0;
    theta1 -= (learninRate/N) * d1;
    printf("theta1: %lf, theta0: %lf\n", theta1, theta0);
    myfile1 << theta0 << " " << theta1 << "\n";
  }
  myfile0.close();
  myfile1.close();
  return 0;
}