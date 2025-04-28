package it.unipr.fdpb.lecture04.es02;

public class Pubblicazione {
    private String titolo;
    private String codiceISBN;

    public Pubblicazione(String titolo, String codiceISBN) {
        this.titolo = titolo;
        this.codiceISBN = codiceISBN;
    }

    public String getTitolo() {
        return titolo;
    }

    public String getCodiceISBN() {
        return codiceISBN;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || !(obj instanceof Pubblicazione)) return false;
        Pubblicazione other = (Pubblicazione) obj;
        return codiceISBN != null && codiceISBN.equals(other.codiceISBN);
    }

    @Override
    public int hashCode() {
        return codiceISBN != null ? codiceISBN.hashCode() : 0;
    }

    @Override
    public String toString() {
        return "Pubblicazione [titolo=" + titolo + ", codiceISBN=" + codiceISBN + "]";
    }
}
