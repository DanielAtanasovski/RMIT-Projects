package app;

import cars.Car;
import cars.SilverServiceCar;
import exceptions.InvalidBooking;
import utilities.DateTime;
import utilities.MiRidesUtilities;

/*
 * Class:			MiRideApplication
 * Description:		The system manager the manages the 
 *              	collection of data. 
 * Author:			Rodney Cocker
 */
public class MiRideApplication
{
	private Car[] cars = new Car[15];
	private int itemCount = 0;
	private String[] availableCars;

	public MiRideApplication()
	{
		//seedData();
	}
	
	public String createCar(String id, String make, String model, String driverName,
			int numPassengers, boolean silverService, Double fee, String[] refreshments) 
	{
		String validId = isValidId(id);
		if(isValidId(id).contains("Error:"))
		{
			return validId;
		}

		if(!checkIfCarExists(id)) {
			cars[itemCount] = (silverService) ? new SilverServiceCar(id, make, model, driverName, numPassengers, fee, refreshments)
					: new Car(id, make, model, driverName, numPassengers);
			itemCount++;
			return "New Car added successfully for registion number: " + cars[itemCount-1].getRegistrationNumber();
		}
		return "Error: Already exists in the system.";
	}

	
	public String[] book(DateTime dateRequired)
	{
		int numberOfAvailableCars = 0;
		// finds number of available cars to determine the size of the array required.
		for(int i=0; i<cars.length; i++)
		{
			if(cars[i] != null)
			{
				if(!cars[i].isCarBookedOnDate(dateRequired))
				{
					numberOfAvailableCars++;
				}
			}
		}
		if(numberOfAvailableCars == 0)
		{
			String[] result = new String[0];
			return result;
		}
		availableCars = new String[numberOfAvailableCars];
		int availableCarsIndex = 0;
		// Populate available cars with registration numbers
		for(int i=0; i<cars.length;i++)
		{
			
			if(cars[i] != null)
			{
				if(!cars[i].isCarBookedOnDate(dateRequired))
				{
					availableCars[availableCarsIndex] = availableCarsIndex + 1 + ". " + cars[i].getRegistrationNumber();
					availableCarsIndex++;
				}
			}
		}
		return availableCars;
	}
	
	public String book(String firstName, String lastName, DateTime required, int numPassengers, String registrationNumber)
	{
		Car car = getCarById(registrationNumber);
		if(car != null)
        {
			if(car.book(firstName, lastName, required, numPassengers))
			{

				String message = "Thank you for your booking. \n" + car.getDriverName() 
		        + " will pick you up on " + required.getFormattedDate() + ". \n"
				+ "Your booking reference is: " + car.getBookingID(firstName, lastName, required);
				return message;
			}
			else
			{
				String message = "Booking could not be completed.";
				return message;
			}
        }
        else{
            return "Car with registration number: " + registrationNumber + " was not found.";
        }
	}
	
	public String completeBooking(String firstName, String lastName, DateTime dateOfBooking, double kilometers)
	{
		String result = "";
		
		// Search all cars for bookings on a particular date.
		for(int i = 0; i <cars.length; i++)
		{
			if (cars[i] != null)
			{
				if(cars[i].isCarBookedOnDate(dateOfBooking))
				{
					return cars[i].completeBooking(firstName, lastName, dateOfBooking, kilometers);
				}
			}
		}
		return "Booking not found.";
	}
	
	public String completeBooking(String firstName, String lastName, String registrationNumber, double kilometers)
	{
		String carNotFound = "Car not found";
		Car car = null;
		// Search for car with registration number
		for(int i = 0; i <cars.length; i++)
		{
			if (cars[i] != null)
			{
				if (cars[i].getRegistrationNumber().equals(registrationNumber))
				{
					car = cars[i];
					break;
				}
			}
		}

		if (car == null)
		{
			return carNotFound;
		}
		if (car.getBookingByName(firstName, lastName) != -1)
		{
			return car.completeBooking(firstName, lastName, kilometers);
		}
		return "Error: Booking not found.";
	}
	
