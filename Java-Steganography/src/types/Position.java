/**
 * 
 */
package types;

/**
 * @author Daniel Atanasovski
 *
 */
public class Position implements java.io.Serializable {
	private int x;
	private int y;

	public Position(int x, int y) {
		this.x = x;
		this.y = y;
	}

	public int getX() {
		return x;
	}

	public int getY() {
		return y;
	}

	@Override
	public boolean equals(Object o) {
		if (this == o) {
			return true;
		}

		if (o == null || getClass() != o.getClass()) {
			return false;
		}

		Position pos = (Position) o;

		if (pos.x == x && pos.y == y)
			return true;

		return false;
	}

	@Override
	public String toString() {
		return String.format("(%d, %d)", this.x, this.y);
	}
}
