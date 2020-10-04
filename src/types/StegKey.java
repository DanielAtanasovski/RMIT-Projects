package types;

import java.util.List;

public class StegKey implements java.io.Serializable {
	private int length;
	private List<Position> positions;
	
	public StegKey(int length, List<Position> positions) {
		this.length = length;
		this.positions = positions;
	}

	public int getLength() {
		return length;
	}

	public List<Position> getPositions() {
		return positions;
	}
	
	
}
