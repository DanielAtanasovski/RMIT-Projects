package main;

import java.util.Scanner;

import encryption.StegDecryption;
import encryption.StegEncryption;

/**
 * @author Daniel Atanasovski
 *
 */
public class Main {

	private static final String image = "input.jpg";

	/**
	 * @param args
	 */

	public static void main(String[] args) {
		System.out.println("--- Steganography ---");
		System.out.println("--- Daniel Atanasovski ---\n");

		Scanner scanner = new Scanner(System.in);
		boolean done = false;
		int choice;
		while (!done) {
			System.out.println("1. Encrypt\n2. Decrypt\n3. Quit\n\nChoice:");
			choice = scanner.nextInt();
			switch (choice) {
			case 1:
				StegEncryption encrypt = new StegEncryption();
				break;
			case 2:
				StegDecryption decrypt = new StegDecryption();
				break;
			case 3:
				done = true;
				break;
			default:
				System.out.println("\nUnknown Input!\n\n");
			}
		}

	}

}
