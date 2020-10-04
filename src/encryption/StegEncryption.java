package encryption;

import java.awt.Color;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectOutputStream;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.Scanner;

import javax.imageio.ImageIO;

import types.Position;
import types.StegKey;

/**
 * @author Daniel Atanasovski
 *
 */
public class StegEncryption {

	private static final String IMAGE_FILE_NAME = "input.jpg";
	private static final String KEY_FILE_NAME = "key";

	private BufferedImage inputImage;
	private BufferedImage outputImage;

	private byte[] byteData;
	private List<Position> pixelPositions;

	Random random;

	public StegEncryption() {
		random = new Random();

		gatherData();
		encrypt();
	}

	private void gatherData() {
		Scanner scanner = new Scanner(System.in);

		// Get Data to encrypt
		System.out.println("Please enter message to be encrypted: ");
		String data = scanner.nextLine();
		byteData = data.getBytes();

		// Convert File to BufferedImage Object
		try {
			inputImage = outputImage = ImageIO.read(new File(IMAGE_FILE_NAME));
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	private void encrypt() {
		pixelPositions = new ArrayList<Position>();
		
		// Encryption
		for (int i = 0; i < byteData.length; i++) {

			// Get data ready
			Position pos = getRandomPosition();
			Color oldPixelColor = new Color(inputImage.getRGB(pos.getX(), pos.getY()));
			System.out.printf("Encrypting at pos: (%d,%d)\n", pos.getX(), pos.getY());
			int bit = byteData[i];

			// Update Red Channel
			int r = oldPixelColor.getRed();
			int data = bit & 0b00000111; // Select bits to be encrypted from byte
			r &= 0b11111000; // Clear bytes where data is to be stored on LSB side
			r |= data; // add data

			// Update Green Channel
			int g = oldPixelColor.getGreen();
			data = bit & 0b00111000; // Select bits to be encrypted from byte
			data >>>= 3; // Shift so that data is at the end
			g &= 0b11111000; // Clear bytes where data is to be stored on LSB side
			g |= data; // add data

			// Update Blue Channel
			int b = oldPixelColor.getBlue();
			data = bit & 0b11000000; // Select bits to be encrypted from byte
			data >>>= 6; // Shift so that data is at the end
			b &= 0b11111100; // Clear bytes where data is to be stored on LSB side
			b |= data; // add data

			// Combine Channels in new image
			Color newPixelColor = new Color(r, g, b);
			outputImage.setRGB(pos.getX(), pos.getY(), newPixelColor.getRGB());
		}

		// Save Output File
		File outputFile = new File("output.png");
		saveKey();

		try {
			ImageIO.write(outputImage, "png", outputFile);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	private Position getRandomPosition() {
		boolean found = false;
		Position pos = null;
		while (!found) {
			int x = random.nextInt(inputImage.getWidth() + 1);
			int y = random.nextInt(inputImage.getHeight() + 1);
			pos = new Position(x, y);

			if (!pixelPositions.contains(pos)) {
				found = true;
			}
		}

		pixelPositions.add(pos);
		return pos;
	}

	private void saveKey() {
		// Generate Key
		StegKey key = new StegKey(byteData.length, pixelPositions);
		System.out.printf("Generating Key: <%d, %s>\n", byteData.length, pixelPositions.toString());
		// Save to File
		try {
			FileOutputStream keyFile = new FileOutputStream(KEY_FILE_NAME);
			ObjectOutputStream out = new ObjectOutputStream(keyFile);
			out.writeObject(key);
			out.close();
			keyFile.close();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		System.out.println("Key Saved.\nEncryption Done.\n");
	}
}
