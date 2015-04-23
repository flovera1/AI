/**
* @description: a property consists of two strings
*    			defining the name and value respectively.
*				This class needs to be abstract in order		
*				to check on property values.
*  	  	 		The abstract method to test for legal property
* 				values is called "isLegalValue". 
*				Any property type must define its own 
*  	 			subclass defining the abstract method!.
*/
public abstract class AbstractProperty{
	private String name  = null;//notice it's private
	private String value = null;//notice it's private
	public AbstractProperty(String name, String value) throws IllegalArgumentException{
		if(isLegalValey(value) == false) {
			throw new IllegalArgumentException(value + "is an Illegal value for Property "+getName());
			this.value = value;
		} 
	}
	public String getValue(){
		return value;
	}
	public abstract boolean isLegalValue(String value);
	public String getValue(){
		return value;
	}
	//Enforcing Immutable object pattern
	public final void setValue(String v) throws UnsupportedOperationException{
		throw new UnsupportedOperationException();
	}
	//Enforcing Immutable object pattern
	public final void setName(String n) throws UnsupportedOperationException{
		throw new UnsupportedOperationException();
	}
}