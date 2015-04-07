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
import java.lang.Math;


//import java.awt.Color;

// API help : http://robocode.sourceforge.net/docs/robocode/robocode/Robot.html

/**
 * Learned - a robot by (your name here)
 */
public class Learned extends Robot
{
	int others; // Number of other robots in the game
	static int corner = 0; // Which corner we are currently using
	// static so that it keeps it between rounds.
	boolean stopWhenSeeRobot = false; // See goCorner()

	/**
	 * run:  Corners' main run function.
	 */
	public void run() {
		// Set colors
		setBodyColor(Color.red);
		setGunColor(Color.black);
		setRadarColor(Color.yellow);
		setBulletColor(Color.green);
		setScanColor(Color.green);

		// Save # of other bots
		others = getOthers();

		// Move to a corner
		goCorner();

		// Initialize gun turn speed to 3
		int gunIncrement = 3;

		// Spin gun back and forth
		while (true) {
			for (int i = 0; i < 30; i++) {
				turnGunLeft(gunIncrement);
			}
			gunIncrement *= -1;
		}
	}

	/**
	 * goCorner:  A very inefficient way to get to a corner.  Can you do better?
	 */
	public void goCorner() {
		// We don't want to stop when we're just turning...
		stopWhenSeeRobot = false;
		// turn to face the wall to the "right" of our desired corner.
		turnRight(normalRelativeAngleDegrees(corner - getHeading()));
		// Ok, now we don't want to crash into any robot in our way...
		stopWhenSeeRobot = true;
		// Move to that wall
		ahead(5000);
		// Turn to face the corner
		turnLeft(90);
		// Move to the corner
		ahead(5000);
		// Turn gun to starting point
		turnGunLeft(90);
	}

	/**
	 * onScannedRobot:  Stop and fire!
	 */
	public void onScannedRobot(ScannedRobotEvent e) {
		// Should we stop, or just fire?
		if (stopWhenSeeRobot) {
			// Stop everything!  You can safely call stop multiple times.
			stop();
			// Call our custom firing method
			smartFire(e.getVelocity(), 
					  e.getBearing(), 
					  e.getDistance());
			// Look for another robot.
			// NOTE:  If you call scan() inside onScannedRobot, and it sees a robot,
			// the game will interrupt the event handler and start it over
			scan();
			// We won't get here if we saw another robot.
			// Okay, we didn't see another robot... start moving or turning again.
			resume();
		} else {
			smartFire(e.getVelocity(), 
					  e.getBearing(), 
					  e.getDistance());
		}
	}

	/**
	 * smartFire:  Custom fire method that determines firepower based on distance.
	 *
	 * @param robotDistance the distance to the robot to fire at
	 */
	public void smartFire(double velocity, double bearing,double robotDistance) {
		
		double [] valoresEntrada = new double [3];
		
		valoresEntrada[0]=velocity;
		valoresEntrada[1] = bearing;
		valoresEntrada[2] = robotDistance;

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
		// Well, others should never be 0, but better safe than sorry.
		if (others == 0) {
			return;
		}
	
	}

        public Learned(){
               v = new Vector<InformacionDisparo> ();
        } 

		private Vector<InformacionDisparo> v;
        private InformacionDisparo info;
        private static int numDisparosCorrectos;
        private static final int numDisparosNecesarios = 100000;
        private static final double lim = 15;

		private static RedNeural redNeural = new RedNeural("redNeuralcorner21.txt");
		
        private class InformacionDisparo {
                public double velocity;
                public double bearing;
                public double distance;
                public double bearingDisparo;
                
                public InformacionDisparo (double v, double b, double d, double bd){
                	velocity = v;
                	bearing = b;
                	distance = d; 
                	bearingDisparo = bd;                	
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
