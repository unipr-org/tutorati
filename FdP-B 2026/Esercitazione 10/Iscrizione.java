package it.unipr.fdpb.es10;

public class Iscrizione implements Comparable<Iscrizione>{

	private Utente utente;
	private int meseInizio;
	private int meseFine;
	private int annoInizio;
	private int annoFine;
	
	public Iscrizione(Utente utente, int meseI, int meseF, int annoI, int annoF) {
		if(annoI > annoF) {
			throw new IscrizioneNonControllataException("Date non valide!!");
		}
		if(meseI > meseF) {
			throw new IscrizioneNonControllataException("Date non valide!!");

		}
		if(annoF > annoI + 1){
			throw new IscrizioneNonControllataException("Date non valide!!");
		}
		// annoF è uguale ad annoI oppure ad annoI + 1
		if(12 - meseI + meseF > 12){
			throw new IscrizioneNonControllataException("Date non valide!!");
		}
		this.utente = utente;
		this.meseInizio = meseI;
		this.meseFine = meseF;
		this.annoInizio = annoI;
		this.annoFine = annoF;
	}
	
	public Utente getUtente() {
		return utente;
	}
	
	public int getAnnoI() {
		return annoInizio;
	}
	
	public int getAnnoF() {
		return annoFine;
	}
	
	public boolean overlapsWith(Iscrizione other) {
		if(this.annoInizio == other.annoFine) {
			if(this.meseInizio <= other.meseFine && this.meseFine >= other.meseInizio)
				return true;
		}
		// finire a casa
		return false;
	}
	
	@Override
	public boolean equals(Object obj) {
		if(this == obj)
			return true;
		if(obj == null || getClass() != obj.getClass())
			return false;
		
		Iscrizione other = (Iscrizione) obj;
		return this.utente.equals(other.utente) && annoInizio == other.annoInizio && annoFine == other.annoFine && meseInizio == other.meseInizio && meseFine == other.meseFine;
	}
	
	@Override
	public String toString() {
		return utente.toString() + "\nInizio " + meseInizio + "/" + annoInizio + "\nFine " + meseFine + "/" + annoFine + "\n";
	}

	@Override
	public int compareTo(Iscrizione o) {
		// da fare a casa
		return 0;
	}
	
	
}
