package it.unipr.fdpb.es10;

public class Utente {

	private String nome;
	private String cognome;
	
	public Utente(String nome, String Cognome){
		this.nome = nome;
		this.cognome = nome;
	}

	@Override
	public boolean equals(Object obj) {
		if(this == obj)
			return true;
							// !(obj instanceof Utente)
		if(obj == null || getClass() != obj.getClass())
			return false;
		
		Utente other = (Utente) obj;
		return this.nome.equals(other.nome) && this.cognome.equals(other.cognome);
	}
	
	@Override
	public String toString() {
		return this.nome + this.cognome;
	}
	
	
}
