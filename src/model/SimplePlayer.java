package model;

import model.interfaces.DicePair;
import model.interfaces.Player;

public class SimplePlayer implements Player {
	private String playerID;
	private String playerName;
	private int points;

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
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public int getBet() {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public void resetBet() {
		// TODO Auto-generated method stub
		
	}

	@Override
	public DicePair getResult() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public void setResult(DicePair rollResult) {
		// TODO Auto-generated method stub
		
	}

}
