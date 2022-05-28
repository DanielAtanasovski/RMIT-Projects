

public class BPTree {

    private Node root;
    private int maxOrder;

    public static int indexPages = 0; // Nodes
    public static int height = 0;

    public BPTree(int pageSize) {
        // Create a B+ Tree
        maxOrder = (int) Math.ceil(pageSize / Node.MAX_SIZE); // order determined by size of a node
        root = new Node(maxOrder);
        indexPages++;
    }

    public BPTree(String indexFile) {
        //TODO: Read a index file into memory for B+ tree
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

        while (!child.isLeaf()) {
            child = findInsertionPoint(child, key).getNode();
        }

        for (int i = 0; i < child.getKeys().size(); i++) {
            if (key == child.getKeys().get(i))
                return child.getRidValues().get(i);
        }

        return Long.MIN_VALUE;
    }

    public void printTree() {
        this.root.printRecursive(0);
    }



//    public Node search (long key) {
//        return treeSearch(key, root);
//    }

    // Return Node where key exists or can exist
//    private Node treeSearch(long key, Node node) {
//        if (node.isLeaf())
//            return node;
//
//        // Keep searching
//        return treeSearch(key, node.search(key));
//    }




}
