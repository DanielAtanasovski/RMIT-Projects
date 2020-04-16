package model;

import java.util.Objects;

import model.interfaces.DicePair;
import model.interfaces.Die;

public class DicePairImpl implements DicePair{
	
	private Die die1;
	private Die die2;
	
	public DicePairImpl()  {
		// TODO: Random
	}

	public DicePairImpl(int value, int numFaces) throws IllegalArgumentException {
		die1 = new DieImpl(1, 2, Die.NUM_FACES);
		die2 = new DieImpl(2, 5, Die.NUM_FACES);
	}
	
	@Override
	public Die getDie1() {
		return this.die1;
	}

	@Override
	public Die getDie2() {
		return this.die2;
	}

	@Override
	public int getTotal() {
		return this.die1.getValue() + this.die2.getValue();
	}
	
	@Override
	public boolean equals(Object dicePair) {
		if (!(dicePair instanceof DicePair))
			return false;
		return equals((DicePair) dicePair);
	}

	@Override
	public boolean equals(DicePair dicePair) {
		return die1.equals(dicePair.getDie1())
				&& die2.equals(dicePair.getDie2());
	}
	
	@Override
	public int hashCode() {
		return Objects.hash(die1, die2);
	}
	
	@Override
	public String toString() {
		String retString = "Dice 1: " + die1.toString() + ", ";
		retString += "Dice 2: " + die2.toString() + " .. ";
		retString += "Total: " + this.getTotal();
		
		return retString;
	}

	@Override
	public int compareTo(DicePair dicePair) {
		int ourTotal = this.getTotal();
		
		if (ourTotal < dicePair.getTotal())
			return -1;
		
		if (ourTotal > dicePair.getTotal())
			return 1;
		
		return 0;
	}

}
