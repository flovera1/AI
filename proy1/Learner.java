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
//import java.awt.Color;

// API help : http://robocode.sourceforge.net/docs/robocode/robocode/Robot.html

/**
 * Learner - a robot by (your name here)
 */
public class Learner extends Robot
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
		if (disparado)
			return;

        double random = generator.nextDouble(); // Num entre 0 y 1
		double direccionDisparo = (random*2*lim) -lim;
		
		turnGunRight (direccionDisparo);
        fire (3);
			   disparado =true;
		turnGunRight (-1*direccionDisparo);
        
		info = new InformacionDisparo(velocity,bearing,robotDistance, random);
		
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
					archivo.write(info.velocity + "," + info.bearing + "," + info.distance + "," +  info.bearingDisparo + "\n");
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
		// Well, others should never be 0, but better safe than sorry.
		if (others == 0) {
			return;
		}
	
		disparado =false;
	}

        public Learner(){
               v = new Vector<InformacionDisparo> ();
			   disparado =false;
        } 

		private Vector<InformacionDisparo> v;
        private InformacionDisparo info;
        private static int numDisparosCorrectos;
        private static final int numDisparosNecesarios = 3;
        private Random generator = new Random();
        private static final double lim = 15;
		private static final String filename = "pruebatrolol.txt";
		private boolean disparado; 

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