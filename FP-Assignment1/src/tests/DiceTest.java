package tests;

import model.DicePairImpl;
import model.DieImpl;
import model.interfaces.DicePair;
import model.interfaces.Die;
import tests.interfaces.Test;

import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * Performs a series of tests centred around the dice classes
 * @author Daniel Atanasovski
 */
public class DiceTest implements Test {
    private static final Logger logger = Logger.getLogger(Test.class.getName());
    @Override
    public boolean StartTest() {
        boolean pass = true;

        logger.setLevel(Level.FINE);
        logger.log(Level.INFO, "## DiceTest has BEGUN ## ");

        // Tests
        pass = pairTest();

        if (pass)
            logger.log(Level.INFO, "## DiceTest has PASSED ##");
        else
            logger.log(Level.INFO, "## DiceTest has FAILED ##");

        return pass;
    }

    private boolean pairTest () {
        DicePair d1 = new DicePairImpl();
        DicePair d2 = new DicePairImpl(d1.getDie1(), d1.getDie2());
        if (!d1.equals(d2) || d1.hashCode() != d2.hashCode()) {
            logger.log(Level.FINE, "equals Failed");
            return false;
        }

        if (d1.compareTo(d2) != 0){
            logger.log(Level.FINE, "compareTo equals Failed");
            return false;
        }

        d1 = new DicePairImpl(new DieImpl(1, 1, Die.NUM_FACES),
                new DieImpl(2, 2, Die.NUM_FACES));
        d2 = new DicePairImpl(new DieImpl(1, 3, Die.NUM_FACES),
                new DieImpl(2, 2, Die.NUM_FACES));
        if (d1.compareTo(d2) != -1 && d2.compareTo(d1) != 1){
            logger.log(Level.FINE, "compareTo Failed");
            return false;
        }


        return true;
    }
}
