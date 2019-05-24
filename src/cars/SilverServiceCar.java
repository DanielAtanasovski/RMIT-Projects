package cars;

import utilities.DateTime;
import utilities.DateUtilities;

public class SilverServiceCar extends Car{

	private double bookingFee;
	private String[] refreshments;
	private int refreshmentsCount = 0;
	
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
		this.refreshmentsCount = refreshments.length;
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
	
	@Override
	public String getDetails() {
		String base = super.getDetails();
		
		StringBuilder sb = new StringBuilder();
		sb.append(base);
		// Refreshments
		sb.append(String.format("%s\n", "Refreshments Available"));
		for(int i = 0; i < refreshmentsCount; i++) {
			sb.append(String.format("%s %-15s\n", "Item " + (i+1), refreshments[i]));
		}
		
		// Bookings
		sb.append(String.format("%s\n", "Current Bookings"));
		for(int i = 0; i < currentBookings.length; i++) {
			sb.append(String.format("%-15s\n", "______________________________"));
			sb.append(currentBookings[i].getDetails());
		}
		
		
		// Past Bookings
		sb.append(String.format("%s\n", "Past Bookings"));
		for(int i = 0; i < pastBookings.length; i++) {
			sb.append(String.format("%-15s\n", "______________________________"));
			sb.append(pastBookings[i].getDetails());
		}
		return sb.toString();
	}

}
