package blockchain;

public class Server {
	private BlockChain chain;

	public Server(BlockChain chain) {
		this.chain = chain;
	}

	public BlockChain getChain() {
		return chain;
	}

	public void updateChain(Block newBlock) {
		chain.addBlock(newBlock); // verifies it too
//		String newBlockHash = newBlock.getHash();
//		Block currentLatestBlock = chain.getBlocks().get(chain.getBlocks().size() - 1);
//
//		// Verify Previous hash
//		if (!newBlock.getPreviousHash().equals(currentLatestBlock.getHash()))
//			return;
//
//		// Verify Data
//		ArrayList<Student> data = newBlock.getData();
//		MerkleTree tree = new MerkleTree(data);
//		if (!tree.getRootHash().equals(newBlock.getMerkleRoot()))
//			return;
//
//		// Verify block hash
//		try {
//			String calculatedHash = HashUtil.Hash(Integer.toString(newBlock.getIndex()) + newBlock.getTimestamp().toString()
//					+ tree.getRootHash() + currentLatestBlock.getHash());
//			if (!calculatedHash.equals(newBlockHash)) {
//				return;
//			}
//		} catch (NoSuchAlgorithmException e) {
//			e.printStackTrace();
//		}

//		chain.add
	}
}
