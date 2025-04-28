package it.unipr.fdpb.lecture04.es02;

public class Libro extends Pubblicazione {
    private String autore;
    private int numeroPagine;

    public Libro(String titolo, String codiceISBN, String autore, int numeroPagine) {
        super(titolo, codiceISBN);
        this.autore = autore;
        this.numeroPagine = numeroPagine;
    }

    public String getAutore() {
        return autore;
    }

    public int getNumeroPagine() {
        return numeroPagine;
    }

    @Override
    public String toString() {
        return "Libro [titolo=" + getTitolo() + ", codiceISBN=" + getCodiceISBN() +
                ", autore=" + autore + ", numeroPagine=" + numeroPagine + "]";
    }
}