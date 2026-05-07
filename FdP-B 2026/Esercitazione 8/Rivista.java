package it.unipr.fdpb.es8;

public class Rivista extends Pubblicazione{

	private int meseUscita;
	private int annoUscita;
	private String editore;
	
	Rivista(String titolo, int codice, int mese, int anno, String editore){
		super(titolo, codice);
		this.meseUscita = mese;
		this.annoUscita = anno;
		this.editore = editore;
	}
	
	public int getMese() {
		return this.meseUscita;
	}
	
	public int getAnno() {
		return this.annoUscita;
	}
	
	public String getEditore() {
		return this.editore;
	}
	
	@Override
	public String toString() {
		return super.toString() + "\nUscita: " + this.meseUscita + "/" + this.annoUscita + "\nEditore: " + this.editore;
	}
	
	@Override
	public boolean equals(Object obj) {
		if(this == obj) {
			return true;
		}
		if(obj == null || !(obj instanceof Rivista)) {
			return false;
		}
		Rivista other = (Rivista) obj;
		return super.equals(other) && this.meseUscita == other.meseUscita && this.annoUscita == other.annoUscita;
	}
	
}
