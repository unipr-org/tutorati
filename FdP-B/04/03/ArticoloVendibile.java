package it.unipr.fdpb.lecture04.es03;

public class ArticoloVendibile {
    private String codiceArticolo;
    private String nome;
    private double prezzoBase;

    public ArticoloVendibile(String codiceArticolo, String nome, double prezzoBase) {
        this.codiceArticolo = codiceArticolo;
        this.nome = nome;
        this.prezzoBase = prezzoBase;
    }

    public String getCodiceArticolo() {
        return codiceArticolo;
    }

    public String getNome() {
        return nome;
    }

    public double getPrezzoBase() {
        return prezzoBase;
    }

    public double calcolaPrezzoFinale() {
        return prezzoBase;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || !(obj instanceof ArticoloVendibile)) return false;
        ArticoloVendibile other = (ArticoloVendibile) obj;
        return codiceArticolo != null && codiceArticolo.equals(other.getCodiceArticolo());
    }

    @Override
    public int hashCode() {
        return codiceArticolo != null ? codiceArticolo.hashCode() : 0;
    }

    @Override
    public String toString() {
        return "Articolo [codice=" + codiceArticolo + ", nome=" + nome + ", prezzoBase=" + prezzoBase + "]";
    }
}