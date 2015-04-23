import java.util.*;

public class ID3{
	ArrayList<Vector> collection   = new ArrayList<Vector>();//collection of instances
	int proportionPositiveExamples = 9;
	int proportionNegativeExamples = 5;
	Record r;
	public ID3(){
		//fill the collection
		Vector<String> v0 = new Vector<String>();
		v0.add("Sunny");
		v0.add("Hot");
		v0.add("High");
		v0.add("Weak");
		v0.add("No");
		Vector<String> v1 = new Vector<String>();
		v1.add("Sunny");
		v1.add("Hot");
		v1.add("High");
		v1.add("Strong");
		v1.add("No");
		Vector<String> v2 = new Vector<String>();
		v2.add("Overcast");
		v2.add("Hot");
		v2.add("High");
		v2.add("Weak");
		v2.add("Yes");
		Vector<String> v3 = new Vector<String>();
		v3.add("Rain");
		v3.add("Mild");
		v3.add("High");
		v3.add("Weak");
		v3.add("Yes");
		Vector<String> v4 = new Vector<String>();
		v4.add("Rain");
		v4.add("Cool");
		v4.add("Normal");
		v4.add("Weak");
		v4.add("Yes");
		Vector<String> v5 = new Vector<String>();
		v5.add("Rain");
		v5.add("Cool");
		v5.add("Normal");
		v5.add("Strong");
		v5.add("No");
		Vector<String> v6 = new Vector<String>();
		v6.add("Overcast");
		v6.add("Cool");
		v6.add("Normal");
		v6.add("Strong");
		v6.add("Yes");
		Vector<String> v7 = new Vector<String>();
		v7.add("Sunny");
		v7.add("Mild");
		v7.add("High");
		v7.add("Weak");
		v7.add("No");
		Vector<String> v8 = new Vector<String>();
		v8.add("Sunny");
		v8.add("Cool");
		v8.add("Normal");
		v8.add("Weak");
		v8.add("Yes");
		Vector<String> v9 = new Vector<String>();
		v9.add("Rain");
		v9.add("Mild");
		v9.add("Normal");
		v9.add("Weak");
		v9.add("Yes");
		Vector<String> v10 = new Vector<String>();
		v10.add("Sunny");
		v10.add("Mild");
		v10.add("Normal");
		v10.add("Strong");
		v0.add("Yes");
		Vector<String> v11 = new Vector<String>();
		v11.add("Overcast");
		v11.add("Mild");
		v11.add("High");
		v11.add("Strong");
		v11.add("Yes");
		Vector<String> v12 = new Vector<String>();
		v12.add("Overcast");
		v12.add("Hot");
		v12.add("Normal");
		v12.add("Weak");
		v12.add("Yes");
		Vector<String> v13 = new Vector<String>();
		v13.add("Rain");
		v13.add("Mild");
		v13.add("High");
		v13.add("Strong");
		v13.add("No");
		collection.add(v0);
		collection.add(v1);
		collection.add(v2);
		collection.add(v3);
		collection.add(v4);
		collection.add(v5);
		collection.add(v6);
		collection.add(v7);
		collection.add(v8);
		collection.add(v9);
		collection.add(v10);
		collection.add(v11);
		collection.add(v12);
		collection.add(v13);
	}

	public static void main(String[] args){

	}
}