public class NodeElement {

    private boolean internal;
    private long days; // Key: days since 01/01/1970
    private long rid = Long.MAX_VALUE; // Value: record id in heap (if leaf)
    private Node node = null; // Value: next node (if internal)

    public static final int MAX_SIZE = Long.SIZE + Long.SIZE + 1; // days bytes + rid bytes + metadata byte

    // Leaf Constructor
    public NodeElement(long days, long rid) {
        this.internal = false;
        this.days = days;
        this.rid = rid;
    }

    // Internal Constructor
    public NodeElement(long days, Node node) {
        this.internal = true;
        this.days = days;
        this.node = node;
    }

    public boolean isInternal() {
        return internal;
    }

    public long getDays() {
        return days;
    }

    public long getRid() {
        return rid;
    }

    public Node getNode() {
        return node;
    }
}
