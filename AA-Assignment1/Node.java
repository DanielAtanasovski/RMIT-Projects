import java.lang.String;

public class Node {
    private Node next;
    private Proc proc;

    public Node (String procLabel, int vt) {
        this.proc = new Proc(procLabel, vt);
        this.next = null;
    }

    // Getters and Setters
    public Node getNext() {
        return this.next;
    }

    public void setNext(Node next) {
        this.next = next;
    }

    public Proc getProc() {
        return this.proc;
    }


}