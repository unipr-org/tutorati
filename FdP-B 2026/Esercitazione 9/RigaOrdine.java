package it.unipr.fdpb.es9;

public class RigaOrdine {

	private ArticoloVendibile articoloAcquistato;
	private int quantita;
	
	public RigaOrdine(ArticoloVendibile articolo, int quantita) {
		if(quantita < 0 )
			throw new QuantitaNegativaArticoloException("Quantità negativa!!");
		this.articoloAcquistato = articolo;
		this.quantita = quantita;
	}
	
	public ArticoloVendibile getArticolo() {
		return this.articoloAcquistato;
	}
	
	public int getQuantita() {
		return this.quantita;
	}
	
	public double calcolaSubtotale() {
		return this.quantita * this.articoloAcquistato.getPrezzoUnitario();
	}
	
	public void aggiungiQuantita(int quantita) {
		if(quantita < 0)
			throw new QuantitaNegativaArticoloException("Quantità negativa");
		this.quantita += quantita;
	}
	
	public void setQuantita(int quantita) {
		if(quantita < 0)
			throw new QuantitaNegativaArticoloException("Quantità negativa");
		this.quantita = quantita;
	}
	
	@Override
	public boolean equals(Object obj) {
		if(this == obj)
			return true;
		if(obj == null || !(obj instanceof RigaOrdine))
			return false;
		
		RigaOrdine other = (RigaOrdine) obj;
		return this.articoloAcquistato.equals(other.articoloAcquistato);
	}
	
	@Override
	public String toString() {
		return "Riga Ordine = {\n" + this.articoloAcquistato.toString() + "\nQuantità = " + this.quantita + "\n}";
	}
	
	public static void main(String[] args) {
		
		ArticoloVendibile a1 = new ProdottoFisico("penna", "p01", 2.3, 2);
		ProdottoFisico a2 = new ProdottoFisico("penna", "p01", 2.3, 2);
		
		RigaOrdine r1 = new RigaOrdine(a1, 5);
		RigaOrdine r2 = new RigaOrdine(a2, 5);
		
		System.out.println(r1.toString());
		System.out.println(r2.toString());
		
		System.out.println(r1.equals(r2));
	}
	
}
