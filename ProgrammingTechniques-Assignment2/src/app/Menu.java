package app;

import java.util.Scanner;

import cars.Car;
import exceptions.InvalidDate;
import exceptions.InvalidRefreshments;
import utilities.DateTime;
import utilities.DateUtilities;

/*
 * Class:		Menu
 * Description:	The class a menu and is used to interact with the user. 
 * Author:		Rodney Cocker
 */
public class Menu
{
	private Scanner console = new Scanner(System.in);
	private MiRideApplication application = new MiRideApplication();
	// Allows me to turn validation on/off for testing business logic in the
	// classes.
	private boolean testingWithValidation = true;

	/*
	 * Runs the menu in a loop until the user decides to exit the system.
	 */
	public void run()
	{
		final int MENU_ITEM_LENGTH = 2;
		String input;
		String choice = "";
		do
		{
			printMenu();

			input = console.nextLine().toUpperCase();

			if (input.length() != MENU_ITEM_LENGTH)
			{
				System.out.println("Error - selection must be two characters!");
			} else
			{
				System.out.println();

				switch (input)
				{
				case "CC":
					try {
						createCar();
					} catch (InvalidRefreshments e) {
						System.out.println(e.getMessage());
						continue;
					}
					break;
				case "BC":
					try {
						book();
					} catch (InvalidDate e) {
						System.out.println(e.getMessage());
						continue;
					}
					break;
				case "CB":
					completeBooking();
					break;
				case "DA":
					displayAll();
					break;
				case "SS":
					System.out.print("Enter Registration Number: ");
					System.out.println(application.displaySpecificCar(console.nextLine()));
					break;
				case "SA":
					searchAvailableCars();
					break;
				case "SD":
					application.seedData();
					break;
				case "EX":
					choice = "EX";
					System.out.println("Exiting Program ... Goodbye!");
					break;
				default:
					System.out.println("Error, invalid option selected!");
					System.out.println("Please try Again...");
				}
			}

		} while (choice != "EX");
	}

	/*
	 * Creates cars for use in the system available or booking.
	 */
	private void createCar() throws InvalidRefreshments, NumberFormatException
	{
		String id = "", make, model, driverName, serviceType;
		int numPassengers = 0;
		double fee = 0;
		String[] refreshments = null;
		boolean silverService = false;

		System.out.print("Enter registration number: ");
		id = promptUserForRegNo();
		if (id.length() != 0)
		{
			// Get details required for creating a car.
			System.out.print("Enter Make: ");
			make = console.nextLine();

			System.out.print("Enter Model: ");
			model = console.nextLine();

			System.out.print("Enter Driver Name: ");
			driverName = console.nextLine();

			System.out.print("Enter number of passengers: ");
			numPassengers = promptForPassengerNumbers();
			if (numPassengers == 0)
				return;
			
			System.out.print("Enter Service Type (SD/SS): ");
			serviceType = console.nextLine();

			if (serviceType.toUpperCase().equals("SS")) {
				System.out.print("Enter Standard Fee: ");
				fee = promptForFee();
				
				System.out.print("Enter List of Refreshments: ");
				refreshments = promptForRefreshments();
				silverService = true;
				
			} else if (!serviceType.toUpperCase().equals("SD")) {
				System.out.println("Error - Invalid service type");
				return; 
			}
			
			boolean result = application.checkIfCarExists(id);

			if (!result)
			{
				String carRegistrationNumber = application.createCar(id, make, model, driverName,
						numPassengers, silverService, fee, refreshments);
				System.out.println(carRegistrationNumber);
			} else
			{
				System.out.println("Error - Already exists in the system");
			}
		}
	}

	/*
	 * Book a car by finding available cars for a specified date.
	 */
	private boolean book() throws InvalidDate
	{
		System.out.println("Enter date car required: ");
		System.out.println("format DD/MM/YYYY)");
		String dateEntered = console.nextLine();
		DateTime dateRequired = generateDate(dateEntered);
		
		if(!DateUtilities.dateIsNotInPast(dateRequired) || !DateUtilities.dateIsNotMoreThan7Days(dateRequired))
		{
			System.out.println("Date is invalid, must be within the coming week.");
			return false;
		}
		
		
		String[] availableCars = application.book(dateRequired);
		for (int i = 0; i < availableCars.length; i++)
		{
			System.out.println(availableCars[i]);
		}
		if (availableCars.length != 0)
		{
			System.out.println("Please enter a number from the list:");
			int itemSelected = Integer.parseInt(console.nextLine());
			
			String regNo = availableCars[itemSelected - 1];
			regNo = regNo.substring(regNo.length() - 6);
			System.out.println("Please enter your first name:");
			String firstName = console.nextLine();
			System.out.println("Please enter your last name:");
			String lastName = console.nextLine();
			System.out.println("Please enter the number of passengers:");
			int numPassengers = Integer.parseInt(console.nextLine());
			String result = application.book(firstName, lastName, dateRequired, numPassengers, regNo);

			System.out.println(result);
		} else
		{
			System.out.println("There are no available cars on this date.");
		}
		return true;
	}
	
