import java.util.*;

public class SearchResult {
    private long key;
    private List<Long> values;

    public SearchResult(long key, List<Long> values) {
        this.key = key;
        this.values = values;
    }

    public List<Long> getValues() {
        return values;
    }

    public long getKey() {
        return key;
    }
}
