package tests;

import model.GameEngineImpl;
import model.SimplePlayer;
import model.interfaces.GameEngine;
import model.interfaces.Player;
import tests.interfaces.Test;

import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * Performs a series of tests centred around the GameEngine class
 * @author Daniel Atanasovski
 */
public class GameEngineTest implements Test {

    private static final Logger logger = Logger.getLogger(Test.class.getName());

    @Override
    public boolean StartTest() {
        boolean pass = true;

        logger.setLevel(Level.FINE);
        logger.log(Level.INFO, "## GameEngineTest has BEGUN ## ");

        // Tests
        pass = (playerTest() && rollTest());

        if (pass)
            logger.log(Level.INFO, "## GameEngineTest has PASSED ##");
        else
            logger.log(Level.INFO, "## GameEngineTest has FAILED ##");

        return pass;
    }

    private boolean playerTest () {
        GameEngine g = new GameEngineImpl();
        Player p = new SimplePlayer("1", "Test", 500);
        // Add Player
        g.addPlayer(p);
        if (g.getPlayer(p.getPlayerId()) != p){
            logger.log(Level.FINE, "addPlayer Failed");
            return false;
        }
        // Get All Players
        if (!g.getAllPlayers().contains(p)){
            logger.log(Level.FINE, "getAllPlayers Failed");
            return false;
        }

        // Remove Player
        g.removePlayer(p);
        if (g.getPlayer(p.getPlayerId()) != null) {
            logger.log(Level.FINE, "removePlayer Failed");
            return false;
        }

        return true;
    }

    private boolean rollTest () {
        // Roll Player
        // Setup
        GameEngine g = new GameEngineImpl();
        Player p = new SimplePlayer("1", "Test", 1000);
        g.addPlayer(p);
        // Setup bet
        p.setBet(200);
        // Roll
        g.rollPlayer(p, 100, 200, 100,
                50, 200, 50);
        if (p.getPoints() != 1000 || p.getBet() != 200 || p.getResult() == null) {
            logger.log(Level.FINE, "rollPlayer Failed");
            return false;
        }

        // Roll House
        g.rollHouse(10, 200, 10,
                30, 300, 30);
        if (p.getBet() != 0) {
            logger.log(Level.FINE, "resetBet Failed");
            return false;
        }
        return true;
    }
}
