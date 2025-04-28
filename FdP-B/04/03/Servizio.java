package it.unipr.fdpb.lecture04.es03;

public class Servizio extends ArticoloVendibile {
    private double durataOre;

    public Servizio(String codiceArticolo, String nome, double prezzoBase, double durataOre) {
        super(codiceArticolo, nome, prezzoBase);
        this.durataOre = durataOre;
    }

    public double getDurataOre() {
        return durataOre;
    }

    @Override
    public double calcolaPrezzoFinale() {
        // Esempio: 20 euro per ora
        double costoServizio = durataOre * 20;
        return super.getPrezzoBase() + costoServizio;
    }

    @Override
    public String toString() {
        return "Servizio [codice=" + getCodiceArticolo() + ", nome=" + getNome() +
                ", prezzoBase=" + getPrezzoBase() + ", durataOre=" + durataOre + "]";
    }
}