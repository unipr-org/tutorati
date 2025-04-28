package it.unipr.fdpb.lecture04.es03;

public class RigaOrdine {
    private ArticoloVendibile articoloAcquistato;
    private int quantita;

    public RigaOrdine(ArticoloVendibile articoloAcquistato, int quantita) {
        if (quantita <= 0)
            throw new IllegalArgumentException("La quantità deve essere positiva.");

        this.articoloAcquistato = articoloAcquistato;
        this.quantita = quantita;
    }

    public ArticoloVendibile getArticoloAcquistato() {
        return articoloAcquistato;
    }

    public int getQuantita() {
        return quantita;
    }

    public void setQuantita(int q) {
        if (q <= 0)
            throw new IllegalArgumentException("La quantità deve essere positiva.");

        this.quantita = q;
    }


    public double calcolaSubtotale() {
        if (articoloAcquistato == null)
            return 0.0;
        return articoloAcquistato.calcolaPrezzoFinale() * quantita;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        RigaOrdine that = (RigaOrdine) obj;
        return articoloAcquistato != null && articoloAcquistato.equals(that.getArticoloAcquistato());
    }

    @Override
    public int hashCode() {
        return articoloAcquistato != null ? articoloAcquistato.hashCode() : 0;
    }

    @Override
    public String toString() {
        return "RigaOrdine [articolo=" + (articoloAcquistato != null ? articoloAcquistato.getCodiceArticolo() : "null") +
                ", quantita=" + quantita + ", subtotale=" + calcolaSubtotale() + "]";
    }
}
