package it.unipr.fdpb.es9;

public class ProdottoFisico implements ArticoloVendibile{

	private String nome;
	private String codice;
	private double prezzoU;
	private double peso;
	
	public ProdottoFisico(String nome, String codice, double prezzo, double peso) {
		this.nome = nome;
		this.codice = codice;
		this.prezzoU = prezzo;
		this.peso = peso;
	}
	
	public String getCodiceArticolo() {
		return codice;
	}

	public String getNomeArticolo() {
		return nome;
	}
	
	public double getPrezzoUnitario() {
		return prezzoU;
	}

	public double getPeso() {
		return peso;
	}
	
	@Override
	public boolean equals(Object obj) {
		// Controllo sulle reference
		if(this == obj)
			return true;
		// Controllo che obj non sia nullo e che sia della stessa classe di this
		if(obj == null || !(obj instanceof ProdottoFisico))
			return false;
		
		ProdottoFisico other = (ProdottoFisico) obj;
		return this.codice.equals(other.codice);
	}
	
	@Override
	public String toString() {
		return "Prodotto = {" + this.nome + ", " + this.codice + ", " + this.prezzoU + ", " + this.peso + "}";
	}
	
}
