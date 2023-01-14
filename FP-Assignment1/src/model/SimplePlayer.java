package model;

import model.interfaces.DicePair;
import model.interfaces.Player;

public class SimplePlayer implements Player {
	private String playerID;
	private String playerName;
	private int points;
	private int bet;
	private DicePair diceResult;

	public SimplePlayer(String playerID, String playerName, int initialPoints) {
		this.playerID = playerID;
		this.playerName = playerName;
		this.points = initialPoints;
	}
	
	@Override
	public String getPlayerName() {
		return this.playerName;
	}

	@Override
	public void setPlayerName(String playerName) {
		this.playerName = playerName;
	}

	@Override
	public int getPoints() {
		return this.points;
	}

	@Override
	public void setPoints(int points) {
		this.points = points;
	}

	@Override
	public String getPlayerId() {
		return this.playerID;
	}

	@Override
	public boolean setBet(int bet) {
		if (bet > 0 && points >= bet){
			this.bet = bet;
			return true;
		}
		return false;
	}

	@Override
	public int getBet() {
		return bet;
	}

	@Override
	public void resetBet() {
		this.bet = 0;
	}

	@Override
	public DicePair getResult() { return diceResult; }

	@Override
	public void setResult(DicePair rollResult) { diceResult = rollResult; }

	@Override
	public String toString() {
		// e.g. "Player: id=1, name=The Roller, bet=100, points=4900, RESULT .. Dice 1: One,  Dice 2: Three .. Total: 4"
		return String.format("Player: id=%s, name=%s, bet=%d, points=%d, RESULT .. Dice 1: %s, Dice 2: %s .. Total: %d",
				playerID, playerName, bet, points, diceResult.getDie1().getValue(), diceResult.getDie2().getValue(),
				diceResult.getTotal());
	}
}
