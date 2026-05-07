package it.unipr.fdpb.es8;

public class Biblioteca {

	private Prestito[] prestiti;
	private int size;
	private int capacity;
	
	
	Biblioteca(){
		this.size = 0;
		this.capacity = 5;
		this.prestiti = new Prestito[this.capacity];
	}
	
	private void enlarge() {
		Prestito[] B = new Prestito[this.capacity*2];
		for(int i = 0; i < this.size; i++) {
			B[i] = this.prestiti[i];
		}
		this.capacity *= 2;
		this.prestiti = B;
	}
	
	private boolean contains(Prestito p) {
		for(int i = 0; i < this.size; i++) {
			if(this.prestiti[i].equals(p)) {
				return true;
			}
		}
		return false;
	}
	
	public void registraPrestito(Prestito p) throws PubblicazioneGiaPrestataException {
		if(contains(p)) {
			throw new PubblicazioneGiaPrestataException("Già in prestito");
		} else {
			if(this.capacity == this.size) {
				enlarge();
			}
			
			this.prestiti[this.size] = p;
			this.size++;
		}
	}
	
	public boolean isPubblicazionePrestata(int codice) {
		for(int i = 0; i < this.size; i++) {
			if(this.prestiti[i].getPubblicazionePrestata().getCodice() == codice) {
				return true;
			}
		}
		return false;
	}
	
	public Prestito[] getPrestitiUtente(int idUtente) {
		
		Prestito[] res = new Prestito[this.size];
		int j = 0;
		
		for(int i = 0; i < this.size; i++) {
			if(this.prestiti[i].getUtenteAssegnatario().getId() == idUtente) {
				res[j] = this.prestiti[i];
				j++;
			}
		}
		return res;
	}
	
	public int getNumeroPrestitiAttuali() {
		return this.size;
	}
	
	@Override
	public String toString() {
		String res = "Prestiti attivi " + this.size + " {\n";
		
		for(int i = 0; i < this.size; i++) {
			res += this.prestiti[i].toString() + "\n";
		}
		
		res += "}";
		return res;
	}
		
}
