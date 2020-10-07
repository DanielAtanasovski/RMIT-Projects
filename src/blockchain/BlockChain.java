package blockchain;

import java.time.LocalDateTime;
import java.util.ArrayList;

import types.Student;

/**
 * @author Daniel Atanasovski
 *
 */
public class BlockChain {

	private ArrayList<Block> chain = new ArrayList<Block>();
	private Block inProgressBlock = null;

	public BlockChain() {
		// Create Genesis
		Student genesisStudent = new Student("0", "Genesis", "GenesisDegree", "01/01/1970", 0.0f, 1970);
		ArrayList<Student> data = new ArrayList<Student>();
		Block genesisBlock = new Block(0, LocalDateTime.now(), data, "0");
		genesisBlock.addStudent(genesisStudent);
		genesisBlock.mineBlock();
		chain.add(genesisBlock);
	}

	public void addStudent(Student student) {
		if (inProgressBlock != null) {
			inProgressBlock.addStudent(student);
			if (inProgressBlock.isBlockFull()) {
				inProgressBlock.mineBlock();
				chain.add(inProgressBlock);
				inProgressBlock = null;
			}
		} else {
			ArrayList<Student> data = new ArrayList<Student>();
			data.add(student);
			inProgressBlock = new Block(chain.size(), LocalDateTime.now(), data, chain.get(chain.size() - 1).getHash());
		}
	}

	public Block verifyStudent(Student student) {
		Block block = null;
		for (int i = 0; i < chain.size(); i++) {
			if (chain.get(i).verifyStudent(student)) {
				block = chain.get(i);
				break;
			}
		}
		
		return block;
	}

	@Override
	public String toString() {
		StringBuilder stringBuilder = new StringBuilder();
		for (int i = 0; i < chain.size(); i++) {
			stringBuilder.append("------------\n");
			stringBuilder.append(chain.get(i).toString() + "\n");
		}
		return stringBuilder.toString();
	}
}
