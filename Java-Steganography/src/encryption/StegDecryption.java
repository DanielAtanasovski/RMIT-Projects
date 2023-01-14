package encryption;

import java.awt.Color;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.util.List;

import javax.imageio.ImageIO;

import types.Position;
import types.StegKey;

/**
 * @author Daniel Atanasovski
 *
 */
public class StegDecryption {

	private static final String IMAGE_FILE_NAME = "output.png";
	private static final String KEY_FILE_NAME = "key";

	private BufferedImage image;
	private String data;
	private byte[] byteData;
	private StegKey key;

	public StegDecryption() {
		System.out.println();
		try {
			image = ImageIO.read(new File(IMAGE_FILE_NAME));
		} catch (IOException e) {
			e.printStackTrace();
		}

		loadKey();
		decrypt();
	}

	private void loadKey() {
		try {
			FileInputStream keyFile = new FileInputStream(KEY_FILE_NAME);
			ObjectInputStream in = new ObjectInputStream(keyFile);
			key = (StegKey) in.readObject();
			in.close();
			keyFile.close();

		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		}

	}

	private void decrypt() {
		String decryptedMessage = "";
		List<Position> positions = key.getPositions();

		// Decrypt
		for (int i = 0; i < key.getLength(); i++) {
			// Get Pixel
			int decryptedCharacter = 0;
			Color pixel = new Color(image.getRGB(positions.get(i).getX(), positions.get(i).getY()));

			// Decrypt Red Channel
			int r = pixel.getRed();
			r &= 0b00000111; // Clear all data except the one we need
			decryptedCharacter |= r;

			// Decrypt Green Channel
			int g = pixel.getGreen();
			g &= 0b00000111; // Clear all data except the one we need
			g <<= 3;
			decryptedCharacter |= g;

			// Decrypt Blue Channel
			int b = pixel.getBlue();
			b &= 0b00000011; // Clear all data except the one we need
			b <<= 6;
			decryptedCharacter |= b;

			char decryptedChar = (char) decryptedCharacter;
			decryptedMessage += decryptedChar;
		}

		System.out.println("Message Decrypted: " + decryptedMessage + "\n");
	}
}
