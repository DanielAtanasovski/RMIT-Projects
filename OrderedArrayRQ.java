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

    private Proc processes[];
    private int procCount;

    /**
     * Constructs empty queue
     */
    public OrderedArrayRQ() {
        processes = new Proc[10];
        procCount = 0;

    }  // end of OrderedArrayRQ()


    @Override
    public void enqueue(String procLabel, int vt) {
        // O(n)
        
        // Reached array limit, increase Size
        if (processes.length-1 == procCount){
            Proc tempArr[] = new Proc[procCount+1];
            System.arraycopy(processes, 0, tempArr, 0, processes.length);
            processes = tempArr;
        }

        // Add the new process
        processes[procCount] = new Proc(procLabel, vt);
        procCount++;

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
            for (int i = 0; i < procCount; i++) {
                // If we aren't the last element (as there is nothing after it)
                if ((i + 1) != procCount) {
                    if (processes[i].getVt() > processes[i + 1].getVt()){
                        // Swap processes
                        Proc temp = processes[i];
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
        if (procCount != 0){
            retString = processes[0].getLabel();

            // Move each element up in the list
            for (int i = 1; i < procCount; i++) {
                processes[i - 1] = processes[i];
            }
        }

        // Reduce count
        procCount--;

        return retString;
    } // end of dequeue()

    @Override
    public boolean findProcess(String procLabel){
        // O(n)
        boolean found = false;
        for (int i = 0; i < procCount; i++) {
            if (processes[i].getLabel().equals(procLabel)){
                found = true;
                break;
            }
        }

        return found;
    } // end of findProcess()


    @Override
    public boolean removeProcess(String procLabel) {
        boolean deleted = false;
        if (procCount != 0){
            // Move each element up in the list
            for (int i = 1; i < procCount; i++) {
                if (deleted)
                processes[i - 1] = processes[i];

                if (processes[i].getLabel().equals(procLabel)){
                    deleted = true;
                }
            }
        }

        return deleted;
    } // end of removeProcess()


    @Override
    public int precedingProcessTime(String procLabel) {
        // Implement me

        return -1; // placeholder, modify this
    }// end of precedingProcessTime()


    @Override
    public int succeedingProcessTime(String procLabel) {
        // Implement me

        return -1; // placeholder, modify this
    } // end of precedingProcessTime()


    @Override
    public void printAllProcesses(PrintWriter os) {
        for (int i = 0; i < procCount; i++) {
            os.print(processes[i].getLabel());

            if (i != (procCount-1))
                os.print(" ");
        }
        os.println();

    } // end of printAllProcesses()

} // end of class OrderedArrayRQ
