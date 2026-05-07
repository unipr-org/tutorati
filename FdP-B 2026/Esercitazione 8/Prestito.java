package it.unipr.fdpb.es8;

public class Prestito {

	private Pubblicazione pubblicazionePrestata;
	private Utente utenteAssegantario;
	private String dataScadenza;
	
	Prestito(Pubblicazione pubblicazionePrestata, Utente utenteAssegantario, String dataScadenza){
		this.pubblicazionePrestata = pubblicazionePrestata;
		this.utenteAssegantario = utenteAssegantario;
		this.dataScadenza = dataScadenza;
	}
	
	public Pubblicazione getPubblicazionePrestata() {
		return this.pubblicazionePrestata;
	}
	
	public Utente getUtenteAssegnatario() {
		return this.utenteAssegantario;
	}
	
	public String getDataScadenza() {
		return this.dataScadenza;
	}
	
	@Override
	public String toString() {
		
		/**
		 * Questo funziona perchè abbiamo fatto override di toString nelle classi Pubblicazione e Utente
		 * 		return "Prestito:\n" + this.pubblicazionePrestata + "\nAssegnatario:\n" + this.utenteAssegantario + "\nScadenza" + this.dataScadenza; 
		 */
		
		return "Prestito:\n" + this.pubblicazionePrestata.toString() + "\nAssegnatario:\n" + this.utenteAssegantario.toString() + "\nScadenza" + this.dataScadenza;
	}
	
	@Override
	public boolean equals(Object obj) {
		if(this == obj){
			return true;
		}
		if(obj == null || !(obj instanceof Prestito)) {
			return false;
		}
		Prestito other = (Prestito) obj;
		return this.pubblicazionePrestata.equals(other.pubblicazionePrestata);
	}
}
