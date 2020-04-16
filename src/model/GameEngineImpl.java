package model;

import java.util.ArrayList;
import java.util.Collection;

import model.interfaces.DicePair;
import model.interfaces.GameEngine;
import model.interfaces.Player;
import view.interfaces.GameEngineCallback;

public class GameEngineImpl implements GameEngine {
	
	private ArrayList<Player> playerList = new ArrayList<Player>();
	private ArrayList<GameEngineCallback> gameEngineCallbackList = new ArrayList<GameEngineCallback>();

	@Override
	public void rollPlayer(Player player, int initialDelay1, int finalDelay1, int delayIncrement1, int initialDelay2,
			int finalDelay2, int delayIncrement2) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void rollHouse(int initialDelay1, int finalDelay1, int delayIncrement1, int initialDelay2, int finalDelay2,
			int delayIncrement2) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void applyWinLoss(Player player, DicePair houseResult) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void addPlayer(Player player) {
		// TODO Check if player is in list already?
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
