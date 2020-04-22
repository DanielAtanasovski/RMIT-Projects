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
		DicePair playerDice = roll(initialDelay1, finalDelay1, delayIncrement1, initialDelay2,
				finalDelay2, delayIncrement2, player);

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
						  int delayIncrement2, Player player) {
		// Dice
		Die die1 = new DicePairImpl().getDie1();
		Die die2 = new DicePairImpl().getDie2();

		// Delays
		int currentDelay1 = initialDelay1;
		int currentDelay2 = initialDelay2;

		// Roll the dice
		boolean doneRolling = false;
		while (!doneRolling) {
			doneRolling = true;

			// Update first die
			if (currentDelay1 < finalDelay1){
				// Update value
				die1 = dieUpdate(die1);
				// Increase Delay
				currentDelay1 += delayIncrement1;
				// Callback
				if (player != null)
					playerUpdate(player, die1);
				else
					houseUpdate(die1);
				// Ensure another loop
				doneRolling = false;
			}

			// Update second die
			if (currentDelay2 < finalDelay2){
				// Update value
				die2 = dieUpdate(die2);
				// Increase Delay
				currentDelay2 += delayIncrement2;
				// Callback
				if (player != null)
					playerUpdate(player, die2);
				else
					houseUpdate(die2);
				// Ensure another loop
				doneRolling = false;
			}
		}

		// Return a new dice pair with rolled dice
		return new DicePairImpl(die1, die2);
	}

	@Override
	public void rollHouse(int initialDelay1, int finalDelay1, int delayIncrement1, int initialDelay2, int finalDelay2,
			int delayIncrement2) {

		// Roll dice
		DicePair houseDice = roll(initialDelay1, finalDelay1, delayIncrement1, initialDelay2,
				finalDelay2, delayIncrement2, null);

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
			die = new DicePairImpl().getDie1();
		else
			die = new DicePairImpl().getDie2();
		return die;
	}

	@Override
	public void applyWinLoss(Player player, DicePair houseResult) {
		if (player.getResult().getTotal() > houseResult.getTotal()){
			// Win
			// (Assuming points bet is doubled and added back to points, otherwise there is no way to get points!)
			player.setPoints(player.getPoints() + (player.getBet()));
		} else if (player.getResult().getTotal() < houseResult.getTotal()) {
			// Loss
			player.setPoints(player.getPoints() - player.getBet());
		} else {
			// Draw
			player.setPoints(player.getPoints());
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
			if (player.getPlayerId() == id) {
				return player;
			}
		}
		return null;
	}

	@Override
	public boolean removePlayer(Player player) {
		for (Player p : playerList) {
			if (p.getPlayerId() == player.getPlayerId()) {
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
