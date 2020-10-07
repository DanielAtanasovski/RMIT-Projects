/**
 * 
 */
package structure;

import java.security.NoSuchAlgorithmException;

import util.HashUtil;

/**
 * @author Daniel Atanasovski
 *
 */
public class NonLeaf {
	
	private String hash;
	private Leaf left;
	private Leaf right;
	
	public NonLeaf(Leaf left, Leaf right) {
		this.left = left;
		this.right = right;
		try {
			this.hash = HashUtil.Hash(left.getHash() + right.getHash());
		} catch (NoSuchAlgorithmException e) {
			e.printStackTrace();
		}
	}

	public String getHash() {
		return hash;
	}
	
	public Leaf getLeftLeaf() {
		return left;
	}
	
	public Leaf getRightLeaf() {
		return right;
	}
}
