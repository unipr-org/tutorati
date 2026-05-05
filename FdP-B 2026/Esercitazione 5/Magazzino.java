package it.unipr.fdpb.es5;

public class Magazzino {

	private Prodotto[] A;
	private int size;
	private int capacity;
	
	private void enlarge(){
		Prodotto[] B = new Prodotto[this.capacity * 2];
		
		for(int i = 0; i < this.size; i++) {
			B[i] = this.A[i];
		}
				
		this.capacity = this.capacity*2;
		this.A = B;
	}
	
	public Magazzino(){
		this.size = 0;
		this.capacity = 5;
		this.A = new Prodotto[this.capacity];
	}
	
	public int contains(Prodotto p) {
		for(int i = 0; i < this.size; i++) {
			if(A[i].uguali(p)){
				return i;
			}
		}
		return -1;
	}
	
	
	public void aggiungiProdotto(Prodotto p) {
		
		int indice = this.contains(p);
		
		if(indice != -1){
			System.out.println("Prodotto gia presente in magazzino, somma quantita!!!");
			this.A[indice] = this.A[indice].sommaProdotti(p);
		} else {
			if(this.size == this.capacity) {
				this.enlarge();
			}
			// Da finire
		}
	}
	
	
	public static void main(String[] args) {
		
	}
	
}
