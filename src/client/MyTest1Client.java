package client;

import model.GameEngineImpl;
import model.SimplePlayer;
import model.interfaces.GameEngine;
import model.interfaces.Player;
import tests.DiceTest;
import tests.GameEngineTest;
import tests.PlayerTest;
import tests.interfaces.Test;
import validate.Validator;
import view.GameEngineCallbackImpl;

/**
 * 
 * @author Daniel Atanasovski
 * 
 */
public class MyTest1Client
{
   public static void main(String args[])
   {
      // TODO: Full test coverage
      // instantiate the GameEngine so we can make calls
      final GameEngine gameEngine = new GameEngineImpl();

      // call method in Validator.jar to test *structural* correctness
      // just passing this does not mean it actually works .. you need to test yourself!
      // pass false if you want to show minimal logging (pass/fail) .. (i.e. ONLY once it passes)
      Validator.validate(false);

      // Player Test
      Test pTest = new PlayerTest();
      pTest.StartTest();
      // Dice Test
      Test dTest = new DiceTest();
      dTest.StartTest();
      // GameEngine Test
      Test gTest = new GameEngineTest();
      gTest.StartTest();
   }
}
