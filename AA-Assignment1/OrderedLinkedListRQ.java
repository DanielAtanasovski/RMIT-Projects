import java.io.PrintWriter;
import java.lang.String;

/**
 * Implementation of the run queue interface using an Ordered Link List.
 *
 * Your task is to complete the implementation of this class.
 * You may add methods and attributes, but ensure your modified class compiles and runs.
 *
 * @author Sajal Halder, Minyi Li, Jeffrey Chan.
 */
public class OrderedLinkedListRQ implements Runqueue {

    private Node head;

    /**
     * Constructs empty linked list
     */
    public OrderedLinkedListRQ() {
        head = null;
    }  // end of OrderedLinkedList()


    @Override
    public void enqueue(String procLabel, int vt) {
        // O(n)
        Node newNode = new Node(procLabel, vt);
        Node prevNode = null;
        Node checkNode = head;

        // Cases
        if (head == null) {
            // No Head
            head = newNode;
        } else if (vt < head.getProc().getVt()){
            // Smaller than Head
            head = newNode;
            head.setNext(checkNode);
        } else {
            // Everything else
            prevNode = head;
            checkNode = head.getNext();
            boolean set = false;

            while(!set) {
                if (checkNode == null) {
                    // End of list
                    prevNode.setNext(newNode);
                    set = true;
                } else if (vt < checkNode.getProc().getVt()){
                    // Less than current node
                    prevNode.setNext(newNode);
                    newNode.setNext(checkNode);
                    set = true;
                } else {
                    // Iterate to next node
                    prevNode = checkNode;
                    checkNode = prevNode.getNext();
                }
            }
        }
    } // end of enqueue()


    @Override
    public String dequeue() {
        // O(1)
        String retString = "";

        if (head != null) {
            // Start of the list is typically the lowest
            retString = head.getProc().getLabel();
            head = head.getNext();
        }

        return retString;
    } // end of dequeue()


    @Override
    public boolean findProcess(String procLabel) {
        // O(n)
        boolean found = false;
        Node currentNode = head;

        while (currentNode != null) {
            if (currentNode.getProc().getLabel().equalsIgnoreCase(procLabel)){
                found = true;
                break;
            }
            currentNode = currentNode.getNext();
        }

        return found;
    } // end of findProcess()


    @Override
    public boolean removeProcess(String procLabel) {
        // O(n)
        boolean found = false;
        Node prevNode = head;
        Node currentNode = head.getNext();
        // Head
        if (head.getProc().getLabel().equalsIgnoreCase(procLabel)) {
            head = head.getNext();
        } else {
            // Rest of list
            while (currentNode != null) {
                if (currentNode.getProc().getLabel().equalsIgnoreCase(procLabel)) {
                    prevNode.setNext(currentNode.getNext());
                    found = true;
                    break;
                }
                prevNode = currentNode;
                currentNode = currentNode.getNext();
            }
        }

        return found;
    } // End of removeProcess()


    @Override
    public int precedingProcessTime(String procLabel) {
        // O(n)
        int count = 0;
        boolean found = false;
        
        if (head != null){
            Node currentNode = head;
            while (currentNode != null){
                if (currentNode.getProc().getLabel().equalsIgnoreCase(procLabel)){
                    // Found the node! Break loop
                    found = true;
                    break;
                }
                    
                // Next Node
                count += currentNode.getProc().getVt();
                currentNode = currentNode.getNext();
            }
        }

        if (!found)
            count = -1;

        return count;
    } // end of precedingProcessTime()


    @Override
    public int succeedingProcessTime(String procLabel) {
        int count = 0;
        boolean found = false;
        
        if (head != null){
            Node currentNode = head;
            while (currentNode != null){

                // Check if found
                if (found) {
                    count += currentNode.getProc().getVt();
                }

                if (currentNode.getProc().getLabel().equalsIgnoreCase(procLabel)){
                    // Found the node! Start Counting
                    found = true;
                }
                    
                // Next Node
                currentNode = currentNode.getNext();
            }
        }

        if (!found)
            count = -1;

        return count;
    } // end of precedingProcessTime()


    @Override
    public void printAllProcesses(PrintWriter os) {
        // O(n)
        if (head != null) {
            Node currentNode = head;
            while (currentNode != null) {
                os.print(currentNode.getProc().getLabel());
                currentNode = currentNode.getNext();

                // To Remove the extra space at the end
                if (currentNode != null)
                    os.print(" ");
            }
            os.println();
        }
    } // end of printAllProcess()

} // end of class OrderedLinkedListRQ
