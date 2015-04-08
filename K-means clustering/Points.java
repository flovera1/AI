import java.awt.*;
import java.util.Random;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;
import java.util.*;
class Surface extends JPanel{
    ArrayList<Data> source = new ArrayList<Data>();
    int color              = 0;
    public Surface(ArrayList<Data> arr, int c){
        for(int i = 0; i < arr.size(); i++){
            source.add(arr.get(i));
        }
        color = c;
    }
    private void doDrawing(Graphics g) {
        Graphics2D g2d = (Graphics2D) g;
        if(this.color == 0){
            g2d.setColor(Color.black);
            Dimension size = getSize();
            Insets insets  = getInsets();
            for (int i = 0; i < 500; i++) {
                int x      = (int) this.source.get(i).X();
                int y      = (int) this.source.get(i).Y();
                g2d.drawLine(x, y, x, y);
            }
        }else if(this.color == 1){
            g2d.setColor(Color.red);
            Dimension size = getSize();
            Insets insets  = getInsets();
            for (int i = 500; i < 1000; i++) {
                int x      = (int) this.source.get(i).X();
                int y      = (int) this.source.get(i).Y();
                g2d.drawLine(x, y, x, y);
            }
        }else if(this.color == 2){
            g2d.setColor(Color.blue);
            Dimension size = getSize();
            Insets insets  = getInsets();
            for (int i = 1000; i < 1500; i++) {
                int x      = (int) this.source.get(i).X();
                int y      = (int) this.source.get(i).Y();
                g2d.drawLine(x, y, x, y);
            }
        }else if(this.color == 3){
            g2d.setColor(Color.green);
            Dimension size = getSize();
            Insets insets  = getInsets();
            for (int i = 1500; i < 2000; i++) {
                int x      = (int) this.source.get(i).X();
                int y      = (int) this.source.get(i).Y();
                g2d.drawLine(x, y, x, y);
            }
        }

    }
    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        doDrawing(g);
    }
}
public class Points extends JFrame {
    public Points(ArrayList<Data> d, int i){
        setTitle("Points in the clustering");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        Surface sur = new Surface(d, i);
        add(sur);
        setSize(500, 500);
        setLocationRelativeTo(null);
    }

   /* public static void main(String[] args) {
        ArrayList<Data> clusters      = new ArrayList<Data>();
        for(int i = 0; i < 2000; i++){
                Random randX         = new Random();
                int  nX              = randX.nextInt(50) + 1;
                Random randY         = new Random();
                int  nY              = randX.nextInt(50) + 1;
                Data d               = new Data(nX, nY);
                clusters.add(d);
        }
        Points ps                     = new Points(clusters);
        ps.setVisible(true);
                }
        });*/
    }