package it.unipr.fdpb.lecture05.es01;

public class Magazzino<T extends Catalogabile> {

    private Catalogabile[] articoli;
    private int numeroArticoliPresenti;
    private static final int CAPACITA_MASSIMA = 200;

    public Magazzino() {
        this.articoli = new Catalogabile[CAPACITA_MASSIMA];
        this.numeroArticoliPresenti = 0;
    }

    private int trovaIndiceArticolo(String codiceUnivoco) {
        if (codiceUnivoco == null)
            return -1;
        for (int i = 0; i < numeroArticoliPresenti; i++) {
            if (articoli[i] != null
                    && codiceUnivoco.equals(articoli[i].getCodiceUnivoco())) {
                return i;
            }
        }
        return -1;
    }

    public void aggiungiArticolo(T articolo) {
        if (articolo == null || articolo.getCodiceUnivoco() == null) {
            throw new IllegalArgumentException("Articolo o codice univoco nullo.");
        }
        if (trovaIndiceArticolo(articolo.getCodiceUnivoco()) != -1) {
            throw new IllegalArgumentException("Articolo con codice " + articolo.getCodiceUnivoco() + " gia presente.");
        }
        if (numeroArticoliPresenti >= articoli.length) {
            throw new RuntimeException("Magazzino pieno. Capacita massima: " + articoli.length);
        }
        articoli[numeroArticoliPresenti++] = articolo;
    }

    public boolean rimuoviArticolo(String codiceUnivoco) {
        int indice = trovaIndiceArticolo(codiceUnivoco);
        if (indice == -1) {
            return false;
        }

        for (int i = indice; i < numeroArticoliPresenti - 1; i++) {
            articoli[i] = articoli[i + 1];
        }
        numeroArticoliPresenti--;

        return true;
    }

    public T trovaArticolo(String codiceUnivoco) {
        int indice = trovaIndiceArticolo(codiceUnivoco);
        if (indice != -1) {
            if (articoli[indice] == null)
                throw new IllegalArgumentException("Articolo null.");
            return (T) articoli[indice];
        }
        return null;
    }

    public double calcolaValoreTotale() {
        double valoreTotale = 0.0;
        for (int i = 0; i < numeroArticoliPresenti; i++) {
            if (articoli[i] != null) {
                valoreTotale += articoli[i].getValore();
            }
        }
        return valoreTotale;
    }

    public int getNumeroArticoliPresenti() {
        return numeroArticoliPresenti;
    }
}
