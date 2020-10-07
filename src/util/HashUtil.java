/**
 * 
 */
package util;

import java.nio.charset.StandardCharsets;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

import org.bouncycastle.util.encoders.Hex;

/**
 * @author Daniel Atanasovski
 *
 */
public class HashUtil {

	/**
	 * @param component
	 * @return hash
	 * @throws NoSuchAlgorithmException
	 */
	public static String Hash(String component) throws NoSuchAlgorithmException {
		MessageDigest digest = MessageDigest.getInstance("SHA-256");
		byte[] hash = digest.digest(component.getBytes(StandardCharsets.UTF_8));
		return new String(Hex.encode(hash));
	}

}
