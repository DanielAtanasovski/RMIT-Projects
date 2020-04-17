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

	// Win Multiplier (So the player gets a return on winning, otherwise no point to game)
	private final int winMultiplier = 2;

	@Override
	public void rollPlayer(Player player, int initialDelay1, int finalDelay1, int delayIncrement1, int initialDelay2,
			int finalDelay2, int delayIncrement2) {
		// Delays
		boolean doneRolling = false;
		int currentDelay1 = initialDelay1;
		int currentDelay2 = initialDelay2;

		// Initialise Die
		Die die1 = new DicePairImpl().getDie1();
		Die die2 = new DicePairImpl().getDie1();

		// Rolling
		while (!doneRolling) {
			doneRolling = true;

			// Update first die
			if (currentDelay1 < finalDelay1){
				die1 = dieUpdate();
				currentDelay1 += delayIncrement1;
				playerUpdate(player, die1);
				doneRolling = false;
			}

			// Update second die
			if (currentDelay2 < finalDelay1){
				die2 = dieUpdate();
				currentDelay2 += delayIncrement2;
				playerUpdate(player,die2);
				doneRolling = false;
			}
		}

		// Completed Rolls for this player, send updates
		DicePair playerDice = new DicePairImpl(die1, die2);
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

	@Override
	public void rollHouse(int initialDelay1, int finalDelay1, int delayIncrement1, int initialDelay2, int finalDelay2,
			int delayIncrement2) {
		// Delays
		boolean doneRolling = false;
		int currentDelay1 = initialDelay1;
		int currentDelay2 = initialDelay2;

		// Initialise Die
		Die die1 = new DicePairImpl().getDie1();
		Die die2 = new DicePairImpl().getDie1();

		// Rolling
		while (!doneRolling) {
			doneRolling = true;

			// Update first die
			if (currentDelay1 < finalDelay1){
				die1 = dieUpdate();
				currentDelay1 += delayIncrement1;
				houseUpdate(die1);
				doneRolling = false;
			}

			// Update second die
			if (currentDelay2 < finalDelay1){
				die2 = dieUpdate();
				currentDelay2 += delayIncrement2;
				houseUpdate(die2);
				doneRolling = false;
			}
		}
		// Completed Rolls for house, send updates
		DicePair houseDice = new DicePairImpl(die1, die2);
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

	private Die dieUpdate() {
		Die die = new DicePairImpl().getDie1();
		return die;
	}

	@Override
	public void applyWinLoss(Player player, DicePair houseResult) {
		if (player.getResult().getTotal() > houseResult.getTotal()){
			// Win
			// (Assuming points bet is doubled and added back to points, otherwise there is no way to get points!)
			player.setPoints(player.getPoints() + (player.getBet() * winMultiplier));
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
		// TODO Auto-generated method stub
		return false;
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
