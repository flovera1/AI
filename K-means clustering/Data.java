/**
* Class: Data.java
* @description: Simple class that has two parameters(in the problem abstraction it could represent
*               just two classes or two "prospects" for clusters). The number of clusters is also
*               important.
* @author: Fernando Lovera flovera1@gmail.com
* @date: Tue 7 Apr
*/    
public class Data{
        private double mX    = 0;
        private double mY    = 0;
        private int mCluster = 0;
        //constructor
        public Data(double x, double y){            
            this.X(x);
            this.Y(y);
        }
        /*
        * setters and getters.
        * set the value of mX and get the value mX.
        * set the value of mY and get the value mY.
        * set the value of the number of getters and setters.
        */
        public void X(double x){
            this.mX = x;
        }
        public double X(){
            return this.mX;
        }
        public void Y(double y){
            this.mY = y;
        }
        public double Y(){
            return this.mY;
        }        
        public void cluster(int clusterNumber){
            this.mCluster = clusterNumber;
        }
        public int cluster(){
            return this.mCluster;
        }
    }