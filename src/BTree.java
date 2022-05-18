import java.util.List;

public class BTree {

    private Node root;
    private int maxOrder;

    public BTree(int pageSize) {
        // Create a B+ Tree
        maxOrder = (int) Math.floor(pageSize / NodeElement.MAX_SIZE);
        create();
    }

    public BTree(String indexFile) {
        //TODO: Read a index file into memory for B+ tree
    }

    public void create() {
        root = new Node();
    }

    private void insert(long key, long value) {
        root.insert(key, value);
    }


}
