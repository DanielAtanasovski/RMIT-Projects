package model;

import java.util.Objects;
import java.util.Random;

import model.interfaces.DicePair;
import model.interfaces.Die;

public class DicePairImpl implements DicePair{
	
	private Die die1;
	private Die die2;
	
	public DicePairImpl()  {
		Random random = new Random();
		die1 = new DieImpl(1, random.nextInt(Die.NUM_FACES) + 1, Die.NUM_FACES);
		die2 = new DieImpl(2, random.nextInt(Die.NUM_FACES) + 1, Die.NUM_FACES);
	}

	// Allowing a two argument constructor so that we may have the correct
	// dice rolls because of the limitation imposed by argument of PlayerResult() requiring a
	// dice pair, making it impossible to generate individual random values with current
	// constructor.
	// Suggested (and allowed) by casper on discussion forums
	// https://rmit.instructure.com/courses/67438/discussion_topics/642302
	public DicePairImpl(Die die1, Die die2) {
		this.die1 = die1;
		this.die2 = die2;
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
		return Integer.compare(this.getTotal(), dicePair.getTotal());
	}

}
