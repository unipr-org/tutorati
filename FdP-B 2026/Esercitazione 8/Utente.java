package it.unipr.fdpb.es8;

public class Utente {

	private String nome;
	private int id;
	
	Utente(String nome, int id){
		this.nome = nome;
		this.id = id;
	}
	
	public String getNome() {
		return this.nome;
	}
	
	public int getId() {
		return this.id;
	}
	
	@Override
	public String toString() {
		return "Nome: " + this.nome + "\nId: " + this.id;
	}
	
	@Override
	public boolean equals(Object obj) {
		if(this == obj) {
			return true;
		}
		if(obj == null || !(obj instanceof Utente)) {
			return false;
		}
		Utente other = (Utente) obj;
		return this.id == other.id;
	}
	
}
