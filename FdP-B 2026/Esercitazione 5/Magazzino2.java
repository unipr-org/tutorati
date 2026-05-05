package it.unipr.fdpb.es5;

import java.util.ArrayList;

public class Magazzino2 {

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
	
	public Magazzino2(){
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
	
	public String spesa(ArrayList<Prodotto> lista) {
		
		int dim = lista.size();
		
		
		for(int i = 0; i < dim; i++) {
			if( this.contains(lista.get(i)) < 0){
				
			}
		}
		
		
		return null;
	}
	
	public static void main(String[] args) {
		
		ArrayList<Prodotto> lista = new ArrayList<Prodotto>();
		
		Magazzino2 m = new Magazzino2();
		
		lista.add( new Prodotto(1,null,10, 0));
		lista.add( new Prodotto(2,null,1, 0));
		lista.add( new Prodotto(3,null,5, 0));
	
		System.out.println(lista.get(2));
		

	}
	
}
