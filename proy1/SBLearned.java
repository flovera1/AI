package proy1; 
import robocode.*;
import java.io.*;
import java.util.Random;
import java.util.Iterator;
import robocode.DeathEvent;
import robocode.Robot;
import robocode.*;
import static robocode.util.Utils.normalRelativeAngleDegrees;
import java.awt.*;
import java.util.Vector;

import java.util.Iterator;
import java.util.Random;
import java.util.StringTokenizer;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.lang.Math;;


/**
 * SpinBot - a sample robot by Mathew Nelson, and maintained by Flemming N. Larsen
 * <p/>
 * Moves in a circle, firing hard when an enemy is detected
 */
public class SBLearned extends AdvancedRobot {

	/**
	 * SpinBot's run method - Circle
	 */
	public void run() {
		// Set colors
		setBodyColor(Color.blue);
		setGunColor(Color.blue);
		setRadarColor(Color.black);
		setScanColor(Color.yellow);

		// Loop forever
		while (true) {
			// Tell the game that when we take move,
			// we'll also want to turn right... a lot.
			setTurnRight(10000);
			// Limit our speed to 5
			setMaxVelocity(5);
			// Start moving (and turning)
			ahead(10000);
			// Repeat.
		}
	}

	/**
	 * onHitRobot:  If it's our fault, we'll stop turning and moving,
	 * so we need to turn again to keep spinning.
	 */
	public void onHitRobot(HitRobotEvent e) {

		if (e.isMyFault()) {
			turnRight(10);
		}
	}


	/**
	 * onScannedRobot:  Stop and fire!
	 */
	public void onScannedRobot(ScannedRobotEvent e) {

			smartFire(e.getVelocity(), 
					  e.getBearing(), 
					  e.getDistance());

	}


	/**
	 * smartFire:  Custom fire method that determines firepower based on distance.
	 *
	 * @param robotDistance the distance to the robot to fire at
	 */
	public void smartFire(double velocity, double bearing,double robotDistance) {
		
		double [] valoresEntrada = new double [3];
		
		valoresEntrada[0] = bearing;
		valoresEntrada[1] = robotDistance;
		valoresEntrada[2] = getHeading();
		
		double random = redNeural.calcularSalida(valoresEntrada)[0];
		
		out.println("Disparando");
		
		double direccionDisparo = (random*2*lim) -lim;
		
		turnGunRight (direccionDisparo);
        fire (3);
			   
		turnGunRight (-1*direccionDisparo);
		
	}

        public void onBulletHit(BulletHitEvent event){
					out.println("TOMAAAAAA");
        }
        

        public void onBulletHitBullet(BulletHitBulletEvent event){ 
                // No se hace nada porque no golpeo un robot enemigo.
        }

        public void onBulletMissed(BulletMissedEvent event){
                // No se hace nada porque no golpeo un robot enemigo.
        }

	/**
	 * onDeath:  We died.  Decide whether to try a different corner next game.
	 */
	public void onDeath(DeathEvent e) {

	
	}

        public SBLearned(){
               v = new Vector<InformacionDisparo> ();
        } 

		private Vector<InformacionDisparo> v;
        private InformacionDisparo info;
        private static int numDisparosCorrectos;
        private static final int numDisparosNecesarios = 100000;
        private static final double lim = 45;

		private static RedNeural redNeural = new RedNeural("redNeuralSimplifiedLimitChanged.txt");
		
        private class InformacionDisparo {
                public double velocity;
                public double bearing;
                public double distance;
                public double bearingDisparo;
                public double heading;
				public double posX;
				public double posY; 
				
                public InformacionDisparo (double v, double b, double d, double bd, double h, double x, double y){
                	velocity = v;
                	bearing = b;
                	distance = d; 
                	bearingDisparo = bd;                	
					heading = h;
					posX = x;
					posY = y;
                }
           
                
        }

        
        
}


class RedNeural {

