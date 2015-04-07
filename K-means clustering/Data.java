/**
*
*/    
public class Data{
        private double mX = 0;
        private double mY = 0;
        private int mCluster = 0;
        public Data(){
            return;
        }
        public Data(double x, double y){
            this.X(x);
            this.Y(y);
            return;
        }
        public void X(double x){
            this.mX = x;
            return;
        }
        public double X(){
            return this.mX;
        }
        public void Y(double y){
            this.mY = y;
            return;
        }
        public double Y(){
            return this.mY;
        }
        public void cluster(int clusterNumber){
            this.mCluster = clusterNumber;
            return;
        }
        public int cluster(){
            return this.mCluster;
        }
    }