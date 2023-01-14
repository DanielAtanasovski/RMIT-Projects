import sun.reflect.generics.reflectiveObjects.NotImplementedException;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

public class Node implements Serializable {

    // 16 bytes for key + value pointer
    // minimum of 16 * 8 records minimum
    public static int MAX_SIZE = 128;

    private boolean leaf = true;
    private Node next = null;
    private boolean root = false;

    private int order = 0;
    public static int nodes = 0;

//    private List<NodeElement> nodeElements;
    private List<Long> keys;
    private List<Long> ridValues; // If Leaf
    private List<Node> nodeValues; // If Internal

    public Node(int order) {
        this.order = order;
        keys = new ArrayList<Long>();
        ridValues = new ArrayList<Long>();
        nodeValues = new ArrayList<Node>();
    }

    public void setNext(Node next) {
        this.next = next;
    }

    public Node getNext() {
        return next;
    }

    public void setRoot(boolean root) {
        this.root = root;
    }

    public byte[] getBytes() {
        throw new NotImplementedException();
//        return null;
    }


    public boolean isFull() {
        return keys.size() == this.order;
    }

    public List<Long> getRidValues() {
        return ridValues;
    }

    public List<Node> getNodeValues() {
        return nodeValues;
    }

    public void setNodeValues(List<Node> nodeValues) {
        this.nodeValues = nodeValues;
    }

    public List<Long> getKeys() {
        return keys;
    }

    public boolean isLeaf() {
        return leaf;
    }
    
    // unsafe insert (won't check if too big)
    public void insert(long key, long value) {
        // Simply add if empty
        if (keys.size() == 0) {
            keys.add(key);
            ridValues.add(value);
            return;
        }

        for (int i = 0; i < keys.size(); i++) {

            if (keys.get(i) == key) {
                // TODO: Duplicate
                // Ignore for now
//                System.out.println("There is a duplicate key!");
                break;
            } else if (key < keys.get(i)){
                // Smaller Key
                keys.add(i, key);
                ridValues.add(i, value);
                break;
            } else if (i + 1 == keys.size()) {
                keys.add(key);
                ridValues.add(value);
                break;
            }
        }

    }

    public void split() {
//        if (root) {
//            System.out.println("Root Splitting");
//            BPTree.height++;
//        }

        Node leftNode = new Node(order);
        Node rightNode = new Node(order);
        int middle = (int) Math.ceil(order / 2);

        // Left Node
        for (int i = 0; i < middle; i++)
            leftNode.insert(keys.get(i), ridValues.get(i));

        // Right Node
        for (int i = middle; i < keys.size(); i++)
            rightNode.insert(keys.get(i), ridValues.get(i));


        // Setup this node as internal
        keys.clear();
        ridValues.clear();
        leaf = false;

        keys.add(rightNode.getKeys().get(0));
        nodeValues.add(leftNode);
        nodeValues.add(rightNode);
    }

    public int getSize() {
        return keys.size();
    }

    public void printRecursive(int count, boolean print) {
        if (print)
            System.out.println("Node at level " + count + " has the keys: " + keys.toString());

        if (!leaf) {
            for (Node childNode : nodeValues) {
                childNode.printRecursive(count + 1, print);
            }
        }
        nodes++;
    }
}
