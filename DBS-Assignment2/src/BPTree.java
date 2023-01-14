import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class BPTree implements Serializable{

    private Node root;
    private int maxOrder;

    public static int indexPages = 0; // Nodes
    public static int height = 0;

    public BPTree(int pageSize) {
        // Create a B+ Tree
        maxOrder = (int) Math.ceil(pageSize / Node.MAX_SIZE); // order determined by size of a node
        root = new Node(maxOrder);
        root.setRoot(true);
        indexPages++;
    }

    public BPTree(byte[] indexFileBytes) {
        //TODO: Read a index file into memory for B+ tree
    }

    public byte[] save() {
        //TODO: Better Save B+ Tree to index file
        boolean done = false;
        int count = 0;
        Node node = root;
        while (!done) {
            if (!node.isLeaf()) {
                if (node.getNodeValues().size() > 0) {
                    node = node.getNodeValues().get(0);
                } else {
                    done = true;
                }
                count++;
            } else {
                done = true;
            }
        }
        System.out.println("Height:" + count);
        ByteArrayOutputStream  bos = new ByteArrayOutputStream ();
        ObjectOutputStream      oos = null;
        try {
            oos = new ObjectOutputStream (bos);
            oos.writeObject(this);
            oos.flush();
            oos.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

        return bos.toByteArray();
    }

    public void insert(long key, long value) {
        Node parent = null;
        Node child = this.root;

        // Search for leaf
        InsertionResult insertionResult = null;
        while (!child.isLeaf()) {
            parent = child;
            insertionResult = findInsertionPoint(child, key);
            child = insertionResult.getNode();
        }

        child.insert(key, value);

        // Split if full
        if (child.isFull()) {
            child.split();

            if (parent != null && !parent.isFull())
                integrateNewNodes(parent, child, insertionResult.getIndex());
        }

    }

    private InsertionResult findInsertionPoint(Node node, long key) {
        for (int i = 0; i < node.getKeys().size(); i++) {
            long compareKey = node.getKeys().get(i);
            if (key < compareKey)
                return new InsertionResult(node.getNodeValues().get(i), i);
        }
        int max = node.getKeys().size();
        return new InsertionResult(node.getNodeValues().get(max), max);
    }

    private void integrateNewNodes(Node parent, Node child, int index) {
        parent.getNodeValues().remove(index); //
        long midPoint = child.getKeys().get(0);

        for (int i = 0; i < parent.getKeys().size(); i++) {
            long parentKey = parent.getKeys().get(i);
            if (midPoint < parentKey) {
                parent.getKeys().add(i, midPoint);
                parent.getNodeValues().add(i, child.getNodeValues().get(0)); // left
                parent.getNodeValues().add(i + 1, child.getNodeValues().get(1)); // right
                break;
            } else if (i + 1 == parent.getKeys().size()) {
                // add to end
                parent.getKeys().add(midPoint);
                parent.getNodeValues().add(child.getNodeValues().get(0)); // left
                parent.getNodeValues().add(child.getNodeValues().get(1)); // right
                break;
            }
        }
    }

    public long search(long key) {
        Node child = this.root;
        List<Long> results = new ArrayList<>();

        // Get through internal nodes
        while (!child.isLeaf()) {
            child = findInsertionPoint(child, key).getNode();
        }

        // Search leaf node children
        for (int i = 0; i < child.getKeys().size(); i++) {
            if (key == child.getKeys().get(i))
                return child.getRidValues().get(i);
        }

        return Long.MIN_VALUE;
    }

    public void printTree(boolean print) {
        Node.nodes = 0;

        this.root.printRecursive(0, print);
    }
}
