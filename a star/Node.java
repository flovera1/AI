/**
* Node class, every position (alson known as location)
* is gonna be a Node. This class contains that data structure
* 
*
*
* Thu 5 Mar
* @Caracas 
* Fernando Lovera
*/
import java.util.*;
private class Node implements Comparable {
	/** The x coordinate of the node */
	private int x;
	/** The y coordinate of the node */
	private int y;
	/** The path cost for this node */
	private float cost;
	/** The parent of this node, how we reached it in the search */
	private Node parent;
	/** The heuristic cost of this node */
	private float heuristic;
	/** The search depth of this node */
	private int depth;		
	/**
	* Create a new node
	* 
	* @param x The x coordinate of the node
	* @param y The y coordinate of the node
	*/
	public Node(int x, int y) {
		this.x = x;
		this.y = y;
	}	
	/**
	* Set the parent of this node
	* 
	* @param parent The parent node which lead us to this node
	* @return The depth we have no reached in searching
	*/
	public int setParent(Node parent) {
		depth       = parent.depth + 1;
		this.parent = parent;	
		return depth;
	}
	/**
	* @see Comparable#compareTo(Object)
	*/
	public int compareTo(Object other) {
		Node o       = (Node) other;
		float f      = heuristic + cost;
		float of     = o.heuristic + o.cost;
		if (f < of) {
			return -1;
		} 
		else if (f > of) {
			return 1;
		} else {
			return 0;
		}
	}
}