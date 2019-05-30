package cars;

import utilities.DateTime;
import utilities.DateUtilities;

public class SilverServiceCar extends Car{

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
		boolean success;
		
		// Silver Service specific requirements
		success = dateIsValid(required);
		if (success) {
			super.book(firstName, lastName, required, numPassengers);
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
			sb.append(String.format("%-15s %s\n", "Item " + (i+1), refreshments[i]));
		}
		
		sb.append(super.getDetailsBookings());
		return sb.toString();
	}
	@Override
	protected String getDetailsBookings() {
		return "";
	}
	
	@Override
	public String toString() {
		String superString = super.toString();
		StringBuilder sb = new StringBuilder();
		sb.append(superString);
		// Refreshments
		for(int i = 0; i < refreshmentsCount; i++) {
			sb.append("Item " + (i+1) + " " + refreshments[i]);
		}
		
		// FIXME: THIS MIGHT NOT WORK AS WE OVERRIDE IT BELOW
		sb.append(super.toStringBookings());
		
		return sb.toString();
	}
	
	/*
	 * This override method prevents the super class from adding 
	 * the bookings before we need them.
	 */
	@Override
	protected String toStringBookings() {
		return "";
	}

}
