/*
* Perceptron program
*/
import java.util.*;
import java.io.*;
import java.text.*;
import java.math.*;

class perceptron{
	static int MAX_ITER         = 100;
	static double LEARNING_RATE = 100;
	static int NUM_INSTANCES    = 100;
	static int theta            = 0; // threshold
	public static void main (String args[]){
		// three variables (features)
		double [] x    = new double [NUM_INSTANCES];
		double [] y    = new double [NUM_INSTANCES];
		double [] z    = new double [NUM_INSTANCES];
		int [] outputs = new int [NUM_INSTANCES];
		//fifty random points of class 1
		for(int i = 0; i < NUM_INSTANCES/2; i++){
			x[i]       = randomNumber(5, 10);
			y[i]       = randomNumber(4, 8);
			z[i]       = randomNumber(2, 9);
			outputs[i] = 1;
			System.out.println(x[i] + "\t" + y[i] + "\t" + z[i] + "\t" + outputs[i]); 
		}
		//fifty random points of class 0
		for(int i = 50; i < NUM_INSTANCES; i++){
			x[i]       = randomNumber(-1, 3);
			y[i]       = randomNumber(-4, 2);
			z[i]       = randomNumber(-3, 5);
			outputs[i] = 0;
			System.out.println(x[i] + "\t" + y[i] + "\t" + z[i] + "\t" + outputs[i]); 		
		}
		double[] weights = new double[4]; // 3 for input variables and one for bias
		double localError, globalError;
		int i, p, iteration, output;
		weights[0] = randomNumber(0,1); // w1
		weights[1] = randomNumber(0,1); // w2
		weights[2] = randomNumber(0,1); // w3
		weights[3] = randomNumber(0,1); // this is the bias
		iteration  = 0;
		do{
			iteration++;
			globalError = 0;
			//loop through all instances (complete one epoch)
			for(p = 0; p < NUM_INSTANCES; p++){
				//calculate predicted class
				output     = calculateOutput(theta, weights, x[p], y[p], z[p]);
				//difference between predicted and actual class values
				localError = outputs[p] - output;
				//update the weights and bias
				weights[0] += LEARNING_RATE * localError + x[p];
				weights[1] += LEARNING_RATE * localError + y[p];
				weights[2] += LEARNING_RATE * localError + z[p];
				weights[3] += LEARNING_RATE * localError;
				//summation of squared error(error value for all instances)
				globalError+= (localError*localError);
			}
			/*Root mean squared error*/
			System.out.println("Iteration "+iteration+" : RMSE = "+ Math.sqrt(globalError/NUM_INSTANCES));
		}while(globalError != 0 && iteration <= MAX_ITER);
		System.out.println("\n ===================== \nDecision boundary equation:");
		System.out.println(weights[0] + "*x + " + weights[1] + "*y + "+weights[2]+ "*z + "+ weights[3]+" = 0");
		/*
		* generate 10 new random points and check their classes
		* notice the range of -10 and 10 means the new pont could be of class 1 or 0
		* -10 to 10 covers all the ranges we used in generating the 50 classes of 1's above
		*/
		for(int j = 0; j < 10; j++){
			double x1 = randomNumber(-10, 10);
			double y1 = randomNumber(-10, 10);
			double z1 = randomNumber(-10, 10);

			output    = calculateOutput(theta, weights, x1, y1, z1);
			System.out.println("\n===========\n New random point: ");
			System.out.println("x = "+x1+", y = "+y1+",z = "+z1);
			System.out.println("class = "+output);
		}
	}
	public static double randomNumber(int min, int max){
		DecimalFormat df = new DecimalFormat("#.###");
		double d         = min + Math.random() * (max - min);
		String s         = df.format(d);
		double x         = Double.parseDouble(s);
		return x;
	}
	public static int calculateOutput(int theta, double weights[], double x, double y, double z){
		double sum = x * weights[0] + y * weights[1] + z * weights[2] + weights[3];
		return (sum >= theta) ? 1 : 0;
	}
}