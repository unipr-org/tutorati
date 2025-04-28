package it.unipr.fdpb.lecture04.es03;

public class ProdottoFisico extends ArticoloVendibile {
    private double pesoKg;

    public ProdottoFisico(String codiceArticolo, String nome, double prezzoBase, double pesoKg) {
        super(codiceArticolo, nome, prezzoBase);
        this.pesoKg = pesoKg;
    }

    public double getPesoKg() {
        return pesoKg;
    }

    @Override
    public double calcolaPrezzoFinale() {
        // Esempio: aggiunge 0.5 euro per kg per spedizione
        double costoSpedizione = pesoKg * 0.5;
        return super.getPrezzoBase() + costoSpedizione;
    }

    @Override
    public String toString() {
        return "ProdottoFisico [codice=" + getCodiceArticolo() + ", nome=" + getNome() +
                ", prezzoBase=" + getPrezzoBase() + ", pesoKg=" + pesoKg + "]";
    }
}
