/**
 * A path is a series of steps from
 * the starting location to the target location. This includes a step for the
 * initial location.
 * 
 * Thue 5 Mar
 * @Caracas
 * @Fernando 
 *
 */
import java.util.*;
public class Path{
	private ArrayList steps = new ArrayList();
	// getters
	/**
	 * @return The number of steps in this path
	 */
	public int getLength() {
		return steps.size();
	}
	/**
	 * @param index The index of the step to retrieve
	 * @return The step information, the position on the map.
	 */
	public Step getStep(int index) {
		return (Step) steps.get(index);
	}
	/** 
	 * @param index The index of the step whose x coordinate should be retrieved
	 * @return The x coordinate at the step
	 */
	public int getX(int index) {
		return getStep(index).x;
	}
	/** 
	 * @param index The index of the step whose y coordinate should be retrieved
	 * @return The y coordinate at the step
	 */
	public int getY(int index) {
		return getStep(index).y;
	}
	/** 
	 * Add a step at the end.
	 * @param x The x coordinate of the new step.
	 * @param y The y coordinate of the new step.
	 */
	public void appendStep(int x, int y) {
		steps.add(new Step(x,y));
	}
	/**
	 * Prepend a step to the path.  
	 * @param x The x coordinate of the new step.
	 * @param y The y coordinate of the new step.
	 */
	public void prependStep(int x, int y) {
		steps.add(0, new Step(x, y));
	}
	/**
	 * @param x The x coordinate of the step to check for
	 * @param y The y coordinate of the step to check for
	 * @return True if the path contains the given step
	 */
	public boolean contains(int x, int y) {
		return steps.contains(new Step(x,y));
	}
}
