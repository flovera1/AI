package proy1;
import robocode.*;
//import java.awt.Color;

// API help : http://robocode.sourceforge.net/docs/robocode/robocode/Robot.html

/**
 * SBLearner - a robot by (your name here)
 */
import java.io.*;
import java.util.Vector;
import java.util.Random;
import java.util.Iterator;
import robocode.AdvancedRobot;
import robocode.HitRobotEvent;
import robocode.ScannedRobotEvent;

import java.awt.*;


/**
 * SpinBot - a sample robot by Mathew Nelson, and maintained by Flemming N. Larsen
 * <p/>
 * Moves in a circle, firing hard when an enemy is detected
 */
public class SBLearner extends AdvancedRobot {

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
		if (disparado)
			return;

        double random = generator.nextDouble(); // Num entre 0 y 1
		double direccionDisparo = (random*2*lim) -lim;
		
		turnGunRight (direccionDisparo);
        fire (3);
			   disparado =true;
		turnGunRight (-1*direccionDisparo);
        
		info = new InformacionDisparo(velocity,bearing,robotDistance, random, getHeading(), getX(), getY());
		
	}

        public void onBulletHit(BulletHitEvent event){
					out.println("Llevo: " + numDisparosCorrectos);
			   disparado =false;
                // Insertar la informacion del disparo en la red Neural.
                v.add(info);
				//FileWriter file = null;
     			//PrintWriter pw = null;
                 
                numDisparosCorrectos++;

				BufferedWriter archivo ;
				try {
					archivo = new BufferedWriter(new FileWriter(filename,true));
					archivo.write(info.bearing + "," + info.distance + "," + info.heading + ","+  info.bearingDisparo + "\n");
					archivo.close();
				} 
				catch ( IOException e )
				{	
				}
		
                 
        }
        

        public void onBulletHitBullet(BulletHitBulletEvent event){ 
			disparado =false;
                // No se hace nada porque no golpeo un robot enemigo.
        }

        public void onBulletMissed(BulletMissedEvent event){
			disparado =false;
                // No se hace nada porque no golpeo un robot enemigo.
        }

	/**
	 * onDeath:  We died.  Decide whether to try a different corner next game.
	 */
	public void onDeath(DeathEvent e) {

		disparado =false;
	}

        public SBLearner(){
               v = new Vector<InformacionDisparo> ();
			   disparado =false;
        } 

		private Vector<InformacionDisparo> v;
        private InformacionDisparo info;
        private static int numDisparosCorrectos;
        private static final int numDisparosNecesarios = 3;
        private Random generator = new Random();
        private static final double lim = 45;
		private static final String filename = "pruebaSBSimplifiedLimitChanged.txt";
		private boolean disparado; 

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
