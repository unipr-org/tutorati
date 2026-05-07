package it.unipr.fdpb.es8;

public class Pubblicazione {

	private String titolo;
	private int codice;
	
	Pubblicazione(String titolo, int codice){
		this.titolo = titolo;
		this.codice = codice;
	}
	
	public String getTitolo() {
		return this.titolo;
	}
	
	public int getCodice() {
		return this.codice;
	}
	
	@Override
	public String toString() {
		return "Titolo: " + this.titolo + "\nCodice: " + this.codice;
	}
	
	@Override
	public boolean equals(Object obj) {
		if (this == obj) {
			return true;
		}
		if(obj == null || !(obj instanceof Pubblicazione)){
			return false;
		}
		
		Pubblicazione other = (Pubblicazione) obj;
		return this.codice == other.codice;
	}
	
}
