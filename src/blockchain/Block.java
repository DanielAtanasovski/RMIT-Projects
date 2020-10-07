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
public class Block {
	private int index = 0;
	private LocalDateTime timestamp = null;
	private ArrayList<Student> data = new ArrayList<Student>(); // 4 student data per block
	private MerkleTree tree = null;
	private String merkleRoot = null;
	private String hash = null;
	private String previousHash = null;

	/**
	 * @param index
	 * @param timestamp
	 * @param data
	 * @param previousHash
	 */
	public Block(int index, LocalDateTime timestamp, ArrayList<Student> data, String previousHash) {
		this.index = index;
		this.timestamp = timestamp;
		this.data = data;
		this.previousHash = previousHash;
	}

	public void mineBlock() {
		if (hash != null) {
			System.out.println("Warning: Block has already been mined!");
			return;
		}

		tree = new MerkleTree(data);
		merkleRoot = tree.getRootHash();
		try {
			this.hash = HashUtil.Hash(Integer.toString(index) + timestamp.toString() + merkleRoot + previousHash);
		} catch (NoSuchAlgorithmException e) {
			e.printStackTrace();
		}
		System.out.println("Block " + index + " has been mined!");
	}

	public boolean addStudent(Student student) {
		if (data.size() >= 4) {
			System.out.println("Warning: Block is full!");
			return false;
		}

		// Verifying is not necessary for this question
		if (previousHash != "0") {
			data.add(student);

			return true;
		}

		return false;
	}

	public boolean verifyStudent(Student student) {
		boolean found = false;
		try {
			String hash = HashUtil.Hash(student.toString());
			
			if (tree.getLeft() == null)
				return false;
			
			if (hash.equals(tree.getLeft().getLeftLeaf().getHash()) || hash.equals(tree.getLeft().getRightLeaf().getHash())
					|| hash.equals(tree.getRight().getLeftLeaf().getHash())
					|| hash.equals(tree.getRight().getRightLeaf().getHash())) {
				found = true;
			}
		} catch (NoSuchAlgorithmException e) {
			e.printStackTrace();
		}
		
		return found;
	}

	public String getHash() {
		return hash;
	}
	
	public String getPreviousHash() {
		return previousHash;
	}
	
	public MerkleTree getTree() {
		return tree;
	}

	public String getMerkleRoot() {
		return merkleRoot;
	}

	public boolean isBlockFull() {
		if (data.size() >= 4)
			return true;
		return false;
	}
	
	public LocalDateTime getTimestamp() {
		return timestamp;
	}
	
	public ArrayList<Student> getData() {
		return data;
	}

	public int getIndex() {
		return index;
	}

	@Override
	public String toString() {
		StringBuilder stringBuilder = new StringBuilder();
		stringBuilder.append("Block " + index + "\n");
		stringBuilder.append("Time: " + timestamp.toString() + "\n");
		for (int i = 0; i < data.size(); i++) {
			stringBuilder.append(data.get(i).toString() + "\n");
		}
		stringBuilder.append("Hash: " + (hash == null ? "Not Mined Yet" : hash.toString()) + "\n");
		stringBuilder.append("Previous Hash: " + previousHash.toString() + "\n");
		return stringBuilder.toString();
	}
}
