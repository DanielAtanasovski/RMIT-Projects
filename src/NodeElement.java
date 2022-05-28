public class NodeElement {

    private boolean internal;
    private long key; // Key: days since 01/01/1970
    private long value = Long.MAX_VALUE; // Value: record id in heap (if leaf)
    private Node node  = null; // Value: next node (if internal)

    public static final int MAX_SIZE = Long.SIZE + Long.SIZE + 1; // days bytes + rid bytes + metadata byte

    // Leaf Constructor
    public NodeElement(long key, long value) {
        this.internal = false;
        this.key = key;
        this.value = value;
    }

    // Internal Constructor
    public NodeElement(long key, Node node) {
        this.internal = true;
        this.key = key;
        this.node = node;
    }

    public boolean isInternal() {
        return internal;
    }

    public long getKey() {
        return key;
    }

    public long getValue() {
        return value;
    }

    public Node getNode() {
        return node;
    }
}
