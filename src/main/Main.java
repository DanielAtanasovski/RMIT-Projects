/**
 * 
 */
package main;

import java.security.Security;

import blockchain.BlockChain;
import blockchain.Server;

/**
 * @author danie
 *
 */
public class Main {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// Hashing Algorithm
		Security.addProvider(new org.bouncycastle.jce.provider.BouncyCastleProvider());
		
		// BlockChain
		BlockChain testChain = new BlockChain();
		
		// Servers
		Server serverA = new Server(testChain);
		Server serverB = new Server(testChain);
		Server serverC = new Server(testChain);
		
		// User Interface

	}

}