	public boolean getBookingByName(String firstName, String lastName, String registrationNumber)
	{
		String bookingNotFound = "Error: Booking not found";
		Car car = null;
		// Search for car with registration number
		for(int i = 0; i <cars.length; i++)
		{
			if (cars[i] != null)
			{
				if (cars[i].getRegistrationNumber().equals(registrationNumber))
				{
					car = cars[i];
					break;
				}
			}
		}
		
		if(car == null)
		{
			return false;
		}
		if(car.getBookingByName(firstName, lastName) == -1)
		{
			return false;
		}
		return true;
	}
	
	public String displaySpecificCar(String regNo)
	{
		for(int i = 0; i < cars.length; i++)
		{
			if(cars[i] != null)
			{
				if(cars[i].getRegistrationNumber().equals(regNo))
				{
					return cars[i].getDetails();
				}
			}
		}
		return "Error: The car could not be located.";
	}
	
	public Car[] getCarsAvailable(DateTime dateRequired, boolean silverService) {
		Car[] carList = new Car[15];
		int carListCurrent = 0;
		for (int i = 0; i < cars.length; i++) {
			if (cars[i] == null) {
				break;
			}
			
			// Check if matches requirement
			boolean isSilverService = cars[i] instanceof SilverServiceCar;
			if (isSilverService != silverService) 
				continue;

			// Check Date
			if (!cars[i].isCarBookedOnDate(dateRequired)) {
				carList[carListCurrent] = cars[i];
				carListCurrent++;
			}
		}
		
		return carList;
	}
	
