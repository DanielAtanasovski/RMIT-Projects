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
public class Leaf {
	private Student student;
	private String hash;
	
	public Leaf(Student student) {
		this.student = student;
		try {
			hash = calculateHash();
		} catch (NoSuchAlgorithmException e) {
			e.printStackTrace();
		}
	}
	
	private String calculateHash() throws NoSuchAlgorithmException {
		MessageDigest digest = MessageDigest.getInstance("SHA-256");
		// Convert everything into one string
		String hashComponent = student.toString();
		// Hash
		byte[] hash = digest.digest(hashComponent.getBytes(StandardCharsets.UTF_8));
		return new String(Hex.encode(hash));
	}
	
	public String getHash() {
		return hash;
	}
}
