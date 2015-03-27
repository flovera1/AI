/**
 * A path determined by some path finding algorithm. A series of steps from
 * the starting location to the target location. This includes a step for the
 * initial location.
 * 
 * @Fernando
 */
import java.util.ArrayList;
public class Path {
	private ArrayList steps = new ArrayList();
	//Getters
	public int getLength() {
		return steps.size();
	}
	public Step getStep(int index) {
		return (Step) steps.get(index);
	}
	public int getX(int index) {
		return getStep(index).x;
	}
	public int getY(int index) {
		return getStep(index).y;
	}
	/**
	* Add at the step
	* @param x The x coordinate  
	* @param y The y coordinate 
	*/
	public void appendStep(int x, int y) {
		steps.add(new Step(x,y));
	}
	public void prependStep(int x, int y) {
		steps.add(0, new Step(x, y));
	}
	/**
	 * Check if this path contains the given step
	 * 
	 * @param x The x coordinate of the step to check for
	 * @param y The y coordinate of the step to check for
	 * @return True if the path contains the given step
	 */
	public boolean contains(int x, int y) {
		return steps.contains(new Step(x,y));
	}
}
