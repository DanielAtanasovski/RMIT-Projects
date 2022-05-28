import java.util.List;

public class InsertionResult {

    private Node node;
    private int index;

    public InsertionResult(Node node, int index) {
        this.node = node;
        this.index = index;
    }

    public int getIndex() {
        return index;
    }

    public Node getNode() {
        return node;
    }
}
