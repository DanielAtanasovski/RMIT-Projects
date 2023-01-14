package blockchain;

/**
 * @author Daniel Atanasovski
 *
 */
public class Server {
	private BlockChain chain;

	public Server(BlockChain chain) {
		this.chain = chain;
	}

	public BlockChain getChain() {
		return chain;
	}

	public void updateChain(Block newBlock) {
		chain.addBlock(newBlock);
	}

	public boolean verifyChain(Block newBlock) {
		return chain.verifyBlock(newBlock);
	}
}
