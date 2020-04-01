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
	private int priorityQueueNumber = 0;

    /**
     * Constructs empty queue
     */
	private static final int TREE_ROOT_INDEX = 1; 
	private static final int BASE_TREE_SIZE = 2;
	
	//for getting left and right of parent node/Proc
	private static final int LEFT = 0;
	private static final int RIGHT = 1;

	//for calculating the children from the parent index. (MULTIPLIER) 
	private static final int LEFT_CHILD_MULTIPLIER = 2;
	private static final int LEFT_TO_RIGHT_MULTIPLIER = 1;
	
	//return value
	private static final int FAIL_VALUE = -1;
	
	private static final int BASE_NUMBER = 2;


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
    	
        Proc procToAdd = new Proc(procLabel, vt, priorityQueueNumber);
        priorityQueueNumber++;

        //see if the tree doesn't even have a root set yet
        if(arrayOfNodes.length == BASE_TREE_SIZE && arrayOfNodes[TREE_ROOT_INDEX] == null) {
        	arrayOfNodes[TREE_ROOT_INDEX] = procToAdd;
        }else {
        	int retIndex = -1;
//        	if (priorityQueueNumber >= arrayOfNodes.length - Math.pow(2, getNumberOfLevels() -1)) {
//    			// increase array length by 2^(current level + 1)
//    			addToArray((int) Math.pow(2, getNumberOfLevels()));
//        	}
        	int i = TREE_ROOT_INDEX;
        	while(i < arrayOfNodes.length) { //worse case in n^2, however should be closer to n log(n)

        		//Proc[] child = findChildren(i);
//        		if(child[2] != null) {
//        			Proc parent = arrayOfNodes[(int) Math.floor(i / 2)];
//        			System.out.println("parent vt: " + parent.getVt());
//        			if(procToAdd.getVt() < parent.getVt() && arrayOfNodes[i] == null) {
//        				System.out.println("patching left");
//        				arrayOfNodes[i*LEFT_CHILD_MULTIPLIER] = procToAdd;
//        			}else if(procToAdd.getVt() >= parent.getVt() && arrayOfNodes[i] == null) {
//        				System.out.println("patching right");
//
//        				arrayOfNodes[i*LEFT_CHILD_MULTIPLIER+1] = procToAdd;
//        			}
//        			break;
//        		}
        		System.out.println(i + " ARR LENGTH: " + arrayOfNodes.length);
        		int parentProcIndex = i;
        		int leftChild = i* LEFT_CHILD_MULTIPLIER;
        		int rightChild = (i * LEFT_CHILD_MULTIPLIER) + LEFT_TO_RIGHT_MULTIPLIER;
        		if(parentProcIndex != TREE_ROOT_INDEX) {
        			parentProcIndex = (int) (i / 2);
        		}
        		
        		boolean isValidLocation = true;
        		System.out.println("right: " + rightChild + " left: " + leftChild);
        		if(leftChild > arrayOfNodes.length || rightChild > arrayOfNodes.length) {
        			//isValidLocation = false;
        			addToArray((int) Math.pow(2, getNumberOfLevels()));
        		}
        		
        		if(isValidLocation && i <= arrayOfNodes.length) {
	        			if(procToAdd.getVt() < arrayOfNodes[i].getVt()) {
	        				i = leftChild;
	        			}else if(procToAdd.getVt() >= arrayOfNodes[i].getVt()) {
	        				i = rightChild;
	        			}
	        			if(arrayOfNodes[i] == null) {
	        				System.out.println(i + "is null");
	        			}else {
	        				System.out.println(arrayOfNodes[i].print());
	        			}
	        			if(arrayOfNodes[i] == null) {
	        				arrayOfNodes[i] = procToAdd;
	        				break;
	        			}
        		}
        		
        		
        		
//        		System.out.println("parent index: " + parentProcIndex);
//        		System.out.println(arrayOfNodes[parentProcIndex].getVt() + "---");
//        		if(child[LEFT] != null){
//	        		if(procToAdd.getVt() < child[LEFT].getVt()) {
//	        			System.out.println("1, going left, index: " + i + "ret " + retIndex);
//	        			i *= LEFT_CHILD_MULTIPLIER;
//	        		}
//	        	}else if(i < arrayOfNodes.length) { 
//	        		
//	        		if(procToAdd.getVt() < arrayOfNodes[parentProcIndex].getVt()){
//		        		System.out.println(" LEFT adding to index: " + i * LEFT_CHILD_MULTIPLIER);
//		        		arrayOfNodes[i * LEFT_CHILD_MULTIPLIER] = procToAdd;
//		        		break;
//	        		}
//	        	}
//        		if (child[RIGHT] != null) {
//	        		if(procToAdd.getVt() >= child[RIGHT].getVt()) {
//	        			System.out.println("1, going right, index: " + i + "ret " + retIndex);
//
//	        			i = (i * LEFT_CHILD_MULTIPLIER) + LEFT_TO_RIGHT_MULTIPLIER;
//	        		}
//	        	}else if(i < arrayOfNodes.length){
//	        		if(procToAdd.getVt() < arrayOfNodes[parentProcIndex].getVt()) {
//		        		System.out.println("RIGHT adding to index: " + (i * LEFT_CHILD_MULTIPLIER) + LEFT_TO_RIGHT_MULTIPLIER);
//		        		arrayOfNodes[(i * LEFT_CHILD_MULTIPLIER) + LEFT_TO_RIGHT_MULTIPLIER] = procToAdd;
//		        		break;
//	        		}
//	        	}
//        		if(child[2] != null){
//	        			System.out.println("1.1, going left, index: " + i + "ret " + retIndex);
//	        			i *= LEFT_CHILD_MULTIPLIER;
//	        		
//	        	}else if (child[2] != null) {
//        				System.out.println("1.1, going RIGHT, index: " + i + "ret " + retIndex);
//	        			i = (i * LEFT_CHILD_MULTIPLIER) + LEFT_TO_RIGHT_MULTIPLIER;
//	        		
//	        	}
        		
//        		if (i >= arrayOfNodes.length - Math.pow(BASE_NUMBER, getNumberOfLevels() -1)) {
//        			/*	
//        			 * 	If the current index in the tree is past the number of levels 
//            		 * 	( ie if the index is trying to to add a child on the bottom level of the tree )
//            		 * 	thus the array needs to grow in order to accommodate a new child to be added.
//            		 * 	If this is the case it will increase array length by 2^(current level + 1)
//            		 * 
//            		 */
//        			System.out.println("increasing array");
//    				addToArray((int) Math.pow(BASE_NUMBER, getNumberOfLevels()));
//    				break;
//    				
//        		}

        	}
    			//arrayOfNodes[retIndex] = procToAdd;
    		}
        
        System.out.println("finnished adding");
        for(int i = TREE_ROOT_INDEX; i < arrayOfNodes.length; i++) { 
        	if(arrayOfNodes[i] != null) {
        	System.out.print(arrayOfNodes[i].getLabel() + " ");
        	}else {
        		System.out.print(" ? ");
        	}
        }
    } // end of enqueue()


    @Override
    public String dequeue() {
        /*
         * 
         * 	- Have to dequeue the first one in (look by the priority value on the Proc)
         * 
         * 	- To find smallest we go down to the left side of the tree and find the smallest
         *  child node ie has the smallest VT value, then we find any duplicate VT
         * 	values of which find the node with the 'highest' queue order, and remove it.
         * 	- IF this node that we have chosen to remove has any children, find Left most child, 
         * 	swap the left most child with the chosen node to delete, then delete it.
         * 
         * 	# complexity: O(n)
         */
    	//making the VT we are looking for smaller then the root vt, thus will go to the left.
//    	int smallestVTFoundIndex = TREE_ROOT_INDEX;
//    	Proc smallestProc = arrayOfNodes[TREE_ROOT_INDEX];
//    	if(arrayOfNodes[TREE_ROOT_INDEX] != null && arrayOfNodes.length >=BASE_TREE_SIZE) {
//    		recursivePreorder(TREE_ROOT_INDEX);
//        	
//    	}
    		
        return getLeft(); // placeholder, modify this
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

        return FAIL_VALUE; // placeholder, modify this
    } // end of precedingProcessTime()


    @Override
    public int succeedingProcessTime(String procLabel) {
        // Implement me

        return FAIL_VALUE; // placeholder, modify this
    } // end of precedingProcessTime()


    @Override
    public void printAllProcesses(PrintWriter os) {
    	recursivePreOrderPrinter(1, os);
    	os.print("\n");
    	os.close();
    } // end of printAllProcess()
    
    
    /////// Custom methods ///////
    private void recursivePreOrderPrinter(int currentProcIndex, PrintWriter os) {
		if (currentProcIndex < arrayOfNodes.length && arrayOfNodes[currentProcIndex] != null) {
			os.print(arrayOfNodes[currentProcIndex].getLabel().toString() + " ");
			recursivePreOrderPrinter(currentProcIndex * LEFT_CHILD_MULTIPLIER, os);
			recursivePreOrderPrinter((currentProcIndex * LEFT_CHILD_MULTIPLIER) + LEFT_TO_RIGHT_MULTIPLIER, os);
			
		}
	}
    
    private String getLeft() {
    	int retProc = -1;
    	String retString = "None";
    	Proc firstFoundSmallestPocVT = null;
    	Proc foundSmallestPocVT = null;
    	for(int i = TREE_ROOT_INDEX; i < arrayOfNodes.length; i++) { 

    		Proc[] child = findChildren(i);
    		if(child[LEFT] != null) {
    			retProc = i;
    			firstFoundSmallestPocVT = child[LEFT];
    			foundSmallestPocVT = child[LEFT];
        		i *= LEFT_CHILD_MULTIPLIER;
    		}
    	}
    	//we have index of smallest Proc,
    	// need to see if there are any smilar ones.
    	foundSmallestPocVT = recursivePreorder(retProc, firstFoundSmallestPocVT);
    	retString = foundSmallestPocVT.getLabel();
    	int indexOfProcToDequeue = getIndexFor(foundSmallestPocVT);
    	arrayOfNodes[indexOfProcToDequeue] = null;
    	return retString;
    }
    
    
    private Proc recursivePreorder(int currProcIndex, Proc smallestProcVT) {
    	Proc retProc = smallestProcVT;
    	if (currProcIndex < arrayOfNodes.length && arrayOfNodes[currProcIndex] != null) {
			//writer.print(arrayOfNodes[currentNode].toString() + " ");
    		Proc tempProc = arrayOfNodes[currProcIndex];
    		if(smallestProcVT.getVt() > tempProc.getVt()) {
    			smallestProcVT = tempProc;
    		}else if(smallestProcVT.getVt() == tempProc.getVt() && smallestProcVT.getPriority() > tempProc.getPriority()) {
    			smallestProcVT = tempProc;
    		}
    		retProc = recursivePreorder(currProcIndex * LEFT_CHILD_MULTIPLIER, smallestProcVT);
    		retProc = recursivePreorder(currProcIndex * LEFT_CHILD_MULTIPLIER + LEFT_TO_RIGHT_MULTIPLIER, smallestProcVT);
		}
    	return retProc;
    }
    
    private void addToArray(int count) {
    	int newArraySize = arrayOfNodes.length + count;
		Proc[] tempArray = new Proc[newArraySize];
		for (int i = 0; i < arrayOfNodes.length; i++) {
    		System.out.println(".");

			// copies array
			tempArray[i] = arrayOfNodes[i];
		}
		// sets the updated array
		arrayOfNodes = tempArray;
	}
    
    private int getIndexFor(Proc procToFind) {
    	//essentially doing the whole divide and conquer approach 
    	if (procToFind == null) {
    		return -1;
    	}
    	for (int i = TREE_ROOT_INDEX; i < arrayOfNodes.length; i++) {
    		if (arrayOfNodes[i] != null) {
    			if(procToFind.getVt() < arrayOfNodes[i].getVt()) {
    				i *= LEFT_CHILD_MULTIPLIER; // will to to the left child of the parent. 
    			}else if(procToFind.getVt() >= arrayOfNodes[i].getVt()){
    				//need to ensure that it isn't the node we actually want.
    				if(arrayOfNodes[i].equals(procToFind)) {
        				return i;
        			}
    				

    				i = (i * LEFT_CHILD_MULTIPLIER) + LEFT_TO_RIGHT_MULTIPLIER; // will get the right child of the parent
    			}
    			if(arrayOfNodes[i].equals(procToFind)) {
    				return i;
    			}
    		}
    	}
    	System.out.println("failed");
		return FAIL_VALUE;
	}
    
    private Proc[] findChildren(int currProc) {
		Proc[] retProcArray = new Proc[3];
		int parent = (int) Math.floor(currProc / 2);
    	int parentIndex = parent;

		// left node will always be index parent * 2
//    	if(parent == null) {
//    		retProcArray[2] = new Proc("PATCH", 0, 0);
//    		return retProcArray;
//    	}

		Proc leftChild = arrayOfNodes[parentIndex * LEFT_CHILD_MULTIPLIER];
		// right node will always be index parent * 2 + 1
		Proc rightChild = arrayOfNodes[(parentIndex * LEFT_CHILD_MULTIPLIER) + LEFT_TO_RIGHT_MULTIPLIER];
		retProcArray[LEFT] = leftChild;
		retProcArray[RIGHT] = rightChild;
		//returns an array of [left child Proc, right child proc]
		return retProcArray;
	} // end of findParent
    
    private int getNumberOfLevels() {
    	
    	//This method simply gets the number of levels the tree has by performing 
    	//logarithms based on the number of proc/nodes the tree has
    	System.out.println("num levels: " + (int) (Math.log(arrayOfNodes.length) / Math.log(BASE_NUMBER)));
		return (int) (Math.log(arrayOfNodes.length) / Math.log(BASE_NUMBER));
    }
    
    private int getCurrentLevel(int index) {
    	
    	//This method simply gets the number of levels the tree has by performing 
    	//logarithms based on the number of proc/nodes the tree has
    	System.out.println("curr level: " +(int) (Math.log(index) / Math.log(BASE_NUMBER)));
		return (int) (Math.log(index) / Math.log(BASE_NUMBER));
    }
   
	
    
} // end of class BinarySearchTreeRQ
