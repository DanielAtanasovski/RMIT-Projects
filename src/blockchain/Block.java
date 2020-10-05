package blockchain;

import java.nio.charset.StandardCharsets;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.time.LocalDateTime;
import java.util.ArrayList;

import org.bouncycastle.util.encoders.Hex;

import structure.MerkleTree;
import types.Student;

public class Block {
	private int index = 0;
	private LocalDateTime timestamp = null;
	private ArrayList<Student> data = new ArrayList<Student>(); // 4 student data per block
	private MerkleTree tree = null;
	private String merkleRoot = null;
	private String hash = null;
	private String previousHash = null;
	
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
			this.hash = calculateHash();
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
	
	private String calculateHash() throws NoSuchAlgorithmException {
		MessageDigest digest = MessageDigest.getInstance("SHA-256");
		// Convert everything into one string
		String hashComponent = Integer.toString(index) + timestamp.toString() + merkleRoot + previousHash;
		// Hash
		byte[] hash = digest.digest(hashComponent.getBytes(StandardCharsets.UTF_8));
		return new String(Hex.encode(hash));
	}

	public String getHash() {
		return hash;
	}

	public String getMerkleRoot() {
		return merkleRoot;
	}
}
