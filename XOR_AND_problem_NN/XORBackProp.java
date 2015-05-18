public class XORBackProp{
	private static final int MAX_EPOCHS = 500;
	//weights
	private static double w13, w23, w14, w24, w35, w45;
	private static double theta3, theta4, theta5;
	//neuron outputs
	private static double gamma3, gamma4, gamma5;
	//neuron error gradients
	private static double delta3, delta4, delta5;
	//weight corrections
	private static double dw13, dw14, dw23, dw24, dw35, dw45, dt3, dt4, dt5;
	//learning rate
	private static double alpha = 0.3;
	private static double error;
	private static double sumSqrError;
	private static int epochs   = 0;
	private static boolean loop = true;
	private static double sigmoid(double exponent){
		return (1.0 / (1 + Math.pow(Math.E, (-1) * exponent)));
	}
	private static void activateNeuron(int x1, int x2, int gd5){
		gamma3 = sigmoid(x1 * w13 + x2 * w23 - theta3);
		gamma4 = sigmoid(x1 * w14 + x2 * w24 - theta4);
		gamma5 = sigmoid(gamma3 * w35 + gamma4 * w45 - theta5);
		error  = gd5 - gamma5;
		weightTraining(x1, x2);
	}
	private static void weightTraining(int x1, int x2){
		delta5 = gamma5 * (1 - gamma5) * error;
		dw35   = alpha  * gamma3 * delta5;
		dw45   = alpha  * gamma4 *delta5;
		dt5    = alpha  * (-1) * delta5;
		delta3 = gamma3 * (1 - gamma3) * delta5 * w35;
		delta4 = gamma4 * (1 - gamma4) * delta5 * w45;
		dw13   = alpha * x1 * delta3;
    	dw23   = alpha * x2 * delta3;
    	dt3    = alpha * (-1) * delta3;
       	dw14   = alpha * x1 * delta4;
    	dw24   = alpha * x2 * delta4;
      	dt4    = alpha * (-1) * delta4;
        w13    = w13 + dw13;
        w14    = w14 + dw14;
       	w23    = w23 + dw23;
        w24    = w24 + dw24;
       	w35    = w35 + dw35;
       	w45    = w45 + dw45;
    	theta3 = theta3 + dt3;
    	theta4 = theta4 + dt4;
    	theta5 = theta5 + dt5;
	}

	public static void main(String[] args){
	    w13    = 0.5;
	    w14    = 0.9;
	    w23    = 0.4;
	    w24    = 1.0;
	    w35    = -1.2;
	    w45    = 1.1;
	    theta3 = 0.8;
	    theta4 = -0.1;
	    theta5 = 0.3;
	    System.out.println("XOR Neural Network");
	    while(loop){
	        activateNeuron(1,1,0);
	        sumSqrError = error * error;
	        activateNeuron(0,1,1);
	        sumSqrError += error * error;
	        activateNeuron(1,0,1);
	        sumSqrError += error * error;
	        activateNeuron(0,0,0);
	        sumSqrError += error * error;
	        epochs++;
	        if(epochs >= MAX_EPOCHS){
	            System.out.println("Learning will take more than " + MAX_EPOCHS + " epochs, so program has terminated.");
	            System.exit(0);
	        }
	        System.out.println(epochs + " " + sumSqrError);
	        if (sumSqrError < 0.001){
	            loop = false;
	        }
	    }
	}
}