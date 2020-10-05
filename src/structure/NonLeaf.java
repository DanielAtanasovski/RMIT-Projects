/**
 * 
 */
package structure;

import java.nio.charset.StandardCharsets;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

import org.bouncycastle.util.encoders.Hex;

import types.Student;

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
			this.hash = calculateHash();
		} catch (NoSuchAlgorithmException e) {
			e.printStackTrace();
		}
	}

	public String getHash() {
		return hash;
	}
	
	private String calculateHash() throws NoSuchAlgorithmException {
		MessageDigest digest = MessageDigest.getInstance("SHA-256");
		// Convert everything into one string
		String hashComponent = left.getHash() + right.getHash();
		// Hash
		byte[] hash = digest.digest(hashComponent.getBytes(StandardCharsets.UTF_8));
		return new String(Hex.encode(hash));
	}
	
}
