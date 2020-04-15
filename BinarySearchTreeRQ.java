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
	private Proc[] tempRebalArray; //holds nodes to be re-added in after deletion to make tree balance again.
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
        tempRebalArray = new Proc[0];
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
        addToTree(procToAdd);
    } // end of enqueue()


    private void addToTree(Proc procToAdd) {
    	if(arrayOfNodes[TREE_ROOT_INDEX] == null) {
        	arrayOfNodes[TREE_ROOT_INDEX] = procToAdd;
        }else {
        	int i = TREE_ROOT_INDEX;
        	
        	while(i <= arrayOfNodes.length) { //worse case in n, however should be closer to log(n)

        		int leftChild = i* LEFT_CHILD_MULTIPLIER;
        		int rightChild = (i * LEFT_CHILD_MULTIPLIER) + LEFT_TO_RIGHT_MULTIPLIER;

        		if(leftChild >= arrayOfNodes.length || rightChild >= arrayOfNodes.length || i >= arrayOfNodes.length) {
        			addToArray((int) Math.pow(2, getNumberOfLevels()));
        		}
        		
        		if(i <= arrayOfNodes.length) {
        			if(procToAdd.getVt() < arrayOfNodes[i].getVt()) {
        				i = leftChild;
        			}else if(procToAdd.getVt() >= arrayOfNodes[i].getVt()) {
        				i = rightChild;
        			}
        			if(arrayOfNodes[i] == null) {
        				arrayOfNodes[i] = procToAdd;
        				break;
        			}
        		}
        	}		
    	}
    }
    
    
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
         * 
         */
    	
    	/*
    	 * the smallest Proc in this tree will always be on the left most side, thus can find a multiple of 2.
    	 */
    	String retVal = "";
    	if(arrayOfNodes.length <= BASE_TREE_SIZE && arrayOfNodes[TREE_ROOT_INDEX] == null) {
    		retVal = "";
    	}else if(arrayOfNodes.length == BASE_TREE_SIZE && arrayOfNodes[TREE_ROOT_INDEX] != null) {
    		retVal = arrayOfNodes[TREE_ROOT_INDEX].getLabel();
    		arrayOfNodes[TREE_ROOT_INDEX] = null;
         }else {
	    	int smallestProcIndex = 1; 
	    	int treeLevels = getNumberOfLevels() - TREE_ROOT_INDEX;
	    	int tempIndex = 1;
	    	for(int i = 0; i <= treeLevels; i ++) {
	    		tempIndex = (int) Math.pow(BASE_NUMBER, i);
	    		if(arrayOfNodes[tempIndex] != null) {
	    			smallestProcIndex = tempIndex;
	    		}
	    		
	    	}
	    	Proc smallestProc = arrayOfNodes[smallestProcIndex];
	    	int i = (smallestProcIndex * LEFT_CHILD_MULTIPLIER) + LEFT_TO_RIGHT_MULTIPLIER;
        	while(i<= arrayOfNodes.length) { //worse case in n^2, however should be closer to n log(n)
        		int leftChild = i* LEFT_CHILD_MULTIPLIER;
        		int rightChild = (i * LEFT_CHILD_MULTIPLIER) + LEFT_TO_RIGHT_MULTIPLIER;
        		if(i <= arrayOfNodes.length) {
        			
        			if(arrayOfNodes[i] != null && smallestProc.getVt() < arrayOfNodes[i].getVt()) {
        				i = leftChild;
        			}else if(arrayOfNodes[i] != null && smallestProc.getVt() >= arrayOfNodes[i].getVt()) {
        				if(smallestProc.getVt() == arrayOfNodes[i].getVt() && 
        						smallestProc.getPriority() < arrayOfNodes[i].getPriority()) {
        					smallestProcIndex = i;
        					smallestProc = arrayOfNodes[i];
        				}
        				i = rightChild;
        				continue;
        			}
        			if(i <= arrayOfNodes.length && arrayOfNodes[i] != null && smallestProc.getVt() == arrayOfNodes[i].getVt() && 
    					smallestProc.getPriority() < arrayOfNodes[i].getPriority()) {
    					smallestProcIndex = i;
    					smallestProc = arrayOfNodes[i];
    					i = rightChild -1;
    					continue;
    				}
        			
        			if(i > arrayOfNodes.length || arrayOfNodes[i] == null) {
        				break;
        			}
        			
        		}else {
        			break;
        		}
        	}
	    		
        	Proc tempsmallestProc = smallestProc;
        	int tempSmallest = smallestProcIndex;
	    	if((smallestProcIndex * LEFT_CHILD_MULTIPLIER) + LEFT_TO_RIGHT_MULTIPLIER < arrayOfNodes.length &&
	    			arrayOfNodes[(smallestProcIndex * LEFT_CHILD_MULTIPLIER) + LEFT_TO_RIGHT_MULTIPLIER] != null){
		    	i = (smallestProcIndex * LEFT_CHILD_MULTIPLIER) + LEFT_TO_RIGHT_MULTIPLIER;
	        	while(i<= arrayOfNodes.length) { //worse case in n^2, however should be closer to n log(n)
			    	tempSmallest = i;

	        		int leftChild = i* LEFT_CHILD_MULTIPLIER;
	        		int rightChild = (i * LEFT_CHILD_MULTIPLIER) + LEFT_TO_RIGHT_MULTIPLIER;
	        		if(i <= arrayOfNodes.length) {
	        			if(arrayOfNodes[i] != null && smallestProc.getVt() < arrayOfNodes[i].getVt()) {
	        				i = leftChild;
	        			}else if(arrayOfNodes[i] != null && smallestProc.getVt() >= arrayOfNodes[i].getVt()) {
		        			i = rightChild;
	        			}
	        			if(i > arrayOfNodes.length || arrayOfNodes[i] == null) {
	        				break;
	        			}
	        			
	        		}else {
	        			break;
	        		}
	        	}
	    	}	    	
	    	if(i > arrayOfNodes.length) {
	    		i = (int) Math.floor(i / 2);
	    	}
    		Proc tempProc = null;
    		Proc tempProc2 = null;
    		int temprearange = smallestProcIndex;
    		
    		
			int rightChild = (temprearange * LEFT_CHILD_MULTIPLIER) + LEFT_TO_RIGHT_MULTIPLIER;
			
			if(rightChild < arrayOfNodes.length && arrayOfNodes[rightChild] != null) {
				tempProc = arrayOfNodes[temprearange];
				tempProc2 = arrayOfNodes[rightChild];
				//check if the parent nodes left child is null or not
	    			
	    			
	       		arrayOfNodes[rightChild] = tempProc;
	    		arrayOfNodes[temprearange] = tempProc2;
	
		    	Proc procToDelete = arrayOfNodes[rightChild];
				
		    	recursivePreorderAddToArray(rightChild);
		    	//arrayOfNodes[rightChild] = null;
		    	
		    	for(int j = 0; j < tempRebalArray.length; j++) {
		    		//early termination
		    		boolean swapped = false;
		        	for(int l = 0; l < tempRebalArray.length; l++) {
		        		Proc temp = null;
		        		if(tempRebalArray[j].getPriority() > tempRebalArray[l].getPriority()) {
		        			temp = tempRebalArray[l];
		        			tempRebalArray[l] = tempRebalArray[j];
		        			tempRebalArray[j] = tempRebalArray[l];
		        			swapped = true;
		        		}
		        	}
		        	if(!swapped) {
		        		break;
		        	}
		        }
		        for(int l = 0; l < tempRebalArray.length; l++) {
		        	if(!tempRebalArray[l].equals(procToDelete)) {
			        	addToTree(tempRebalArray[l]);
		        	}
		        }
		        tempRebalArray = new Proc[0];
			}else {
				arrayOfNodes[temprearange] = null;
		    	//dynamiclyShrinkArray();

			}
			if(tempsmallestProc == null) {
				retVal = "";
			}else {
				retVal = tempsmallestProc.getLabel();
			}
         }
    	dynamiclyShrinkArray();
    	return retVal;
    } // end of dequeue()


    @Override
    public boolean findProcess(String procLabel) {
        // Implement me
    	// complexity is O(n-1)
    	for(int i = TREE_ROOT_INDEX; i < arrayOfNodes.length; i++) {
    		if(arrayOfNodes[i] != null && arrayOfNodes[i].getLabel().equals(procLabel)){
    			return true;
    		}
    	}
        return false; // placeholder, modify this
    } // end of findProcess()


    @Override
    public boolean removeProcess(String procLabel) {
    	// complexity is O(n-1)
    	// Assignment spec sheet does not specify FIFO, thus the fist proc found with the specified procLabel will be removed.
    	for(int i = TREE_ROOT_INDEX; i < arrayOfNodes.length; i++) {
    		if(arrayOfNodes[i] != null && arrayOfNodes[i].getLabel().equals(procLabel)){
    	    	recursivePreorderAddToArray(i);
    	    	for(int l = 0; l < tempRebalArray.length; l++) {
//    	    		if(tempRebalArray[l]!= null && arrayOfNodes[i]!= null &&!arrayOfNodes[i].equals(tempRebalArray[l])) {
//    	    			System.out.println("....adding to array");
    	    		if(tempRebalArray[l] != null && !tempRebalArray[l].getLabel().equals(procLabel)){
    	    			addToTree(tempRebalArray[l]);
    	    		}
//    	    		}
    	    	}
    	        tempRebalArray = new Proc[0];
    	        dynamiclyShrinkArray();
    	    	return true;
    	    }
    	}
    	


        return false; // placeholder, modify this
    } // end of removeProcess()

    

    @Override
    public int precedingProcessTime(String procLabel) {
        // Implement me
    	Proc foundProc = getProcByLabel(procLabel);
    	if(foundProc == null) {
    		return FAIL_VALUE;
    	}
    	int foundProcIndex = getIndexFor(foundProc);
    	int topParent = foundProcIndex;
    	getCurrentLevel(foundProcIndex);
    	while(topParent < arrayOfNodes.length && arrayOfNodes[(int) Math.floor(topParent / 2)] != null 
    			&& getCurrentLevel(topParent) == getCurrentLevel(topParent -1)){
    		topParent = (int) Math.floor(topParent / 2);
    	}
    			
    	
    	int retPvVal = 0;
    	retPvVal = recursivePreorderGetPrev(topParent, foundProc, retPvVal);
        return retPvVal; // placeholder, modify this
    } // end of precedingProcessTime()


    @Override
    public int succeedingProcessTime(String procLabel) {
    	 // Implement me
    	Proc foundProc = getProcByLabel(procLabel);
    	if(foundProc == null) {
    		return FAIL_VALUE;
    	}
    	int foundProcIndex = getIndexFor(foundProc);

    	int topParent = foundProcIndex;
    	getCurrentLevel(foundProcIndex);
    	while(topParent < arrayOfNodes.length && arrayOfNodes[(int) Math.floor(topParent / 2)] != null 
    			&& getCurrentLevel(topParent) == getCurrentLevel(topParent +1)) {
    		topParent = ((int) Math.floor(topParent / 2));
    	}
    			
    	int retPvVal = 0;
    	retPvVal = recursivePreorderGetPost(topParent, foundProc, retPvVal);
        return retPvVal; // placeholder, modify this
    } // end of precedingProcessTime()


    @Override
    public void printAllProcesses(PrintWriter os) {
    	recursivePreOrderPrinter(1, os);
    	os.print("\n");
    	os.flush();	
    } // end of printAllProcess()
    
    
    /////// Custom methods ///////
    
    
    private void recursivePreOrderPrinter(int currentProcIndex, PrintWriter os) {
		if (currentProcIndex < arrayOfNodes.length && arrayOfNodes[currentProcIndex] != null) {
			os.print(arrayOfNodes[currentProcIndex].getLabel().toString() + " ");
			recursivePreOrderPrinter(currentProcIndex * LEFT_CHILD_MULTIPLIER, os);
			recursivePreOrderPrinter((currentProcIndex * LEFT_CHILD_MULTIPLIER) + LEFT_TO_RIGHT_MULTIPLIER, os);
		}
	}
    
    private Proc getSmallestProcPriority() {
    	/*
    	 * the smallest Proc in this tree will always be on the left most side, thus can find a multiple of 2.
    	 */
    	 if(arrayOfNodes.length == BASE_TREE_SIZE && arrayOfNodes[TREE_ROOT_INDEX] != null) {
         	return arrayOfNodes[TREE_ROOT_INDEX];
         }else {
	    	int smallestProcIndex = 1; 
	    	int treeLevels = getNumberOfLevels() - TREE_ROOT_INDEX;
	    	int tempIndex = 1;
	    	for(int i = 0; i <= treeLevels; i ++) {
	    		tempIndex = (int) Math.pow(BASE_NUMBER, i);
	    		if(arrayOfNodes[tempIndex] != null) {
	    			smallestProcIndex = tempIndex;
	    		}
	    		
	    	}
	    	Proc smallestProc = arrayOfNodes[smallestProcIndex];
	    	int i = (smallestProcIndex * LEFT_CHILD_MULTIPLIER) + LEFT_TO_RIGHT_MULTIPLIER;
        	while(i<= arrayOfNodes.length) { //worse case in n^2, however should be closer to n log(n)
        		int leftChild = i* LEFT_CHILD_MULTIPLIER;
        		int rightChild = (i * LEFT_CHILD_MULTIPLIER) + LEFT_TO_RIGHT_MULTIPLIER;
        		if(i <= arrayOfNodes.length) {        			
        			if(arrayOfNodes[i] != null && smallestProc.getVt() < arrayOfNodes[i].getVt()) {
        				i = leftChild;
        			}else if(arrayOfNodes[i] != null && smallestProc.getVt() >= arrayOfNodes[i].getVt()) {
        				if(smallestProc.getVt() == arrayOfNodes[i].getVt() && 
        						smallestProc.getPriority() < arrayOfNodes[i].getPriority()) {
        					smallestProcIndex = i;
        					smallestProc = arrayOfNodes[i];
        				}
        				i = rightChild;
        				continue;
        			}
        			if(i <= arrayOfNodes.length && arrayOfNodes[i] != null && smallestProc.getVt() == arrayOfNodes[i].getVt() && 
    					smallestProc.getPriority() < arrayOfNodes[i].getPriority()) {
    					smallestProcIndex = i;
    					smallestProc = arrayOfNodes[i];
    					i = rightChild -1;
    					continue;
    				}
        			
        			if(i > arrayOfNodes.length || arrayOfNodes[i] == null) {
        				break;
        			}
        			
        		}else {
        			break;
        		}
        	}	    		
        	Proc tempsmallestProc = smallestProc;
        	int tempSmallest = smallestProcIndex;
	    	if((smallestProcIndex * LEFT_CHILD_MULTIPLIER) + LEFT_TO_RIGHT_MULTIPLIER < arrayOfNodes.length &&
	    			arrayOfNodes[(smallestProcIndex * LEFT_CHILD_MULTIPLIER) + LEFT_TO_RIGHT_MULTIPLIER] != null){
		    	i = (smallestProcIndex * LEFT_CHILD_MULTIPLIER) + LEFT_TO_RIGHT_MULTIPLIER;
	        	while(i<= arrayOfNodes.length) { //worse case in n^2, however should be closer to n log(n)
			    	tempSmallest = i;

	        		int leftChild = i* LEFT_CHILD_MULTIPLIER;
	        		int rightChild = (i * LEFT_CHILD_MULTIPLIER) + LEFT_TO_RIGHT_MULTIPLIER;
	        		if(i <= arrayOfNodes.length) {
	        			if(arrayOfNodes[i] != null && smallestProc.getVt() < arrayOfNodes[i].getVt()) {
	        				i = leftChild;

	        			}else if(arrayOfNodes[i] != null && smallestProc.getVt() >= arrayOfNodes[i].getVt()) {
		        			i = rightChild;
	        			}
	        			if(i > arrayOfNodes.length || arrayOfNodes[i] == null) {
	        				break;
	        			}
	        			
	        		}else {
	        			break;
	        		}
	        	}
	    	}
	    	
	    	if(i > arrayOfNodes.length) {
	    		i = (int) Math.floor(i / 2);
	    	}

    		Proc tempProc = null;
    		Proc tempProc2 = null;
    		int temprearange = smallestProcIndex;
    		
    		
			int rightChild = (temprearange * LEFT_CHILD_MULTIPLIER) + LEFT_TO_RIGHT_MULTIPLIER;
			
			if(rightChild < arrayOfNodes.length && arrayOfNodes[rightChild] != null) {
				tempProc = arrayOfNodes[temprearange];
				tempProc2 = arrayOfNodes[rightChild];
				//check if the parent nodes left child is null or not
	    			
	    			
	       		arrayOfNodes[rightChild] = tempProc;
	    		arrayOfNodes[temprearange] = tempProc2;
	
		    	Proc procToDelete = arrayOfNodes[rightChild];
				
		    	recursivePreorderAddToArray(rightChild);
		    	//arrayOfNodes[rightChild] = null;
		    	
		    	for(int j = 0; j < tempRebalArray.length; j++) {
		    		//early termination
		    		boolean swapped = false;
		        	for(int l = 0; l < tempRebalArray.length; l++) {
		        		Proc temp = null;
		        		if(tempRebalArray[j].getPriority() > tempRebalArray[l].getPriority()) {
		        			temp = tempRebalArray[l];
		        			tempRebalArray[l] = tempRebalArray[j];
		        			tempRebalArray[j] = tempRebalArray[l];
		        			swapped = true;
		        		}
		        	}
		        	if(!swapped) {
		        		break;
		        	}
		        }
		        for(int l = 0; l < tempRebalArray.length; l++) {
		        	if(!tempRebalArray[l].equals(procToDelete)) {
			        	addToTree(tempRebalArray[l]);
		        	}
		        }
		        tempRebalArray = new Proc[0];
			}else {
				arrayOfNodes[temprearange] = null;
				
			}
	    	return tempsmallestProc;
         }
    }
    
    
    
    
    private void recursivePreorderAddToArray(int currProcIndex) {
    	// complexity is O(n)
    	if (currProcIndex < arrayOfNodes.length && arrayOfNodes[currProcIndex] != null) {
    		Proc tempProc = arrayOfNodes[currProcIndex];
    		arrayOfNodes[currProcIndex] = null; //delete the node in the list
    		addToRebalArray(tempProc);
    		recursivePreorderAddToArray(currProcIndex * LEFT_CHILD_MULTIPLIER);
    		recursivePreorderAddToArray(currProcIndex * LEFT_CHILD_MULTIPLIER + LEFT_TO_RIGHT_MULTIPLIER);
		}
    }
    
    private int recursivePreorderGetPrev(int currProcIndex, Proc selectedProc, int retVal) {
    	// complexity is O(n)
    	if (currProcIndex < arrayOfNodes.length && arrayOfNodes[currProcIndex] != null) {
    		if(arrayOfNodes[currProcIndex].getVt() < selectedProc.getVt() || 
    				(arrayOfNodes[currProcIndex].getVt() == selectedProc.getVt() 
    				&& arrayOfNodes[currProcIndex].getPriority() < selectedProc.getPriority())) {
    			retVal+= arrayOfNodes[currProcIndex].getVt();
    		}
    		retVal = recursivePreorderGetPrev(currProcIndex * LEFT_CHILD_MULTIPLIER, selectedProc, retVal);
    		retVal = recursivePreorderGetPrev(currProcIndex * LEFT_CHILD_MULTIPLIER + LEFT_TO_RIGHT_MULTIPLIER, selectedProc, retVal);
		}
    	return retVal;
    }
    
    private int recursivePreorderGetPost(int currProcIndex, Proc selectedProc, int retVal) {
    	// complexity is O(n)
    	if (currProcIndex < arrayOfNodes.length && arrayOfNodes[currProcIndex] != null) {
    		if(arrayOfNodes[currProcIndex].getVt() > selectedProc.getVt() || 
    				(arrayOfNodes[currProcIndex].getVt() == selectedProc.getVt() 
    				&& arrayOfNodes[currProcIndex].getPriority() > selectedProc.getPriority())) {
    			retVal+= arrayOfNodes[currProcIndex].getVt();
    		}
    		retVal = recursivePreorderGetPost(currProcIndex * LEFT_CHILD_MULTIPLIER, selectedProc, retVal);
    		retVal = recursivePreorderGetPost(currProcIndex * LEFT_CHILD_MULTIPLIER + LEFT_TO_RIGHT_MULTIPLIER, selectedProc, retVal);
		}
    	return retVal;
    }
    
    private void addToArray(int count) {
    	int newArraySize = arrayOfNodes.length + count;
		Proc[] tempArray = new Proc[newArraySize];
		for (int i = 0; i < arrayOfNodes.length; i++) {

			// copies array
			tempArray[i] = arrayOfNodes[i];
		}
		// sets the updated array
		arrayOfNodes = tempArray;
	}
    
    
    
    private void addToRebalArray(Proc procToReAdd) {
    	int newArraySize = (tempRebalArray.length + 1);
		Proc[] tempArray = new Proc[newArraySize];
		if(tempRebalArray.length == 0) {
			tempRebalArray = tempArray;
		}
		for (int i = 0; i < tempRebalArray.length; i++) {
			
			
			// copies array
			tempArray[i] = tempRebalArray[i];
		}
		// sets the updated array
		tempRebalArray = tempArray;
		tempRebalArray[newArraySize -1] = procToReAdd;

	}
    
    
    
    private int getIndexFor(Proc procToFind) {
    	//essentially doing the whole divide and conquer approach 
    	if (procToFind == null) {
    		return -1;
    	}
    	for (int i = TREE_ROOT_INDEX; i < arrayOfNodes.length;) {
			if(arrayOfNodes[i] != null && procToFind.getVt() < arrayOfNodes[i].getVt()) {
				i *= LEFT_CHILD_MULTIPLIER; // will to to the left child of the parent. 
			}else if(arrayOfNodes[i] != null && procToFind.getVt() >= arrayOfNodes[i].getVt()){
				//need to ensure that it isn't the node we actually want.
				if(arrayOfNodes[i].equals(procToFind)) {
    				return i;
    			}
				i = (i * LEFT_CHILD_MULTIPLIER) + LEFT_TO_RIGHT_MULTIPLIER; // will get the right child of the parent
			}
			if(i < arrayOfNodes.length && arrayOfNodes[i] != null && arrayOfNodes[i].equals(procToFind)) {
				return i;
			}

    	}
		return FAIL_VALUE;
	}
    
    private Proc[] findChildren(int currProc) {
		Proc[] retProcArray = new Proc[2];
    	Proc leftChild = null;
    	Proc rightChild = null;
    	int leftChildIndex = currProc * LEFT_CHILD_MULTIPLIER;
    	int rightChildIndex = (currProc * LEFT_CHILD_MULTIPLIER) + LEFT_TO_RIGHT_MULTIPLIER;
    	
    	if(leftChildIndex < arrayOfNodes.length) {
    		leftChild = arrayOfNodes[leftChildIndex];
    	}
    		
		// right node will always be index parent * 2 + 1
    	if(rightChildIndex < arrayOfNodes.length) {
    		rightChild = arrayOfNodes[rightChildIndex];
    	}
    	
		retProcArray[LEFT] = leftChild;
		retProcArray[RIGHT] = rightChild;
		//returns an array of [left child Proc, right child proc]
		return retProcArray;
	} // end of findParent
    
    private int getNumberOfLevels() {
    	
    	//This method simply gets the number of levels the tree has by performing 
    	//logarithms based on the number of proc/nodes the tree has
		return (int) (Math.log(arrayOfNodes.length) / Math.log(BASE_NUMBER));
    }
    
    private int getCurrentLevel(int index) {
    	
    	//This method simpl-y gets the number of levels the tree has by performing 
    	//logarithms based on the number of proc/nodes the tree has
		return (int) (Math.log(index) / Math.log(BASE_NUMBER));
    }
   
	
    private Proc getProcByLabel(String label) {
    	Proc procToReturn = null;
    	for(int i = TREE_ROOT_INDEX; i < arrayOfNodes.length; i++) {
    		if(arrayOfNodes[i] != null && arrayOfNodes[i].getLabel().equals(label)) {
    			procToReturn = arrayOfNodes[i];
    		}
    	}
    	return procToReturn;
    }
    
    private void dynamiclyShrinkArray() {
    	int levels = getNumberOfLevels();
    	int startIndex = (int) Math.pow(BASE_NUMBER, levels);
    	int endIndex = (int)(startIndex/BASE_NUMBER);
    	/*start looking at the bottom levels then progress up. since the bottom levels are
    	 * most likely to be empty, thus can remove a level.
    	 * 
    	 * Complexity: O(n^2)
    	*/ 
    	boolean canShrink = true;
    	for(int i = levels; i > 0; i--) {
    		for(int j = startIndex-1; j > endIndex; j--) {
    			if(j < arrayOfNodes.length && arrayOfNodes[j] != null) {
    				canShrink = false;
    				break;
    			}
    		}
    		if(canShrink) {
    			/*if the the lower level can't be shrunk then stop, as the level above 
    			 * can not be shrunk, as it is the parent. Thus break early.
    			 */
    			break;
    		}
    	}
    	if(canShrink) {
    		int tempArraySize = endIndex;
    		Proc[] tempArray = new Proc[arrayOfNodes.length - (int)(startIndex/BASE_NUMBER)];
    		if(tempArray.length == TREE_ROOT_INDEX) {
    			tempArray = new Proc[BASE_TREE_SIZE];
    		}
    		for(int i = TREE_ROOT_INDEX; i < tempArray.length; i ++) {
    			 tempArray[i] = arrayOfNodes[i]; 
    		}
    		arrayOfNodes = tempArray;
    	}
    	
    }
    
} // end of class BinarySearchTreeRQ
