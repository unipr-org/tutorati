package it.unipr.fdpb.es8;

public class Libro extends Pubblicazione{

	private String autore;
	private int nPagine;
	
	Libro(String titolo, int codice, String autore, int nPagine){
		super(titolo, codice);
		this.autore = autore;
		this.nPagine = nPagine;
	}
	
	public String getAutore() {
		return this.autore;
	}
	
	public int getNPagine() {
		return this.nPagine;
	}
	
	@Override
	public String toString() {
		return super.toString() + "\nAutore: " + this.autore + "\nNumero Pagine: " + this.nPagine;
	}
	
	@Override
	public boolean equals(Object obj) {
		if(obj == this) {
			return true;
		}
		if(obj == null || !(obj instanceof Libro)) {
			return false;
		}
		Libro other = (Libro) obj;
		return super.equals(other) && (this.autore.equals(other.autore));
	}
	
}
