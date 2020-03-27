import java.lang.String;

public class Proc {
    private String label;
    private int vt;

    public Proc(String label, int vt){
        this.label = label;
        this.vt = vt;
    }

    /**
     * @return the label
     */
    public String getLabel() {
        return this.label;
    }

    /**
     * @return the vt
     */
    public int getVt() {
        return this.vt;
    }

}