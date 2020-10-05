package blockchain;

import java.time.LocalDateTime;
import java.util.ArrayList;

import types.Student;

public class BlockChain {
	
	private ArrayList<Block> chain = new ArrayList<Block>();
	
	public BlockChain() {
		// Create Genesis
		Student genesisStudent = new Student("0", "Genesis", "GenesisDegree", "1/1/1970", 0.0f, 1970);
		ArrayList<Student> data = new ArrayList<Student>();
		data.add(genesisStudent);
		Block genesisBlock = new Block(0, LocalDateTime.now(), data, "0");
		chain.add(genesisBlock);
	}
}