	int numNodosEntrada;
	int numNodosIntermedios;
	int numNodosSalida;
	
	double [][] weight_input_layer;
	double [][] weight_output_layer;
	double tasaAprendizaje;
	
	public RedNeural(int numNodosEntrada, 
				     int numNodosIntermedios, 
				     int numNodosSalida, 
				     double tasaAprendizaje) {
		
		super();
		
		this.numNodosEntrada = numNodosEntrada;
		this.numNodosIntermedios = numNodosIntermedios;
		this.numNodosSalida = numNodosSalida;
		this.tasaAprendizaje = tasaAprendizaje;
		
		weight_input_layer = new double[numNodosEntrada+1][numNodosIntermedios];
		
		Random generator = new Random();
		
		for (int i =0; i<numNodosEntrada+1;i++){
			for (int j = 0; j < numNodosIntermedios; j++){
				weight_input_layer[i][j] = generator.nextDouble();
			}
		}
		
		weight_output_layer = new double [numNodosIntermedios+1][numNodosSalida];
		for (int i =0; i<numNodosIntermedios+1;i++){
			for (int j = 0; j < numNodosSalida; j++){
				weight_output_layer[i][j] = generator.nextDouble();
			}
		}
	}
	
	void  feed_forward(double [] valor_entrada, double [] valores_intermedios, double [] valor_salida){
		double acum;
		
		//Calculo de los valores intermedios.
		for(int i = 0; i < numNodosIntermedios; i++){
			//Calculo de net
			acum =0;
		
			for (int j = 0 ; j < numNodosEntrada; j++){
				acum+=weight_input_layer[j][i]*valor_entrada[j];
			}
			
			// Aplicacion de la funcion sigmoidal. 
			valores_intermedios[i] = sigmoid(acum+weight_input_layer[numNodosEntrada][i]);
		}
		
			//Calculo de los valores intermedios.
		for(int i = 0; i < numNodosSalida; i++){
			//Calculo de net
			acum =0;
		
			for (int j = 0 ; j < numNodosIntermedios; j++){
				acum+=weight_output_layer[j][i]*valores_intermedios[j];
			}
			
			// Aplicacion de la funcion sigmoidal. 
			valor_salida[i] = sigmoid(acum+weight_output_layer[numNodosIntermedios][i]);
		}
	}
	
	double sigmoid(double y){
		return 1/(1+Math.exp(-y));
	}
	
	double []  calcularSalida(double [] valor_entrada){
		
		double [] valor_salida = new double [numNodosSalida] ;
		
		double [] valores_intermedios = new double [numNodosIntermedios];
		
		feed_forward(valor_entrada, valores_intermedios, valor_salida);
		
		return valor_salida ;
		
	}    
	
	double error_output(double output, double target){
		return output*(1-output)*(target-output);
	}
	
	void resolve_case(double [] valor_entrada, double [] target){
		
		double [] valores_intermedios = new double [numNodosIntermedios];
		double [] valor_salida =  new double [numNodosSalida];
		
		double [] error_intermedios =  new double [numNodosIntermedios];
		double [] error_salida =  new double [numNodosSalida];

		// Feed forward.
		feed_forward(valor_entrada, valores_intermedios,valor_salida);
		
		
		//Calculo del error de la capa de salida.
		for (int i = 0 ; i< numNodosSalida; i++){
			error_salida[i] = error_output(valor_salida[i], target[i]);
		}
		
		
		double acum;
		
		//Calculo de error de cada neurona intermedia
		for(int i = 0; i < numNodosIntermedios; i++){
			acum = 0; 
			for(int j=0; j < numNodosSalida; j++){
				acum += weight_output_layer[i][j]*error_salida[j];
			}
			error_intermedios[i] =  valores_intermedios[i]*(1-valores_intermedios[i])*acum;
		}
		
		
		//Actualizar pesos de la capa intermedia a la de salida
		for(int j=0; j < numNodosSalida; j++){
		
			for(int i = 0 ; i < numNodosIntermedios; i++){
				weight_output_layer[i][j] += tasaAprendizaje*error_salida[j]*valores_intermedios[i];
			}
			//weight_output_layer[numNodosIntermedios][j] += tasaAprendizaje*error_salida[j];
		}
		
		
		
		//Actualizar pesos de la capa de entrada a la capa de salida. 
		for(int i = 0; i<numNodosIntermedios; i++){
			for (int j = 0; j<numNodosEntrada; j++){
				weight_input_layer[j][i] += tasaAprendizaje*
											error_intermedios[i]*
											valor_entrada[j];	
			}
			//weight_input_layer[numNodosEntrada][i]+=tasaAprendizaje*
			//								error_intermedios[i];
		}
		
	}
	
