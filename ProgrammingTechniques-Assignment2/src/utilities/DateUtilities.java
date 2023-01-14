package utilities;

import exceptions.InvalidDate;

public class DateUtilities {

	public static boolean dateIsNotInPast(DateTime date) throws InvalidDate
	{
		final int OFFSET_FOR_DAYS_IN_MILLISECONDS = 1;
		boolean notInPast = false;
		
		DateTime today = new DateTime();
		
		int daysInPast = DateTime.diffDays(date, today) + OFFSET_FOR_DAYS_IN_MILLISECONDS;
		if(daysInPast >=0)
		{
			notInPast = true;
		} else {
			throw new InvalidDate("Error - Date is in the past.");
		}
		
		return notInPast;
	}
	
	public static boolean datesAreTheSame(DateTime date1, DateTime date2)
	{
		if(date1.getEightDigitDate().equals(date2.getEightDigitDate()))
		{
			return true;
		}
		return false;
	}
	
	public static boolean dateIsNotMoreThan7Days(DateTime date) throws InvalidDate
	{
		boolean within7Days = false;
		DateTime today = new DateTime();
		DateTime nextWeek = new DateTime(7);
		
		int daysInFuture = DateTime.diffDays(nextWeek, date);
		if(daysInFuture >0 && daysInFuture <8)
		{
			within7Days = true;
		} else {
			throw new InvalidDate("Error - Date is more than 7 days in advance.");
		}
		return within7Days;
	}
	
	public static boolean dateIsNotMoreThan3Days(DateTime date) throws InvalidDate
	{
		boolean within3Days = false;
		DateTime today = new DateTime();
		DateTime next3Days = new DateTime(3);
		
		int daysInFuture = DateTime.diffDays(next3Days, date);
		if(daysInFuture > 0 && daysInFuture < 4)
		{
			within3Days = true;
		} else {
			throw new InvalidDate("Error - Date is more than 3 days in advance.");
		}
		return within3Days;
	}
}
