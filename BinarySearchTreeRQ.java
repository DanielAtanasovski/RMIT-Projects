import java.io.PrintWriter;
import java.lang.String;

/**
 * Implementation of the Runqueue interface using a Binary Search Tree.
 *
 * Your task is to complete the implementation of this class.
 * You may add methods and attributes, but ensure your modified class compiles and runs.
 *
 * @author Sajal Halder, Minyi Li, Jeffrey Chan
 */
public class BinarySearchTreeRQ implements Runqueue {

	
	/*
	 * BASIC IDEA:
	 * - As this is a Binary tree all elements need to be balanced
	 * as such every removal and addition of a node the tree needs to 
	 * re-balance itself. My thinking is that we make a balance() method to handle it
	 * 
	 * - balance()
	 * this will essentially make a copy of the whole tree and then one by one, 
	 * feed each element into the original tree to then re-balance. However this isn't
	 * that efficient as it will cause the whole tree to be 're made' every deletion or insertions
	 * 
	 * A better idea would be to balance only when needed. But I am unsure of how to do this...
	 * 
	 * 
	 *
	 * 				-- Example structure of Binary Search Tree using an array. --
	 * -+---------------+---------------------------------------------------+------------------------------+-
	 * 	| Depth/level:	|		Example Tree:		NOTE: ? = NULL value	| Index value: (base of 2)	   |
	 * -+---------------+---------------------------------------------------+------------------------------+-
	 * 	|	0			|			? - D									|	2							|
	 * 	|				|			    /\									|								|	
	 * 	|	1			|				B F									|	4							|
	 *	|				|			   /\ /\								|								|
	 * 	|	2			|			  A C D H    <-- Notice a duplicate D	|	8							|
	 * 	|				|			 /\ |\|\ |\								|								|
	 * 	|	3			|			? ? ??? ?G I							|	16							|
	 * -+---------------+---------------------------------------------------+-------------------------------+
	 * 
	 * 								--	Tree represented in array.	--
	 * 		-+----------+---+---+---+---+---+---+---+---+---+---+----+----+----+----+----+----+----+--+-+-
	 * 		 |Index:	| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 | 15 | 16 | 17 |
	 *  	+-----------+---+---+---+---+---+---+---+---+---+---+----+----+----+----+----+----+----+----+
	 * 		 |Value:	| ? | D | B | F | A | C | D | H | ? | ? | ?  | ?  | ?  | ?  | ?  | ?  | G  | I  |
	 * 		-+----------+---+---+---+---+---+---+---+---+---+---+----+----+----+----+----+----+----+----+-
	 *						   
	 * 						  ^
	 *						  |-- The root of the whole tree.
	 */
	
	
	
	private Proc[] arrayOfNodes;

    /**
     * Constructs empty queue
     */
	private static final int TREE_ROOT_INDEX = 1; 
	private static final int BASE_TREE_SIZE = 2;
	
	//for getting left and right of parent node/Proc
	private static final int LEFT = 0;
	private static final int RIGHT = 1;

    public BinarySearchTreeRQ() {
        arrayOfNodes = new Proc[BASE_TREE_SIZE];

    }  // end of BinarySearchTreeRQ()


    @Override
    public void enqueue(String procLabel, int vt) {
    	/*	NOTE: 
    	 * 	- 	As seen in the Assignment 1 discussion, it doesn't matter if it is balanced....
    	 *		I will try my best to have it balanced as it will speed up searching.
    	 * 	-	The VT values are not unique and there for there is no way of making 
    	 * 		a perfectly balanced tree with duplicates of values, thus i will do the following:
    	 * 		-	If the vt of the Proc is < the parent it will go on the LEFT of the parent.
    	 * 		-	If the vt of the Proc is > OR = to the parent it will go on the RIGHT of the parent.
    	 * 
    	 * 	- (See tree diagram above about duplicates)
    	 */
    	
        Proc nodeToAdd = new Proc(procLabel, vt);
        Proc currParent = null; // the current parent we are looking at.
        
        //see if the tree doesn't even have a root set yet
        if(arrayOfNodes.length == BASE_TREE_SIZE && arrayOfNodes[TREE_ROOT_INDEX] != null) {
        	arrayOfNodes[TREE_ROOT_INDEX] = nodeToAdd;
        }else {
        	
        	currParent = arrayOfNodes[TREE_ROOT_INDEX]; //set to the base root of tree.
        	for(int i = TREE_ROOT_INDEX; i < arrayOfNodes.length; i++) { //worse case in n^2, however should be closer to n log(n)
        		Proc[] child = findChildren(arrayOfNodes[i]);
        		if(nodeToAdd.getVt() > child[LEFT].getVt()) {
        			
        		}

        	}
        	
        	
        }
        
    } // end of enqueue()


    @Override
    public String dequeue() {
        // Implement me

        return ""; // placeholder, modify this
    } // end of dequeue()


    @Override
    public boolean findProcess(String procLabel) {
        // Implement me

        return false; // placeholder, modify this
    } // end of findProcess()


    @Override
    public boolean removeProcess(String procLabel) {
        // Implement me

        return false; // placeholder, modify this
    } // end of removeProcess()


    @Override
    public int precedingProcessTime(String procLabel) {
        // Implement me

        return -1; // placeholder, modify this
    } // end of precedingProcessTime()


    @Override
    public int succeedingProcessTime(String procLabel) {
        // Implement me

        return -1; // placeholder, modify this
    } // end of precedingProcessTime()


    @Override
    public void printAllProcesses(PrintWriter os) {
        // Implement me

    } // end of printAllProcess()
    
    
    /////// Custom methods ///////

    private int getIndexFor(Proc procToFind) {
    	//essentialy doing the whole divide and conquer approach 
    	for (int i = TREE_ROOT_INDEX; i < arrayOfNodes.length; i++) {
    		if (arrayOfNodes[i] != null) {
    			if(procToFind.getVt() < arrayOfNodes[i].getVt()) {
    				i *= 2; // will to to the left child of the parent. 
    			}else if(procToFind.getVt() >= arrayOfNodes[i].getVt()){
    				//need to ensure that it isnt the node we actualy want.
    				if(arrayOfNodes[i].equals(procToFind)) {
        				return i;
        			}
    				i = (i * 2) + 1; // will get the right child of the parent
    			}
    			if(arrayOfNodes[i].equals(procToFind)) {
    				return i;
    			}
    		}
    	}
		return -1;
	}
    
    public Proc[] findChildren(Proc parent) {
    	
		// left node will always be index parent * 2
		Proc leftChild = arrayOfNodes[getIndexFor(parent) * 2];
		// right node will always be index parent * 2 + 1
		Proc rightChild = arrayOfNodes[getIndexFor(parent) * 2 + 1];
		Proc[] retProcArray = new Proc[2];
		retProcArray[0] = leftChild;
		retProcArray[1] = rightChild;
		return retProcArray;
	} // end of findParent
    
    private int getNumberOfLevels() {
		return (int) (Math.log(arrayOfNodes.length) / Math.log(2));
    }
   
	
    
} // end of class BinarySearchTreeRQ
