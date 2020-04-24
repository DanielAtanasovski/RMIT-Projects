package model;

import java.util.ArrayList;
import java.util.Collection;

import model.interfaces.DicePair;
import model.interfaces.Die;
import model.interfaces.GameEngine;
import model.interfaces.Player;
import view.interfaces.GameEngineCallback;

public class GameEngineImpl implements GameEngine {
	
	private ArrayList<Player> playerList = new ArrayList<Player>();
	private ArrayList<GameEngineCallback> gameEngineCallbackList = new ArrayList<GameEngineCallback>();

	@Override
	public void rollPlayer(Player player, int initialDelay1, int finalDelay1, int delayIncrement1, int initialDelay2,
			int finalDelay2, int delayIncrement2) {

		// Roll dice
		DicePair playerDice = null;
		try {
			playerDice = roll(initialDelay1, finalDelay1, delayIncrement1, initialDelay2,
					finalDelay2, delayIncrement2, player);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}

		// Send updates
		player.setResult(playerDice);
		playerResult(player, playerDice);
	}

	private void playerUpdate(Player player, Die die) {
		for (GameEngineCallback g: gameEngineCallbackList) {
			g.playerDieUpdate(player, die, this);
		}
	}

	private void playerResult(Player player, DicePair dice) {
		for (GameEngineCallback g : gameEngineCallbackList){
			g.playerResult(player, dice,this);
		}
	}

	private DicePair roll(int initialDelay1, int finalDelay1, int delayIncrement1, int initialDelay2, int finalDelay2,
						  int delayIncrement2, Player player) throws InterruptedException {
		// Dice
		Die die1 = new DicePairImpl().getDie1();
		Die die2 = new DicePairImpl().getDie2();

		// Delays
		int currentDelay1 = initialDelay1;
//		int currentDelay2 = initialDelay2;

		// Roll the dice
		boolean doneRolling = false;
		while (!doneRolling) {
			doneRolling = true;

			// Update first die
			if (currentDelay1 < finalDelay1){
				// Update value
				die1 = dieUpdate(die1);
				// Increase Delay
				Thread.sleep(delayIncrement1);
				currentDelay1 += delayIncrement1;
				// Callback
				if (player != null) {
					playerUpdate(player, die1);
					playerUpdate(player, die2);
				}
				else {
					houseUpdate(die1);
					houseUpdate(die2);
				}
				// Ensure another loop
				doneRolling = false;
			}

			// Update second die separately
			// TODO: Threading to support simultaneous dice rolls (Assignment 2)
//			if (currentDelay2 < finalDelay2){
//				// Update value
//				die2 = dieUpdate(die2);
//				// Increase Delay
//				currentDelay2 += delayIncrement2;
//				// Callback
//				if (player != null)
//					playerUpdate(player, die2);
//				else
//					houseUpdate(die2);
//				// Ensure another loop
//				doneRolling = false;
//			}
		}

		// Return a new dice pair with rolled dice
		return new DicePairImpl(die1, die2);
	}

	@Override
	public void rollHouse(int initialDelay1, int finalDelay1, int delayIncrement1, int initialDelay2, int finalDelay2,
			int delayIncrement2) {

		// Roll dice
		DicePair houseDice = null;
		try {
			houseDice = roll(initialDelay1, finalDelay1, delayIncrement1, initialDelay2,
					finalDelay2, delayIncrement2, null);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}

		// Updates
		updateHousePlayers(houseDice);
		houseResult(houseDice);
		resetPlayers();
	}

	private void houseUpdate(Die die) {
		for (GameEngineCallback g: gameEngineCallbackList) {
			g.houseDieUpdate(die, this);
		}
	}

	private void houseResult(DicePair dicePair) {
		for (GameEngineCallback gameEngineCallback: gameEngineCallbackList) {
			gameEngineCallback.houseResult(dicePair, this);
		}
	}

	private void updateHousePlayers(DicePair houseResult) {
		for (Player player : playerList){
			applyWinLoss(player, houseResult);
		}
	}

	private void resetPlayers() {
		for (Player player: playerList) {
			player.resetBet();
		}
	}

	private Die dieUpdate(Die die) {
		Die newDie;
		if (die.getNumber() == 1)
			newDie = new DicePairImpl().getDie1();
		else
			newDie = new DicePairImpl().getDie2();
		return newDie;
	}

	@Override
	public void applyWinLoss(Player player, DicePair houseResult) {
		switch (player.getResult().compareTo(houseResult)) {
			case -1:
				// Loss
				player.setPoints(player.getPoints() - player.getBet());
				break;
			case 0:
				// Draw
				player.setPoints(player.getPoints());
				break;
			case 1:
				// Win
				player.setPoints(player.getPoints() + (player.getBet()));
				break;
		}
	}

	@Override
	public void addPlayer(Player player) {
		// Check if player exists in the list
		for (Player p : playerList) {
			if (p.getPlayerId().equals(player.getPlayerId())){
				// Found the duplicate, replace it
				int i = playerList.indexOf(p);
				playerList.set(i, player);
				return;
			}
		}
		// Assuming no duplicate
		playerList.add(player);
	}

	@Override
	public Player getPlayer(String id) {
		for (Player player : playerList) {
			if (player.getPlayerId().equals(id)) {
				return player;
			}
		}
		return null;
	}

	@Override
	public boolean removePlayer(Player player) {
		for (Player p : playerList) {
			if (p.getPlayerId().equals(player.getPlayerId())) {
				playerList.remove(p);
				return true;
			}
		}
		return false;
	}

	@Override
	public boolean placeBet(Player player, int bet) {
		return player.setBet(bet);
	}

	@Override
	public void addGameEngineCallback(GameEngineCallback gameEngineCallback) {
		gameEngineCallbackList.add(gameEngineCallback);		
	}

	@Override
	public boolean removeGameEngineCallback(GameEngineCallback gameEngineCallback) {
		for (GameEngineCallback callback : gameEngineCallbackList) {
			if (callback == gameEngineCallback) {
				gameEngineCallbackList.remove(gameEngineCallback);
				return true;
			}
		}
		return false;
	}

	@Override
	public Collection<Player> getAllPlayers() {
		return playerList;
	}

}
