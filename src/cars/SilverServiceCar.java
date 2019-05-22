package cars;

import utilities.DateTime;

public class SilverServiceCar extends Car{

	private double bookingFee;
	
	public SilverServiceCar(String regNo, String make, String model,
			String driverName, int passengerCapacity,
			double bookingFee, String[] refreshments) {
		
		// Call Car Constructor
		super(regNo, make, model, driverName, passengerCapacity);
		
		// Check Booking Fee
		if (bookingFee < 3) {
			bookingFee = 3;
		}
		this.bookingFee = bookingFee;
	}
	
	@Override
	public boolean book(String firstName, String lastName, DateTime required, int numPassengers) {
		super.book(firstName, lastName, required, numPassengers);
		
		return false;
		
	}
	
	@Override
	private boolean notCurrentlyBookedOnDate(DateTime date) {
		return false;
		
	}
	
	/*
	 * Calculates and Returns the car's fee
	 */
	private double calculateFee() {
		return 0;
	}

}
