package model;

import java.util.Objects;

import model.interfaces.Die;

public class DieImpl implements Die {

	private int number;
	private int value;
	private int numFaces;

	public DieImpl(int number, int value, int numFaces) throws IllegalArgumentException {
		this.number = number;
		this.value = value;
		this.numFaces = numFaces;
	}

	@Override
	public int getNumber() {
		return this.number;
	}

	@Override
	public int getValue() {
		return this.value;
	}

	@Override
	public int getNumFaces() {
		return this.numFaces;
	}

	@Override
	public boolean equals(Die die) {
		return this.numFaces == die.getNumFaces()
				&& this.value == die.getValue();
	}

	@Override
	public boolean equals(Object die) {
		if (!(die instanceof Die))
			return false;

		return equals((Die)die);
	}

	@Override
	public int hashCode() {
		return Objects.hash(number, value, numFaces);
	}

	@Override
	public String toString() {
		String retString;
		switch (this.value) {
			case 1:
				retString = "One";
				break;
			case 2:
				retString = "Two";
				break;
			case 3:
				retString = "Three";
				break;
			case 4:
				retString = "Four";
				break;
			case 5:
				retString = "Five";
				break;
			case 6:
				retString = "Six";
				break;
			case 7:
				retString = "Seven";
				break;
			case 8:
				retString = "Eight";
				break;
			case 9:
				retString = "Nine";
				break;
			default:
				retString = "> Nine";
				
		}
		
		return retString;
	}

}
