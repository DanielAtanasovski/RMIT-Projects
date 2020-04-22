package view;

import java.util.logging.Level;
import java.util.logging.Logger;

import model.interfaces.DicePair;
import model.interfaces.Die;
import model.interfaces.GameEngine;
import model.interfaces.Player;
import view.interfaces.GameEngineCallback;

/**
 * 
 * Skeleton example implementation of GameEngineCallback showing Java logging behaviour
 * 
 * @author Caspar Ryan
 * @see view.interfaces.GameEngineCallback
 * 
 */
public class GameEngineCallbackImpl implements GameEngineCallback
{
	private static final Logger logger = Logger.getLogger(GameEngineCallback.class.getName());

	public GameEngineCallbackImpl()
	{
		// FINE shows rolling output, INFO only shows result
		logger.setLevel(Level.FINE);
	}

	@Override
	public void playerDieUpdate(Player player, Die die, GameEngine gameEngine)
	{
		// intermediate results logged at Level.FINE
		String resultString = String.format("%s die %s rolled to %s", player.getPlayerName(),
				die.getNumber(), die.toString());
		logger.log(Level.FINE, resultString);
	}

	@Override
	public void playerResult(Player player, DicePair result, GameEngine gameEngine)
	{
		// final results logged at Level.INFO
		String resultString = String.format("%s *RESULT*: Dice 1: %s, Dice 2: %s .. rolled to %d",
				player.getPlayerName(), result.getDie1().toString(), result.getDie2().toString(), result.getTotal());
		logger.log(Level.INFO, resultString);
	}

	@Override
	public void houseDieUpdate(Die die, GameEngine gameEngine) {
		String resultString = String.format("House die %d rolled to %s", die.getNumber(), die.toString());
		logger.log(Level.FINE, resultString);
	}

	@Override
	public void houseResult(DicePair result, GameEngine gameEngine) {
		String resultString = String.format("HOUSE *RESULT*: Dice 1: %s, Dice 2: %s .. Total: %d ", result.getDie1().toString(),  result.getDie2().toString(), result.getTotal());
		logger.log(Level.INFO, resultString);

		// Show Final Player Results
		String playerResultString = "FINAL PLAYER RESULTS \n";
		for (Player player : gameEngine.getAllPlayers()) {
			playerResultString += player.toString() + "\n";
		}
		logger.log(Level.INFO, playerResultString);
	}
}
