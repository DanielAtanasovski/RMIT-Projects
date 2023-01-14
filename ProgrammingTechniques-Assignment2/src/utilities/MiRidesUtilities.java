package utilities;

import exceptions.InvalidId;

public class MiRidesUtilities 
{
	private final static int ID_LENGTH = 6;
	
	public static String isRegNoValid(String regNo) throws InvalidId
	{
		int regNoLength = regNo.length();
		if(regNoLength != ID_LENGTH)
		{
			throw new InvalidId("Error - Registration is not six characters.");
		}
		boolean letters = regNo.substring(0,3).matches("[a-zA-Z]+");
		if (!letters) {
			throw new InvalidId("Error - Registration does not begin with three letters.");	
		}
		boolean numbers = regNo.substring(3).matches("[0-9]+");
		if (!numbers) {
			throw new InvalidId("Error - Registration does not end with three numerals.");
		}
		return regNo;
	}

	public static String isPassengerCapacityValid(int passengerCapacity)
	{
		if(passengerCapacity > 0 && passengerCapacity < 10)
		{
			return "OK";
		}
		else
		{
			return "Error: Passenger capacity must be between 1 and 9.";
		}
	}
}
