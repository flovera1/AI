/*
*Tree is the representation of the decision tree.
*
* it uses the class Node which holds the information of the nodes.
*
* 19 Feb 2015.	
* @Authored: Fernando Lovera
*/
import java.io.*;
import java.util.*;
public class Tree {
	Node root;
	private HashMap nodes;
	public Tree(Node root){
		this.root = root;
	}
	public HashMap getNodes(){
		return nodes;
	}
	public void addNode(Node node) {
        nodes.put(node);
        if (node.parent != null) {
            nodes.get(parent).addChild(node);
        }
        return node;
    }

	public buildTree(){}

}