	/*
	 * Takes in an input string and converts it a new date
	 */
	private DateTime generateDate(String input) throws NumberFormatException, IndexOutOfBoundsException{
		int day = Integer.parseInt(input.substring(0, 2));
		int month = Integer.parseInt(input.substring(3, 5));
		int year = Integer.parseInt(input.substring(6));
		return new DateTime(day, month, year);
	}
	
	/*
	 * Complete bookings found by either registration number or booking date.
	 */
	private void completeBooking() throws NumberFormatException, NullPointerException
	{
		System.out.print("Enter Registration or Booking Date:");
		String response = console.nextLine();
		
		String result;
		// User entered a booking date
		if (response.contains("/"))
		{
			double kilometers = 0;
			System.out.print("Enter First Name:");
			String firstName = console.nextLine();
			System.out.print("Enter Last Name:");
			String lastName = console.nextLine();
			System.out.print("Enter kilometers:");
			
			try {
				kilometers = Double.parseDouble(console.nextLine());
			} catch (NumberFormatException e) {
				throw e;
			} catch (NullPointerException e) {
				throw e;
			}
			
			DateTime dateOfBooking = generateDate(response);
			result = application.completeBooking(firstName, lastName, dateOfBooking, kilometers);
			System.out.println(result);
		} else
		{
			
			System.out.print("Enter First Name:");
			String firstName = console.nextLine();
			System.out.print("Enter Last Name:");
			String lastName = console.nextLine();
			if(application.getBookingByName(firstName, lastName, response))
			{
				System.out.print("Enter kilometers:");
				double kilometers = Double.parseDouble(console.nextLine());
				result = application.completeBooking(firstName, lastName, response, kilometers);
				System.out.println(result);
			}
			else
			{
				System.out.println("Error: Booking not found.");
			}
		}
		
	}
	
	private int promptForPassengerNumbers() throws NumberFormatException
	{
		int numPassengers = 0;
		boolean validPassengerNumbers = false;
		// By pass user input validation.
		if (!testingWithValidation)
		{
			return Integer.parseInt(console.nextLine());
		} 
		else
		{
			while (!validPassengerNumbers)
			{
				try {
					numPassengers = Integer.parseInt(console.nextLine());
				} catch (NumberFormatException e) {
					System.out.println("Error - Invalid Passengers");
					return 0;
				}
				
				String validId = application.isValidPassengerCapacity(numPassengers);
				if (validId.contains("Error:"))
				{
					System.out.println(validId);
					System.out.println("Enter passenger capacity: ");
					System.out.println("(or hit ENTER to exit)");
				} else
				{
					validPassengerNumbers = true;
				}
			}
			return numPassengers;
		}
	}
	
	private void displayAll() {
		String stringType;
		boolean silverServiceType = false;
		boolean orderType = false;
		
		// Service Type
		System.out.println("Enter Type (SD/SS): ");
		stringType = console.nextLine();
		if (stringType.toUpperCase().equals("SD")) {
			silverServiceType = false;
		} else if (stringType.toUpperCase().equals("SS")) {
			silverServiceType = true;
		} else {
			System.out.println("Invalid Service Type");
		}
		
		// Order Type
		System.out.println("Enter Sort Order (A/D): ");
		stringType = console.nextLine();
		if (stringType.toUpperCase().equals("A")) {
			orderType = true;
		} else if (stringType.toUpperCase().equals("D")) {
			orderType = false;
		} else {
			System.out.println("Invalid Order Type");
		}
		
		// Get Output
		String allCars = application.displayAllBookings(silverServiceType, orderType);
		if (allCars == null) {
			System.out.println("Error - No Cars were found of the selected type.");
			return;
		}
			
		System.out.println(allCars);
	}
	
