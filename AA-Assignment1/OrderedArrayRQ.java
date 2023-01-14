import java.io.PrintWriter;
import java.lang.String;


/**
 * Implementation of the Runqueue interface using an Ordered Array.
 *
 * Your task is to complete the implementation of this class.
 * You may add methods and attributes, but ensure your modified class compiles and runs.
 *
 * @author Sajal Halder, Minyi Li, Jeffrey Chan
 */
public class OrderedArrayRQ implements Runqueue {

    private Node processes[];
    private int size;
    private int capacity = 10;
    

    /**
     * Constructs empty queue
     */
    public OrderedArrayRQ() {
        processes = new Node[capacity];
        size = 0;

    }  // end of OrderedArrayRQ()


    @Override
    public void enqueue(String procLabel, int vt) {
        // O(n)
        
        // Reached array limit, increase Size
        if (capacity == size){
            capacity++;
            Node tempArr[] = new Node[capacity];
            System.arraycopy(processes, 0, tempArr, 0, processes.length);
            processes = tempArr;
        }

        // Add the new process
        processes[size] = new Node(procLabel, vt);
        size++;

        // Resort the array
        sort();

    } // end of enqueue()

    /** 
     * Resorts the array
    */
    private void sort() {
        // O(n)
        // Based on bubble sort
        boolean loop = true;
        // We only stop looping when no swap occurs
        while (loop) {
            boolean swapOccurred = false;
            for (int i = 0; i < size; i++) {
                // If we aren't the last element (as there is nothing after it)
                if ((i + 1) != size) {
                    if (processes[i].getProc().getVt() > processes[i + 1].getProc().getVt()){
                        // Swap processes
                        Node temp = processes[i];
                        processes[i] = processes[i + 1];
                        processes[i + 1] = temp;
                        swapOccurred = true;
                    }
                }
            }
            // If no swaps happened, we can assume that it is sorted
            if (!swapOccurred)
                loop = false;
        }
    }


    @Override
    public String dequeue() {
        String retString = "";

        // If there is no processes
        // list is empty
        if (size != 0){
            retString = processes[0].getProc().getLabel();

            // Move each element up in the list
            for (int i = 0; i < size; i++) {
                if ((i - 1) != -1)
                    processes[i - 1] = processes[i];
            }

            // Reduce count
            size--;
        }

        

        return retString;
    } // end of dequeue()

    @Override
    public boolean findProcess(String procLabel){
        // O(n)
        boolean found = false;
        for (int i = 0; i < size; i++) {
            if (processes[i].getProc().getLabel().equals(procLabel)){
                found = true;
                break;
            }
        }

        return found;
    } // end of findProcess()


    @Override
    public boolean removeProcess(String procLabel) {
        boolean deleted = false;
        if (size != 0){
            // Move each element up in the list
            for (int i = 0; i < size; i++) {
                if (deleted){
                    if ((i - 1) != -1) // Check we aren't getting the -1 element
                        processes[i - 1] = processes[i];
                }

                // Found the process, now move up following elements
                if (processes[i].getProc().getLabel().equals(procLabel)){
                    deleted = true;
                }
            }
        }

        if (deleted)
            size--;

        return deleted;
    } // end of removeProcess()


    @Override
    public int precedingProcessTime(String procLabel) {
        int preTime = -1;
        int foundProc = -1;

        // Find the process
        foundProc = getProcIndex(procLabel);

        if (foundProc != -1){
            // first in the list, so none before
            if (foundProc == 0){
                preTime = 0;
            } else {
                preTime = 0;
                for (int i = 0; i < foundProc; i++) {
                    preTime += processes[i].getProc().getVt();
                }
            }
        }

        return preTime;
    }// end of precedingProcessTime()


    @Override
    public int succeedingProcessTime(String procLabel) {
        int sucTime = -1;
        int foundProc = -1;

        foundProc = getProcIndex(procLabel);

        if (foundProc != -1) {
            // Last element in the list, so none after
            if (foundProc  == size - 1) {
                sucTime = 0;
            } else {
                sucTime = 0;
                for (int i = foundProc + 1; i < size; i++) {
                    sucTime += processes[i].getProc().getVt();
                }
            }
        }
        
        return sucTime;
    } // end of precedingProcessTime()

    private int getProcIndex(String procLabel) {
        int foundProc = -1;

        for (int i = 0; i < size; i++) {
            if (processes[i].getProc().getLabel().equalsIgnoreCase(procLabel)){
                foundProc = i;
                break;
            }
        }

        return foundProc;
    }


    @Override
    public void printAllProcesses(PrintWriter os) {
        for (int i = 0; i < size; i++) {
            os.print(processes[i].getProc().getLabel());

            if (i != (size-1))
                os.print(" ");
        }
        os.println();

    } // end of printAllProcesses()

} // end of class OrderedArrayRQ