	//entrenamiento
	void resolve_set_cases(double [][] entrada, double [][] target,int size){
		
		for(int i = 0; i<size; i++){		
			resolve_case(entrada[i], target[i]);//el target se inicializa en el main
		}
	}
	
	public void writeToFile (String fileName){
		try{
			  // Create file 
			  FileWriter fstream = new FileWriter(fileName);
			  BufferedWriter out = new BufferedWriter(fstream);
			  
			  out.write(Integer.toString(numNodosEntrada) + " ");
			  out.write(Integer.toString(numNodosIntermedios) + " ");
			  out.write(Integer.toString(numNodosSalida) + " ");
			  out.write(Double.toString(tasaAprendizaje) + "\n");
			  
			  for (int i =0; i<numNodosEntrada+1;i++){
				for (int j = 0; j < numNodosIntermedios; j++){
					  out.write(Double.toString(weight_input_layer[i][j]) + " ");
				}
				out.write ("\n");
			  }

			  for (int i =0; i<numNodosIntermedios+1;i++){
				for (int j = 0; j < numNodosSalida; j++){
					out.write(Double.toString(weight_output_layer[i][j]) + " ");
				}
				out.write ("\n");
			  }
	
			  out.write ("\n");			  
			  
			  //Close the output stream
			  out.close();
			  }
		catch (Exception e){//Catch exception if any
			  System.err.println("Error: " + e.getMessage());
			  }
	}

	public RedNeural (String fileName){
		
		try {
		    BufferedReader in = new BufferedReader(new FileReader(fileName));
		    String str;
		    
		    str = in.readLine();
		    StringTokenizer st = new StringTokenizer(str, " ");
		    
		    this.numNodosEntrada =  Integer.valueOf(st.nextToken()).intValue();
			this.numNodosIntermedios =  Integer.valueOf(st.nextToken()).intValue();
			this.numNodosSalida =  Integer.valueOf(st.nextToken()).intValue();
			this.tasaAprendizaje =  Double.valueOf(st.nextToken()).doubleValue();
 
			weight_input_layer = new double[numNodosEntrada+1][numNodosIntermedios];
			weight_output_layer = new double [numNodosIntermedios+1][numNodosSalida];
			
			for (int i =0; i<numNodosEntrada+1;i++){
				str = in.readLine();
				st = new StringTokenizer(str, " ");
				for (int j = 0; j < numNodosIntermedios; j++){
					weight_input_layer[i][j] = Double.valueOf(st.nextToken()).doubleValue();
				}
			}
				  
			for (int i =0; i<numNodosIntermedios+1;i++){
				str = in.readLine();
				st = new StringTokenizer(str, " ");
				for (int j = 0; j < numNodosSalida; j++){
					weight_output_layer[i][j] =  Double.valueOf(st.nextToken()).doubleValue();
				}

			}
		    
		    in.close();
		} catch (IOException e) {
			System.out.println("Error leyendo!");
			  System.err.println("Caught IOException: "
                        + e.getMessage()); 
		}
					
	}
}																																																																			
								