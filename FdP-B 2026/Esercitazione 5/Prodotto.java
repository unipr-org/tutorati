package it.unipr.fdpb.es5;

public class Prodotto {

	private int codice;
	private String nome;
	private double prezzo;
	private int quantita;
	private boolean disponibilita;
	
	
	private boolean verificaDisponibilita() {
		if(this.quantita != 0) {
			return true;
		} else {
			return false;
		}
		//return this.quantita != 0;
	}
	
	public Prodotto() {
		this.codice = 0;
		this.nome = "";
		this.prezzo = 0;
		this.quantita = 0;
		this.disponibilita = verificaDisponibilita();
	}
	
	public Prodotto(int codice, String nome) {
		if(codice > 0) {
			this.codice = codice;
		} else {
			System.out.println("Codice non valido, impostato al default!!");
			this.codice = 0;
		}
		
		this.nome = nome;
		this.prezzo = 0;
		this.quantita = 0;
		this.disponibilita = verificaDisponibilita();
	}
	
	public Prodotto(int codice, String nome, double prezzo, int quantita) {
		if(codice > 0) {
			this.codice = codice;
		} else {
			System.out.println("Codice non valido, impostato al default!!");
			this.codice = 0;
		}
		
		this.nome = nome;
		
		if(prezzo > 0) {
			this.prezzo = prezzo;
		} else {
			System.out.println("Prezzo non valido, impostato al default!!");
			this.prezzo = 0;
		}
		
		if(quantita >= 0) {
			this.quantita = quantita;
		} else {
			System.out.println("Quantita non valida, impostata al default!!");
			this.quantita = 0;
		}
		
		this.disponibilita = verificaDisponibilita();
	}
	
	public int getCodice() {
		return this.codice;
	}
	
	public String getNome() {
		return this.nome;
	}
	
	public double getPrezzo() {
		return this.prezzo;
	}
	
	public int getQuantita() {
		return this.quantita;
	}
	
	public boolean getDisponibilita() {
		return this.disponibilita;
	}
	
	public void setCodice(int codice) {
		if(codice > 0) {
			this.codice = codice;
		} else {
			System.out.println("Codice non valido, non modificato!!");
		}
	}
	
	public void setNome(String nome) {
		this.nome = nome;
	}
	
	public void setPrezzo(double prezzo) {
		if(prezzo > 0) {
			this.prezzo = prezzo;
		} else {
			System.out.println("Prezzo non valido, non modificato!!");
		}
	}
	
	public void setQuantita(int quantita) {
		if(quantita >= 0) {
			this.quantita = quantita;
			this.disponibilita = verificaDisponibilita();
		} else {
			System.out.println("Quantita non valida, non modificata!!");
		}
	}
	
	public void aggiungiQuantita() {
		this.quantita++;
		this.disponibilita = verificaDisponibilita();
	}
	
	public void aggiungiQuantita(int num) {
		if(num >= 0) {
			this.quantita += num;
			this.disponibilita = verificaDisponibilita();
		} else {
			System.out.println("Quantita da aggiungere non valida, non modificata!!");
		}
		
	}
	
	public void rimuoviQuantita() {
		if(this.quantita > 0) {
			this.quantita--;
			this.disponibilita = verificaDisponibilita();
		} else {
			System.out.println("Impossibile rimuovere quantita!!");
		}
	}
	
	public void rimuoviQuantita(int num){
		if(this.quantita > 0 && num >= 0 && num <= this.quantita) {
			this.quantita -= num;
			this.disponibilita = verificaDisponibilita();
		} else {
			System.out.println("Impossibile rimuovere quantita!!");

		}
	}
	
	public void stampa() {
		System.out.println("Codice = " + this.codice + ", Nome = " + this.nome + ", Prezzo = " + this.prezzo + ", Quantita = " + this.quantita);
	}
	
	
	@Override
	public String toString() {
		return "Codice = " + this.codice + ", Nome = " + this.nome + ", Prezzo = " + this.prezzo + ", Quantita = " + this.quantita;
	}
	
	public boolean uguali(Prodotto other) {
		
		if(this == other) {
			return true;
		} 
		
		if(this.codice == other.codice) {
			return true;
		} else {
			return false;
		}
	}
	
	public Prodotto sommaProdotti(Prodotto other) {
		
		Prodotto res;
		
		if(this.codice == other.codice) {
			res = new Prodotto(this.codice, this.nome, this.prezzo, this.quantita + other.quantita);
		} else {
			System.out.println("Prodotti diversi, ritorno prodotto default!!");
			res = new Prodotto();
		}
		return res;
	}
	
	public static void main(String[] args) {
		
		Prodotto p1 = new Prodotto();
		Prodotto p2 = new Prodotto(1, "penna");
		Prodotto p3 = new Prodotto(2, "quaderno", 2.5, 20);
		Prodotto p4 = new Prodotto(2, "quaderno", 2.5, 30);
		
		System.out.println("Prodotti:");
		
		p1.stampa();
		p2.stampa();
		p3.stampa();
		
		System.out.println("Controllo i setter");
		
		p1.setCodice(3);
		p1.setNome("libro");
		p1.setPrezzo(4.5);
		p1.setQuantita(15);
		
		p1.stampa();
		
		System.out.println("Controllo aggiungi/rimuovi quantita");
		
		p1.aggiungiQuantita();
		
		p1.stampa();
		
		p1.aggiungiQuantita(10);
		
		p1.stampa();
		
		p1.aggiungiQuantita(-5);
		
		p1.stampa();
		
		p1.rimuoviQuantita();
		
		p1.stampa();
		
		p1.rimuoviQuantita(3);
		
		p1.stampa();
		
		p1.rimuoviQuantita(-3);
		
		p1.stampa();
		
		System.out.println("Controllo toString()");
		
		System.out.println(p1.toString());
		
		System.out.println("Controllo uguali()");

		System.out.println(p3.uguali(p4));
		
		Prodotto p5 = p3.sommaProdotti(p4);
		
		System.out.println("Controllo sommaProdotti()");
		
		p5.stampa();
		
	}
	
	
	
}
