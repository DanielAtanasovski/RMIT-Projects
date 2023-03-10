/**
 * 
 */
package main;

import java.security.NoSuchAlgorithmException;
import java.security.Security;
import java.util.Scanner;

import blockchain.Block;
import blockchain.BlockChain;
import blockchain.Server;
import types.Student;
import util.HashUtil;

/**
 * @author Daniel Atanasovski
 *
 */
public class Main {

	public static Server serverA;
	public static Server serverB;
	public static Server serverC;

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// Hashing Algorithm
		Security.addProvider(new org.bouncycastle.jce.provider.BouncyCastleProvider());

		// BlockChain
		BlockChain testChain = new BlockChain();

		// Servers
		serverA = new Server(testChain);
		serverB = new Server(new BlockChain(testChain));
		serverC = new Server(new BlockChain(testChain));

		// User Interface
		System.out.println("--- Blockchain ---");
		System.out.println("--- Daniel Atanasovski ---");

		boolean isSeeded = false;
		boolean done = false;
		Scanner scanner = new Scanner(System.in);

		// Interface Loop
		while (!done) {
			// Show Choices
			System.out.println();
			System.out.println("1. Admin Add Student");
			System.out.println("2. Employer Verify");
			System.out.println("3. Print Blockchain");
			System.out.println("4. Seed Blockchain");
			int choice = scanner.nextInt();

			if (choice == 1) {
				// Adding a Student
				System.out.println("Enter Student data to add: ");
				Student student = getStudentData(scanner);
				Block fullBlock = serverA.getChain().addStudent(student);
				if (fullBlock != null) {
					// new block is full and will simulate someone mining it instantly
					updateServers(fullBlock);
				}
			} else if (choice == 2) {
				// Verifying a Student
				System.out.println("Enter Student data to verify: ");

				Student student = getStudentData(scanner);
				Block block = serverB.getChain().verifyStudent(student);

				try {
					System.out.println("Student Hash to find: " + HashUtil.Hash(student.toString()));
				} catch (NoSuchAlgorithmException e) {
					e.printStackTrace();
				}

				if (block != null) {
					System.out.println("Student Successfully Verified!");
					System.out.println("Student found in block " + block.getIndex());
					System.out.println(block.getTree().toString());
				} else {
					System.out.println("Student Unsuccessfully Verified!");
					System.out.println("Student does not exist on the blockchain");
				}

			} else if (choice == 3) {
				System.out.println(serverC.getChain().toString());

			} else if (choice == 4) {
				if (!isSeeded) {
					isSeeded = true;
					System.out.println();
					Student student1 = new Student("s5235", "David Wallace", "Bachelor of Commerce", "14/06/1994", 2.4f,
							2021);
					Student student2 = new Student("s4467", "Emily Butler", "Bachelor of Computer Science",
							"10/10/1996", 3.2f, 2020);
					Student student3 = new Student("s5235", "Rey Walker", "Bachelor of Accounting", "11/03/1997", 3.6f,
							2021);
					Student student4 = new Student("s8484", "Michael Edwards", "Bachelor of Computer Science",
							"13/05/1999", 2.1f, 2020);
					Student student5 = new Student("s9565", "Peter Parker", "Bachelor of Sport Science", "18/02/2000",
							3.0f, 2023);
					Student student6 = new Student("s2123", "Tony Stark", "Bachelor of Electrical Engineering",
							"14/08/1997", 2.2f, 2021);
					Student student7 = new Student("s7532", "John Krasinski", "Bachelor of Commerce", "26/03/1998",
							1.9f, 2023);
					Student student8 = new Student("s2332", "Kaitlyn Hope", "Bachelor of Aerospace Engineering",
							"28/06/1999", 3.8f, 2020);
					Student student9 = new Student("s4567", "Moses Phillips", "Bachelor of Computer Engineering",
							"19/07/1998", 3.3f, 2022);
					Student student10 = new Student("s5595", "Luke Skies", "Bachelor of Computer Science", "23/11/2000",
							2.6f, 2021);
					Student student11 = new Student("s4595", "Ryan Jeremy", "Bachelor of Mechanical Engineering",
							"09/02/1995", 2.9f, 2020);
					Student student12 = new Student("s2149", "Alex Jacobs", "Bachelor of Aerospace Engineering",
							"02/08/1990", 3.5f, 2022);
					serverA.getChain().addStudent(student1);
					serverA.getChain().addStudent(student2);
					serverA.getChain().addStudent(student3);
					Block fullBlock = serverA.getChain().addStudent(student4);
					updateServers(fullBlock);
					serverA.getChain().addStudent(student5);
					serverA.getChain().addStudent(student6);
					serverA.getChain().addStudent(student7);
					fullBlock = serverA.getChain().addStudent(student8);
					updateServers(fullBlock);
					serverA.getChain().addStudent(student9);
					serverA.getChain().addStudent(student10);
					serverA.getChain().addStudent(student11);
					fullBlock = serverA.getChain().addStudent(student12);
					updateServers(fullBlock);
				}
			} else {
				System.out.println("Unknown Choice! \n");
			}
		}
	}

	private static void updateServers(Block block) {
		if (serverA.verifyChain(block) && serverB.verifyChain(block) && serverC.verifyChain(block)) {
			serverA.updateChain(block);
			serverB.updateChain(block);
			serverC.updateChain(block);
		}
	}

	public static Student getStudentData(Scanner scanner) {
		System.out.println("Student Number: ");
		scanner.nextLine();
		String number = scanner.nextLine();
		System.out.println("Student Name: ");
		String name = scanner.nextLine();
		System.out.println("Degree Name: ");
		String degree = scanner.nextLine();
		System.out.println("DOB (dd/mm/yyyy): ");
		String dob = scanner.nextLine();
		System.out.println("CGPA: ");
		float gpa = scanner.nextFloat();
		System.out.println("Graduation Year (yyyy): ");
		int year = scanner.nextInt();

		Student student = new Student(number, name, degree, dob, gpa, year);
		return student;
	}

}