	public boolean seedData()
	{
		for(int i = 0; i < cars.length; i++)
		{
			if(cars[i] != null)
			{
				return false;
			}
		}
		// 2 cars not booked
		Car honda = new Car("SIM194", "Honda", "Accord Euro", "Henry Cavill", 5);
		cars[itemCount] = honda;
		honda.book("Craig", "Cocker", new DateTime(1), 3);
		itemCount++;
		
		Car lexus = new Car("LEX666", "Lexus", "M1", "Angela Landsbury", 3);
		cars[itemCount] = lexus;
		lexus.book("Craig", "Cocker", new DateTime(1), 3);
		itemCount++;
		
		SilverServiceCar holden = new SilverServiceCar("JJC567", "Commodore", "V8", "Merry Jackline", 4, 8.70,
				new String[] {"Beer","Wine","Chips"} );
		cars[itemCount] = holden;
		itemCount++;
		
		SilverServiceCar ford = new SilverServiceCar("HHR883", "Fiesta", "MZ", "Tommy Holtz", 3, 5.50,
				new String[] {"Coca Cola","Mangoes","Pineapples"} );
		cars[itemCount] = ford;
		itemCount++;
		
		// 2 cars booked each
		Car bmw = new Car("BMW256", "Mini", "Minor", "Barbara Streisand", 4);
		cars[itemCount] = bmw;
		itemCount++;
		bmw.book("Craig", "Cocker", new DateTime(1), 3);
		
		Car audi = new Car("AUD765", "Mazda", "RX7", "Matt Bomer", 6);
		cars[itemCount] = audi;
		itemCount++;
		audi.book("Rodney", "Cocker", new DateTime(1), 4);
		
		SilverServiceCar mazda = new SilverServiceCar("KKH439", "Atenza", "6", "Frank Walker", 4, 9.20,
				new String[] {"Coca Cola","Sprite","Lollies"} );
		cars[itemCount] = mazda;
		itemCount++;
		mazda.book("Daniel", "Atanasovski", new DateTime(2), 3);
		
		SilverServiceCar porsche = new SilverServiceCar("LMR443", "Coupe", "968", "Jeremy Stan", 1, 12.60,
				new String[] {"Wine","Beer","Apples"} );
		cars[itemCount] = porsche;
		itemCount++;
		porsche.book("Keith", "Urban", new DateTime(1), 1);
		
		// 1 car booked five times (not available)
		Car toyota = new Car("TOY765", "Toyota", "Corola", "Tina Turner", 7);
		cars[itemCount] = toyota;
		itemCount++;
		toyota.book("Rodney", "Cocker", new DateTime(1), 3);
		toyota.book("Craig", "Cocker", new DateTime(2), 7);
		toyota.book("Alan", "Smith", new DateTime(3), 3);
		toyota.completeBooking("Alan", "Smith", 24);
		toyota.book("Carmel", "Brownbill", new DateTime(4), 7);
		toyota.book("Paul", "Scarlett", new DateTime(5), 7);
		toyota.completeBooking("Paul", "Scarlett", 45);
		toyota.book("Paul", "Scarlett", new DateTime(6), 7);
		toyota.book("Paul", "Scarlett", new DateTime(7), 7);
		
		
		// 1 car booked five times (not available)
		Car rover = new Car("ROV465", "Honda", "Rover", "Jonathon Ryss Meyers", 7);
		cars[itemCount] = rover;
		itemCount++;
		rover.book("Rodney", "Cocker", new DateTime(1), 3);
		rover.completeBooking("Rodney", "Cocker", 75);
		DateTime inTwoDays = new DateTime(2);
		rover.book("Rodney", "Cocker", inTwoDays, 3);
		rover.completeBooking("Rodney", "Cocker", inTwoDays,75);
		
		SilverServiceCar nissan = new SilverServiceCar("DDR882", "Dayz Roox", "m32", "Michael Flinstone", 5, 12.10,
				new String[] {"Lollies","Cordial","Chips"} );
		cars[itemCount] = nissan;
		itemCount++;
		nissan.book("Jamie", "Walker", new DateTime(2), 4);
		nissan.completeBooking("Jamie", "Walker", 35);
		nissan.book("Terry", "Manning", new DateTime(1), 3);
		nissan.completeBooking("Terry", "Manning", 17);
		nissan.book("Tom", "Cruise", new DateTime(2), 5);
		
		SilverServiceCar volvo = new SilverServiceCar("LST992", "Saloon", "PV51", "Tim Cooper", 4, 15.50,
				new String[] {"Water","Cherries","Ice Cream"} );
		cars[itemCount] = volvo;
		itemCount++;
		volvo.book("Freddy", "Kreuger", new DateTime(3), 4);
		volvo.completeBooking("Freddy", "Kreuger", 35);
		volvo.book("Hammy", "Charles", new DateTime(1), 2);
		volvo.completeBooking("Hammy", "Charles", 19);
		volvo.book("Jamie", "Walker", new DateTime(2), 4);
		volvo.completeBooking("Jamie", "Walker", 25);
		volvo.book("Terry", "Manning", new DateTime(1), 3);
		volvo.completeBooking("Terry", "Manning", 5);
		volvo.book("Tim", "Manning", new DateTime(3), 3);
		volvo.book("Penelope", "Cruz", new DateTime(1), 4);
		
		
		
		return true;
	}

