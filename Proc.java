import java.lang.String;

public class Proc {
    private String label;
    private int vt;
    private boolean hasBeenFound = false;
    private int priority = 0;

    public Proc(String label, int vt){
        this.label = label;
        this.vt = vt;
    }

    //alternate constructor that will take a priorityQueue number
    public Proc(String label, int vt, int priority){
        this.label = label;
        this.vt = vt;
        this.priority = priority;
    }
    /**
     * @return the label
     */
    public String getLabel() {
        return label;
    }

    /**
     * @return the vt
     */
    public int getVt() {
        return this.vt;
    }

    public String print() {
    	return "Proc: " + this.label + " vt: " + this.vt + " priority: " + this.priority + "\n";
    }
    
    public void setHasBeenFound(boolean found) {
    	/*set if node has been searched and added to a list.
    	*better to add space then searching through a list of found procs, 
    	*which will add a much bigger complexity
    	*/
    	this.hasBeenFound = found;
    }
    
    public boolean hasBeenFound() {
    	return this.hasBeenFound;
    }
    
    public void setPriority(int priority) {
    	this.priority = priority;
    }
    
    public int getPriority() {
    	return this.priority;
    }
}