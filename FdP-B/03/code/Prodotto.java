package it.unipr.fdpb.lecture03;

public class Prodotto {
    private int codice;
    private String nome;
    private double prezzo;
    private int quantita;
    private Boolean disponibilita;

    public Prodotto() {
        this(0, "", 0, 0);
    }

    Prodotto(int codice, String nome) {
        this(codice, nome, 0, 0);
    }

    public Prodotto(int codice, String nome, double prezzo, int quantita) {
        this.codice = codice;
        this.nome = nome;
        this.prezzo = prezzo;
        this.quantita = quantita;
        this.disponibilita = quantita > 0;
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
    public Boolean isDisponibile(){
        return this.disponibilita;
    }

    public void setCodice(int codice) {
        if (codice < 0)
            throw new RuntimeException("Codice invalido, deve essere positivo");
        this.codice = codice;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public void setPrezzo(double prezzo) {
        if (prezzo < 0)
            throw new RuntimeException("Prezzo invalido, deve essere positivo");
        this.prezzo = prezzo;
    }

    public void setQuantita(int quantita) {
        if (quantita < 0)
            throw new RuntimeException("Quantita invalida, deve essere positiva");
        this.quantita = quantita;
        this.disponibilita = quantita > 0;
    }

    public void aggiungiQuantita(int quantita) {
        if (quantita < 0)
            throw new RuntimeException("Quantita invalida, deve essere positiva");
        this.quantita += quantita;
        this.disponibilita = quantita > 0;
    }

    public void aggiungiQuantita() {
        aggiungiQuantita(1);
    }

    public void rimuoviQuantita(int quantita){
        if (quantita < 1)
            throw new RuntimeException("Impossibile rimuovere perche la quantita' e' gia' zero");

        if(quantita > this.quantita)
            throw new RuntimeException("Quantita invalida, deve essere minore di quella esistente");

        this.quantita -= quantita;
        this.disponibilita = this.quantita > 0;
    }

    public void rimuoviQuantita() {
        rimuoviQuantita(1);
    }

    public Prodotto somma(Prodotto other) {
        if (this.codice != other.getCodice())
            throw new RuntimeException("Impossibile sommare, codici diversi");

        return new Prodotto(
                this.codice,
                this.nome,
                this.prezzo,
                this.quantita + other.getQuantita());
    }

    public boolean equals(Prodotto other) {
        return this.codice == other.getCodice();
    }

    public void print(){
        System.out.println(nome + " [" + codice + "], €" + prezzo + " [quantita': " + quantita + "]");
    }

    @Override
    public String toString() {
        return nome + " [" + codice + "], €" + prezzo + " [quantita': " + quantita + "]";
    }

    public static void main(String[] args) {
        Prodotto p1 = new Prodotto();
        System.out.println(p1);

        p1.setNome("Prodotto predefinito");
        p1.print();

        Prodotto p2 = new Prodotto(1, "Tastiera");
        p2.print();

        Prodotto p3 = new Prodotto(2, "Mouse", 20.0, 5);
        p3.print();

        p2.setQuantita(10);
        p2.setPrezzo(5);
        p2.print();

        p3.aggiungiQuantita();
        p3.aggiungiQuantita(7);
        p3.print();

        p2.rimuoviQuantita();
        p2.rimuoviQuantita(4);
        p2.print();

        try {
            p1.rimuoviQuantita(100);
        } catch (RuntimeException e) {
            System.err.println(e.getMessage());
        }

        Prodotto p4 = new Prodotto(1, "Tastiera da gaming", 7, 100);
        p4.print();

        try {
            Prodotto p5 = p1.somma(p4);
        } catch (RuntimeException e) {
            System.err.println(e.getMessage());
        }

        Prodotto p5 = p2.somma(p4);
        p5.print();

        if (p2.equals(p4))
            System.out.println("Equal");

        if (!p2.equals(p3))
            System.out.println("Not equal");
    }
}
