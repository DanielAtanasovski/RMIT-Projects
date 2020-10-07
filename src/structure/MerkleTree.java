/**
 * 
 */
package structure;

import java.security.NoSuchAlgorithmException;
import java.util.List;

import types.Student;
import util.HashUtil;

/**
 * @author Daniel Atanasovski
 *
 */
public class MerkleTree {

	private String rootHash;
	private NonLeaf left;
	private NonLeaf right;
	private Leaf extra;

	public MerkleTree(List<Student> students) {
		switch (students.size()) {
		case 0:
			this.rootHash = "";
			break;
		case 1:
			this.extra = new Leaf(students.get(0));
			this.rootHash = this.extra.getHash();
			break;
		case 2:
			this.left = new NonLeaf(new Leaf(students.get(0)), new Leaf(students.get(1)));
			this.rootHash = this.left.getHash();
			break;
		case 3:
			this.left = new NonLeaf(new Leaf(students.get(0)), new Leaf(students.get(1)));
			this.extra = new Leaf(students.get(2));
			try {
				this.rootHash = HashUtil.Hash(left.getHash() + extra.getHash());

			} catch (NoSuchAlgorithmException e1) {
				e1.printStackTrace();
			}
			break;
		case 4:
			this.left = new NonLeaf(new Leaf(students.get(0)), new Leaf(students.get(1)));
			this.right = new NonLeaf(new Leaf(students.get(2)), new Leaf(students.get(3)));
			try {
				this.rootHash = HashUtil.Hash(left.getHash() + right.getHash());
			} catch (NoSuchAlgorithmException e) {
				e.printStackTrace();
			}
			break;
		}
	}

	public String getRootHash() {
		return this.rootHash;
	}

	public NonLeaf getLeft() {
		return left;
	}

	public NonLeaf getRight() {
		return right;
	}

	@Override
	public String toString() {
		String topLayer = "|" + rootHash + "|";
		String middleLayer = "|" + left.getHash() + "|\t" + "|" + right.getHash() + "|\n";
		String bottomLayer = "|" + left.getLeftLeaf().getHash() + "|\t" + "|" + left.getRightLeaf().getHash() + "|\t"
				+ "|" + right.getLeftLeaf().getHash() + "|\t" + "|" + right.getRightLeaf().getHash() + "|";
		
		// indent to align
		middleLayer = middleLayer.indent((bottomLayer.length()/2) - (middleLayer.length()/2));
		topLayer = topLayer.indent((middleLayer.length()/2) - (topLayer.length()/8));
		
		// Build Output
		StringBuilder stringBuilder = new StringBuilder();
		stringBuilder.append("--- Merkle Tree ---\n");
		stringBuilder.append(topLayer);
		stringBuilder.append(middleLayer);
		stringBuilder.append(bottomLayer);
		return stringBuilder.toString();
	}
}
