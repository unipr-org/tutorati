package it.unipr.fdpb.es9;

public class Carrello {

	private RigaOrdine[] righe;
	private int size;
	private int capacity;
	
	private void enlarge() {
		RigaOrdine[] B = new RigaOrdine[this.capacity * 2];
		for(int i = 0; i < this.size; i++) {
			B[i] = this.righe[i];
		}
		righe = B;
		this.capacity *= 2;
				
	}
	
	private int contains(RigaOrdine elem) {
		for(int i = 0; i < this.size; i++) {
			if( righe[i].equals(elem))
				return i;
		}
		return -1;
	}
	
	private int contains(String codice) {
		for(int i = 0; i < this.size; i++) {
			if( righe[i].getArticolo().getCodiceArticolo().equals(codice))
				return i;
		}
		return -1;
	}
	
	public Carrello() {
		this.capacity = 5;
		this.size = 0;
		this.righe = new RigaOrdine[this.capacity];
	}
	
	public void aggiungiArticolo(ArticoloVendibile articolo, int quanita) {
		RigaOrdine nuovo = new RigaOrdine(articolo, quanita);
		int indice = contains(nuovo);
		if(indice == -1) {
			if(this.size == this.capacity)
				enlarge();
			this.righe[this.size++] = nuovo;
		} else {
			this.righe[indice].aggiungiQuantita(quanita);
		}
	}
	
	public double calcolaTotale() {
		double res = 0;
		for(int i = 0; i < this.size; i++) {
			res += this.righe[i].calcolaSubtotale();
		}
		return res;
	}
	
	public void rimuoviArticolo(String CodiceArticolo) throws RigaOrdineNonPresenteException {
		int indice = contains(CodiceArticolo);
		if(indice == -1) {
			throw new RigaOrdineNonPresenteException("Nessuna riga presente con " + CodiceArticolo);
		} else {
			righe[indice] = righe[this.size];
			this.size--;
			
			RigaOrdine[] B = new RigaOrdine[this.capacity];
			for(int i = 0; i < this.size; i++) {
				B[i] = righe[i];
			}
			righe = B;
		}
	}
	
	public void modificaQuantita(String CodiceArticolo, int quanita) throws RigaOrdineNonPresenteException {
		int indice = contains(CodiceArticolo);
		if(indice == -1) {
			throw new RigaOrdineNonPresenteException("Nessuna riga presente con " + CodiceArticolo);
		} else {
			righe[indice].setQuantita(quanita);
		}
	}
	
}
