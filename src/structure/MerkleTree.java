/**
 * 
 */
package structure;

import java.nio.charset.StandardCharsets;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.List;

import org.bouncycastle.util.encoders.Hex;

import types.Student;

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
			case 1:
				this.extra = new Leaf(students.get(0));
				this.rootHash = this.extra.getHash();
			case 2:
				this.left = new NonLeaf(new Leaf(students.get(0)), new Leaf(students.get(1)));
				this.rootHash = this.left.getHash();
			case 3:
				this.left = new NonLeaf(new Leaf(students.get(0)), new Leaf(students.get(1)));
				this.extra = new Leaf(students.get(2));
				try {
					this.rootHash = calculateHash(false);
				} catch (NoSuchAlgorithmException e1) {
					e1.printStackTrace();
				}
			case 4:
				this.left = new NonLeaf(new Leaf(students.get(0)), new Leaf(students.get(1)));
				this.right = new NonLeaf(new Leaf(students.get(2)), new Leaf(students.get(3)));
				try {
					this.rootHash = calculateHash(true);
				} catch (NoSuchAlgorithmException e) {
					e.printStackTrace();
				}
			}
	}

	public String getRootHash() {
		return this.rootHash;
	}

	private String calculateHash(boolean complete) throws NoSuchAlgorithmException {
		MessageDigest digest = MessageDigest.getInstance("SHA-256");
		// Convert everything into one string
		String hashComponent;
		if (complete) {
			hashComponent = left.getHash() + right.getHash();
		} else {
			hashComponent = left.getHash() + extra.getHash();
		}

		// Hash
		byte[] hash = digest.digest(hashComponent.getBytes(StandardCharsets.UTF_8));
		return new String(Hex.encode(hash));
	}
}
