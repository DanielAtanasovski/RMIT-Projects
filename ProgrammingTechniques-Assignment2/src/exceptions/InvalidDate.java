package exceptions;

public class InvalidDate extends Exception {
	public InvalidDate() {
		super();
	}
	
	public InvalidDate(String message) {
		super(message);
	}
}
