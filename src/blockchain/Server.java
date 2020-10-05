package blockchain;

public class Server {
	private BlockChain chain;
	
	public Server(BlockChain chain) {
		this.chain = chain;
	}

	public BlockChain getChain() {
		return chain;
	}
}
