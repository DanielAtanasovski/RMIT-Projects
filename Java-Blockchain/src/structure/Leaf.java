/**
 * 
 */
package structure;

import java.security.NoSuchAlgorithmException;

import types.Student;
import util.HashUtil;

/**
 * @author Daniel Atanasovski
 *
 */
public class Leaf {
	private String hash;

	public Leaf(Student student) {
		try {
			hash = HashUtil.Hash(student.toString());
		} catch (NoSuchAlgorithmException e) {
			e.printStackTrace();
		}
	}

	public String getHash() {
		return hash;
	}
}
