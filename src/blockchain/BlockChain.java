package blockchain;

import java.security.NoSuchAlgorithmException;
import java.time.LocalDateTime;
import java.util.ArrayList;

import structure.MerkleTree;
import types.Student;
import util.HashUtil;

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

	public BlockChain(BlockChain copyChain) {
		chain = new ArrayList<Block>(copyChain.chain);
	}

	public void addBlock(Block newblock) {
		if (verifyBlock(newblock))
			chain.add(newblock);
	}

	public boolean verifyBlock(Block newBlock) {
		String newBlockHash = newBlock.getHash();
		Block currentLatestBlock = chain.get(chain.size() - 1);

		// Verify Previous hash
		if (!newBlock.getPreviousHash().equals(currentLatestBlock.getHash())) {
			System.out.println("Failed to add new block. Previous Block Hash Mismatch");
			return false;
		}

		// Verify Data
		ArrayList<Student> data = newBlock.getData();
		MerkleTree tree = new MerkleTree(data);
		if (!tree.getRootHash().equals(newBlock.getMerkleRoot())) {
			System.out.println("Failed to add new block. Merkle Root Hash Mismatch");
			return false;
		}

		// Verify block hash
		try {
			String calculatedHash = HashUtil.Hash(Integer.toString(newBlock.getIndex())
					+ newBlock.getTimestamp().toString() + tree.getRootHash() + currentLatestBlock.getHash());
			if (!calculatedHash.equals(newBlockHash)) {
				System.out.println("Failed to add new block. Block Hash Mismatch");
				return false;
			}
		} catch (NoSuchAlgorithmException e) {
			e.printStackTrace();
		}

		return true;
	}

	public Block addStudent(Student student) {
		Block fullBlock = null;
		if (inProgressBlock != null) {
			inProgressBlock.addStudent(student);
			if (inProgressBlock.isBlockFull()) {
				// Complete this block and return it to verify it
				inProgressBlock.mineBlock();
//				chain.add(inProgressBlock); TODO: REMOVE THIS LINE
				fullBlock = inProgressBlock;
				inProgressBlock = null;
			}
		} else {
			// Create new in progress block
			ArrayList<Student> data = new ArrayList<Student>();
			data.add(student);
			inProgressBlock = new Block(chain.size(), LocalDateTime.now(), data, chain.get(chain.size() - 1).getHash());
		}
		return fullBlock;
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

	public ArrayList<Block> getBlocks() {
		return chain;
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
