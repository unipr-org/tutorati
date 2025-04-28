package it.unipr.fdpb.lecture04.es02;

public class Rivista extends Pubblicazione {
    private int meseUscita;
    private int annoUscita;
    private String editore;

    public Rivista(String titolo, String codiceISBN, int meseUscita, int annoUscita, String editore) {
        super(titolo, codiceISBN);
        this.meseUscita = meseUscita;
        this.annoUscita = annoUscita;
        this.editore = editore;
    }

    public int getMeseUscita() {
        return meseUscita;
    }

    public int getAnnoUscita() {
        return annoUscita;
    }

    public String getEditore() {
        return editore;
    }

    @Override
    public String toString() {
        return "Rivista [titolo=" + getTitolo() + ", codiceISBN=" + getCodiceISBN() +
                ", meseUscita=" + meseUscita + ", annoUscita=" + annoUscita +
                ", editore=" + editore + "]";
    }
}