	public String displayAllBookings(boolean silverService, boolean aToZ)
	{
		if(itemCount == 0)
		{
			return "No cars have been added to the system.";
		}
		StringBuilder sb = new StringBuilder();
		sb.append("Summary of all cars: ");
		sb.append("\n");
		 
		// Prepare car list
		Car[] selectedCars = new Car[15];
		int selectedCarsAmount = 0;
		for (int i = 0; i < itemCount; i++)
		{
			// Type Check
			boolean isSilverService = cars[i] instanceof SilverServiceCar;
			if (isSilverService != silverService) 
				continue;
			
			selectedCars[selectedCarsAmount] = cars[i];
			selectedCarsAmount++;
		}
		
		// Check if there is any cars
		if (selectedCarsAmount == 0)
			return null;
		
		// Bubble Sort alphabetically
		if (aToZ) {
			for(int i = 0; i < selectedCarsAmount; i++) {
				for(int j = 1; j < (selectedCarsAmount-i); j++) {
					String carCheckReg = selectedCars[j-1].getRegistrationNumber().substring(0,3);
		        	String secondCarCheckReg = selectedCars[j].getRegistrationNumber().substring(0,3);
		        	
		        	// First Letter
		            if(carCheckReg.charAt(0) > secondCarCheckReg.charAt(0)) {
		            	Car temp = selectedCars[j-1];
		            	selectedCars[j-1] = selectedCars[j];
		            	selectedCars[j] = temp;
		            } else if (carCheckReg.charAt(0) == secondCarCheckReg.charAt(0)) {
		            	// Second Letter
		            	if(carCheckReg.charAt(1) > secondCarCheckReg.charAt(1)) {
		            		Car temp = selectedCars[j-1];
			            	selectedCars[j-1] = selectedCars[j];
			            	selectedCars[j] = temp;
		            	} else if (carCheckReg.charAt(1) == secondCarCheckReg.charAt(1)) {
		            		// Third Letter
		            		if (carCheckReg.charAt(2) > secondCarCheckReg.charAt(2)) {
		            			Car temp = selectedCars[j-1];
				            	selectedCars[j-1] = selectedCars[j];
				            	selectedCars[j] = temp;
		            		}
		            	}
		            }
		         }
		      }
		} else {
			for(int i = 0; i < selectedCarsAmount; i++) {
				for(int j = 1; j < (selectedCarsAmount-i); j++) {
					String carCheckReg = selectedCars[j-1].getRegistrationNumber().substring(0,3);
		        	String secondCarCheckReg = selectedCars[j].getRegistrationNumber().substring(0,3);
		        	
		        	// First Letter
		            if(carCheckReg.charAt(0) < secondCarCheckReg.charAt(0)) {
		            	Car temp = selectedCars[j-1];
		            	selectedCars[j-1] = selectedCars[j];
		            	selectedCars[j] = temp;
		            } else if (carCheckReg.charAt(0) == secondCarCheckReg.charAt(0)) {
		            	// Second Letter
		            	if(carCheckReg.charAt(1) < secondCarCheckReg.charAt(1)) {
		            		Car temp = selectedCars[j-1];
			            	selectedCars[j-1] = selectedCars[j];
			            	selectedCars[j] = temp;
		            	} else if (carCheckReg.charAt(1) == secondCarCheckReg.charAt(1)) {
		            		// Third Letter
		            		if (carCheckReg.charAt(2) < secondCarCheckReg.charAt(2)) {
		            			Car temp = selectedCars[j-1];
				            	selectedCars[j-1] = selectedCars[j];
				            	selectedCars[j] = temp;
		            		}
		            	}
		            }
		         }
		      }
		}
		
		// Append to string builder
		for (Car car : selectedCars) {
			if (car == null) 
				continue;
			sb.append(car.getDetails());
		}
		
		return sb.toString();
	}

	public String displayBooking(String id, String seatId)
	{
		Car booking = getCarById(id);
		if(booking == null)
		{
			return "Booking not found";
		}
		return booking.getDetails();
	}
	
	public String isValidId(String id)
	{
		return MiRidesUtilities.isRegNoValid(id);
	}
	
	public String isValidPassengerCapacity(int passengerNumber)
	{
		return MiRidesUtilities.isPassengerCapacityValid(passengerNumber);
	}

	public boolean checkIfCarExists(String regNo)
	{
		Car car = null;
		if (regNo.length() != 6)
		{
			return false;
		}
		car = getCarById(regNo);
		if (car == null)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	
	private Car getCarById(String regNo)
	{
		Car car = null;

		for (int i = 0; i < cars.length; i++)
		{
			if(cars[i] != null)
			{
				if (cars[i].getRegistrationNumber().equals(regNo))
				{
					car = cars[i];
					return car;
				}
			}
		}
		return car;
	}
}
