package it.unipr.fdpb.es6;

import it.unipr.fdpb.es5.Prodotto;

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
			
			this.A[this.size] = p;
			this.size += 1;
		}
	}
	
	// Rimuove il prodotto se presente
	public void rimuoviProdotto(Prodotto p) {
		
		int indice = this.contains(p);
		
		if(indice == -1) {
			System.out.println("Elemento non presente in magazzino!!");
		} else {
			this.A[indice] = this.A[this.size - 1];
			this.size -=1;
			
			Prodotto[] B = new Prodotto[this.capacity];
			
			for(int i = 0; i < this.size; i++) {
				B[i] = A[i];
			}
			
			A = B;
		}
		
	}
	
	@Override
	public String toString(){
		
		String res = "Prodotti nel magazzino: \n";
		
		for(int i = 0; i < this.size; i++) {
			res += A[i].toString() + "\n";
		}
		
		return res;
	}
	
	public String spesa(ListP lista) {
		
		String res = "";
		double prezzo = 0;
		
		ElemP elem = lista.getHead();
		
		while(elem != null) {
			
			int indice = this.contains(elem.getValue());
			
			if(indice == -1) {
				return "Elemento " + elem.getValue().toString() + " non presente in magazzino!!";
			} else {
				if(this.A[indice].getQuantita() < elem.getValue().getQuantita()){
					return "Elemento " + elem.getValue().toString() + " non presente in magazzino in quantità richiesta!!";
				}
			}
			elem = elem.getNext();
		}
		
		elem = lista.getHead();
		
		while(elem != null) {
			
			int indice = this.contains(elem.getValue());
						
			prezzo += A[indice].getPrezzo() * elem.getValue().getQuantita();
			
			A[indice].rimuoviQuantita(elem.getValue().getQuantita());
			
			elem = elem.getNext();
		}
		
		return "Costo Spesa = " + prezzo;
	}
	
	public static void main(String[] args) {
		
		Magazzino m = new Magazzino();
		
		System.out.println(m.toString());

		Prodotto p1 = new Prodotto(1,"libro",2.5, 20);
		Prodotto p2 = new Prodotto(2,"quaderno",1.5, 10);
		Prodotto p3 = new Prodotto(3,"penna",3, 200);
		Prodotto p4 = new Prodotto(4,"tavolo",50, 5);
		
		m.aggiungiProdotto(p1);
		m.aggiungiProdotto(p2);
		m.aggiungiProdotto(p3);
		m.aggiungiProdotto(p4);
		
		System.out.println(m.toString());
		
		//m.rimuoviProdotto(p1);
		
		ListP lista = new ListP();
		
		Prodotto p5 = new Prodotto(1,"libro", 0.1, 15);
		Prodotto p6 = new Prodotto(3,"penna", 0.1, 4);
		
		lista.addFirst(p5);
		lista.addFirst(p6);
		
		System.out.println( "Lista = " + lista.toString());
		
		System.out.println(m.spesa(lista));
		
	}
	
}
