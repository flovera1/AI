/**
* Program that reflects the datatype sorted list
* With this datatype is possible to have a list ordered 
* the order is basically the same order as Collections (Interface in Java Api)
*
*
* Thu 5 Mar
* @Caracas 
* @Fernando 
*/
import java.util.*;
private class SortedList{
	/** The list of elements */
	private ArrayList list = new ArrayList();		
	/**
	* Retrieve the first element from the list
	*  
	* @return The first element from the list
	*/
	public Object first() {
		return list.get(0);
	}	
	/**
	* Empty the list
	*/
	public void clear() {
		list.clear();
	}	
	/**
	* Add an element to the list - causes sorting
	* 
	* @param o The element to add
	*/
	public void add(Object o) {
		list.add(o);
		Collections.sort(list);
	}	
	/**
	* Remove an element from the list
	* 
	* @param o The element to remove
	*/
	public void remove(Object o) {
		list.remove(o);
	}
	/**
	* Get the number of elements in the list
	* 
	* @return The number of element in the list
 	*/
	public int size() {
		return list.size();
	}	
	/**
	* Check if an element is in the list
	* 
	* @param o The element to search for
	* @return True if the element is in the list
	*/
	public boolean contains(Object o) {
		return list.contains(o);
	}
}