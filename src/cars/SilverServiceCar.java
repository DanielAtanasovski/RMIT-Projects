package cars;

import utilities.DateTime;
import utilities.DateUtilities;

public class SilverServiceCar extends Car{

	private double bookingFee;
	private String[] refreshments;
	
	// Constants
	private final double MINIMUM_BOOKING_FEE = 3;
	
	public SilverServiceCar(String regNo, String make, String model,
			String driverName, int passengerCapacity,
			double bookingFee, String[] refreshments) {
		
		// Call Car Constructor
		super(regNo, make, model, driverName, passengerCapacity);
		
		// Check Booking Fee
		if (bookingFee < MINIMUM_BOOKING_FEE) {
			bookingFee = MINIMUM_BOOKING_FEE;
		}
		this.bookingFee = bookingFee;
		this.refreshments = refreshments;
	}
	
	@Override
	public boolean book(String firstName, String lastName, DateTime required, int numPassengers) {
		
		// Check base car requirements.
		boolean success = super.book(firstName, lastName, required, numPassengers);	
		if (!success) {
			return false;
		}
		
		// Silver Service specific requirements
		success = dateIsValid(required);
		if (success) {
			super.createBooking(firstName, lastName, required, numPassengers);
		}
		
		return success;
	}
	
	
	@Override
	protected boolean dateIsValid(DateTime date)
	{
		return DateUtilities.dateIsNotInPast(date) && DateUtilities.dateIsNotMoreThan3Days(date);
	}
	
	/*
	 * Calculates and Returns the car's fee
	 */
	public double calculateFee(double km) {
		double tripFee = km * (0.4 * bookingFee); 
		return tripFee;
	}

}