	private void searchAvailableCars() {
		String stringType;
		boolean silverServiceType = false;
		DateTime date;
		
		// Type Check
		System.out.println("Enter Type (SD/SS): ");
		stringType = console.nextLine();
		if (stringType.toUpperCase().equals("SD")) {
			silverServiceType = false;
		} else if (stringType.toUpperCase().equals("SS")) {
			silverServiceType = true;
		} else {
			System.out.println("Invalid Service Type");
		}
		
		System.out.println("Enter Date: ");
		date = promptForDate();
		
		Car[] availableCars = application.getCarsAvailable(date, silverServiceType);
		if(availableCars[0] == null) {
			System.out.println("Error - No cars were found for this date.");
			return;
		}
		// Display Available Cars
		for (int i = 0; i < availableCars.length; i++) {
			if (availableCars[i] == null) 
				break;
			
			System.out.println(availableCars[i].getDetails());
		}
	}
	/*
	 * Checks user input for valid fee
	 */
	//TODO: Exception for invalid number
	private double promptForFee() {
//		double fee = 0.0;
//		boolean validFee = false;
//		if (!testingWithValidation) {
//			return Double.parseDouble(console.nextLine());
//		} else {
//			while(!validFee) {
//				fee = Double.parseDouble(console.nextLine());
//				
//			}
//			return fee;
//		}
		return Double.parseDouble(console.nextLine());
	}
	
	/*
	 * Checks user input for valid refreshment list
	 */
	// TODO: Exception for invalid List
	private String[] promptForRefreshments() throws InvalidRefreshments {
		String line = console.nextLine();
		String[] refreshments = line.split(",");
		
		if (refreshments.length < 3) 
			throw new InvalidRefreshments("Error - Not enough Refreshments.");
		if (duplicateRefreshmentCheck(refreshments))
			throw new InvalidRefreshments("Error - Duplicate refreshments detected.");
		
		return refreshments;
	}
	
	/*
	 * Check for duplicate Refreshments
	 */
	private boolean duplicateRefreshmentCheck(String[] refreshments) {
		for (int i = 0; i < refreshments.length; i++) {
			String currentItem = refreshments[i];
			for (int j = 0; j < refreshments.length; j++) {
				if (j == i)
					continue;
				
				if (currentItem.equals(refreshments[j])) {
					return false;
				}
			}
		}
		return true;
	}
	
	private DateTime promptForDate() {
		String date = console.nextLine();
		int day = Integer.parseInt(date.substring(0, 2));
		int month = Integer.parseInt(date.substring(3, 5));
		int year = Integer.parseInt(date.substring(6));
		return new DateTime(day,month,year);
	}

	/*
	 * Prompt user for registration number and validate it is in the correct form.
	 * Boolean value for indicating test mode allows by passing validation to test
	 * program without user input validation.
	 */
	private String promptUserForRegNo()
	{
		String regNo = "";
		boolean validRegistrationNumber = false;
		// By pass user input validation.
		if (!testingWithValidation)
		{
			return console.nextLine();
		} 
		else
		{
			while (!validRegistrationNumber)
			{
				regNo = console.nextLine();
				boolean exists = application.checkIfCarExists(regNo);
				if(exists)
				{
					// Empty string means the menu will not try to process
					// the registration number
					System.out.println("Error: Reg Number already exists");
					return "";
				}
				if (regNo.length() == 0)
				{
					break;
				}

				String validId = application.isValidId(regNo);
				if (validId == null || validId.contains("Error:"))
				{
					System.out.println("Enter registration number: ");
					System.out.println("(or hit ENTER to exit)");
				} else
				{
					validRegistrationNumber = true;
				}
			}
			return regNo;
		}
	}

	/*
	 * Prints the menu.
	 */
	private void printMenu()
	{
		System.out.printf("\n********** MiRide System Menu **********\n\n");

		System.out.printf("%-30s %s\n", "Create Car", "CC");
		System.out.printf("%-30s %s\n", "Book Car", "BC");
		System.out.printf("%-30s %s\n", "Complete Booking", "CB");
		System.out.printf("%-30s %s\n", "Display ALL Cars", "DA");
		System.out.printf("%-30s %s\n", "Search Specific Car", "SS");
		System.out.printf("%-30s %s\n", "Search Available Cars", "SA");
		System.out.printf("%-30s %s\n", "Seed Data", "SD");
		System.out.printf("%-30s %s\n", "Exit Program", "EX");
		System.out.println("\nEnter your selection: ");
		System.out.println("(Hit enter to cancel any operation)");
	}
}
