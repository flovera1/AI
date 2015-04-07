/**
* Class: Centroid
* @description: Ok, this class represents the centroid of the clusters
*               that's why it has two coordenates: X and Y
* @author: Fernando Lovera flovera1@gmail.com
*/    
public class Centroid{
        private double X = 0.0;
        private double Y = 0.0;
        //constructor
        public Centroid(double newX, double newY){
            this.X = newX;
            this.Y = newY;
        }
        /**
        * Setters and getters for the centroid
        */
        public void X(double newX){
            this.X = newX;
        }
        public double X(){
            return this.X;
        }
        public void Y(double newY){
            this.Y = newY;
            return;
        }
        public double Y(){
            return this.Y;
        }
    }