package tests;

import model.DicePairImpl;
import model.SimplePlayer;
import model.interfaces.DicePair;
import model.interfaces.Player;
import tests.interfaces.Test;

import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * Performs a series of tests centred around the SimplePlayer Class
 * @author Daniel Atanasovski
 */
public class PlayerTest implements Test {

    private static final Logger logger = Logger.getLogger(Test.class.getName());

    @Override
    public boolean StartTest() {
        boolean pass = true;

        logger.setLevel(Level.FINE);
        logger.log(Level.INFO, "## PlayerTest has BEGUN ## ");

        // Tests
        pass = settersTest();

        if (pass)
            logger.log(Level.INFO, "## PlayerTest has PASSED ##");
        else
            logger.log(Level.INFO, "## PlayerTest has FAILED ##");

        return pass;
    }

    private boolean settersTest() {
        Player player = new SimplePlayer("1", "test", 0);

        // Attributes
        String newName = "Test2";
        int newPoints = 1000;
        int underBet = 500;
        int overBet = 1200;

        // Name \\
        player.setPlayerName(newName);
        if (!player.getPlayerName().equals(newName)) {
            logger.log(Level.FINE, "setPlayerName Failed");
            return false;
        }
        // Points \\
        player.setPoints(newPoints);
        if (player.getPoints() != newPoints) {
            logger.log(Level.FINE, "setPoints Failed");
            return false;
        }
        // Betting \\
        // under Bet
        if (!player.setBet(underBet) || player.getPoints() != newPoints) {
            logger.log(Level.FINE, "setBet for betting under current points Failed");
            return false;
        }
        // over bet
        if (player.setBet(overBet) || player.getPoints() != newPoints) {
            logger.log(Level.FINE, "setBet for betting over current points Failed");
            return false;
        }
        // exact bet
        if (!player.setBet(newPoints) || player.getPoints() != newPoints) {
            logger.log(Level.FINE, "setBet for betting the exact same as current points Failed");
            return false;
        }
        // Dice \\
        DicePair dice = new DicePairImpl();
        player.setResult(dice);
        if (player.getResult().compareTo(dice) != 0){
            logger.log(Level.FINE, "setResult Failed");
            return false;
        }
        // Reset \\
        player.resetBet();
        if (player.getBet() != 0 || player.getPoints() != newPoints){
            logger.log(Level.FINE, "resetBet Failed");
            return false;
        }

        return true;
    }

}
