/*
* @authored: Fernando Lovera
* @description:
*  	 	 	 	SUMx: The sum of all x values of the points
* 	    	  	SUMy: The sum of all y values of the points.
* 	  	 	 	SUMxx: The sum of the square of x values meaning that we square x vales 
*	  	 	  	 	   individually and add them togethers.
* 	      	 	SUMxy: for each point we multiply its x value with its y value, then add all the 
*	  	  	 	  	   results together to find this sum.
*	 	 		The first thing is to calculate the sums simultaneously. 
*				Then, calculate the means of x and y values (kind of the average).
*	 			slope and y_intercept of the best-fit function can be determined using the means
* 	 	 	 	and the sums we found. 
*/
#include <iostream>
#include <cmath>
#include <stdio.h>
using namespace std;

float x[15];
float y[15];
void leastSqrRegression(int dataSize){
	double SUMx        = 0;
	double SUMy        = 0;
	double SUMxy       = 0; 
	double SUMxx       = 0; // sum of x^2
	double SUMres      = 0;
	double res         = 0;
	double slope       = 0;
	double y_intercept = 0; //y intercept of regression line
	double SUM_Yers    = 0; //sum squarred of the error
	double AVGy        = 0; //average y 
	double AVGx        = 0; //average x
	double Yres        = 0; //squarred errors
	double Rsqr        = 0; // coeficient of determination
	for(int i = 0; i < dataSize; i++){
		//sum of x's, y's and squared x*y
		SUMx  += x[i];
		SUMy  += y[i];
		SUMxy += x[i] * y[i];
		SUMxx += x[i] * x[i];
	}
	//calculate the means 
	AVGx        = SUMx / dataSize;
	AVGy        = SUMy / dataSize;
	slope       = (dataSize * SUMxy - SUMx*SUMy) / (dataSize * SUMxx - SUMx*SUMx);
	y_intercept = AVGy - slope * AVGx;
	printf("x mean(AVGx) = %0.5E\n", AVGx);
	printf("y mean(AVGy) = %0.5E\n", AVGy);
	printf("\n");
	printf("The linear equation that best fits the given data: \n");
 	printf ("       y = %2.8lfx + %2.8f\n", slope, y_intercept);
 	printf("------------------------------\n");
   	printf ("------------------------------------------------------------\n");
   	printf ("   Original (x,y)   (y_i - y_avg)^2     (y_i - a_o - a_1*x_i)^2\n");
   	printf ("------------------------------------------------------------\n");
   	for(int i = 0; i < dataSize; i++){
   		Yres = pow(y[i] - y_intercept - (slope * x[i]), 2);
   	    //sum of (y_i - a0 - a1 * x_i)^2
      	SUM_Yers += Yres;
      	//current residue squared (y_i - AVGy)^2
      	res = pow(y[i] - AVGy, 2);
      	//sum of squared residues
      	SUMres += res;
      	printf ("   (%0.2f %0.2f)      %0.5E         %0.5E\n", x[i], y[i], res, Yres);
   	}
   //calculate r^2 coefficient of determination
   Rsqr = (SUMres - SUM_Yers) / SUMres;
   printf("--------------------------------------------------\n");
   printf("Sum of (y_i - y_avg)^2 = %0.5E\t\n", SUMres);
   printf("Sum of (y_i - a_o - a_1*x_i)^2 = %0.5E\t\n", SUM_Yers);
   printf("Standard deviation(St) = %0.5E\n", sqrt(SUMres / (dataSize - 1)));
   printf("Standard error of the estimate(Sr) = %0.5E\t\n", sqrt(SUM_Yers / (dataSize-2)));
   printf("Coefficent of determination(r^2) = %0.5E\t\n", (SUMres - SUM_Yers)/SUMres);
   printf("Correlation coefficient(r) = %0.5E\t\n", sqrt(Rsqr));
}
int main(){
	int totalOfPoints = 15;
	for(int i = 0; i < totalOfPoints; i++){
		x[i]         = rand() % 5;
		y[i]         = rand() % 5;
	}
	leastSqrRegression(totalOfPoints);
	
	return 0;
}

