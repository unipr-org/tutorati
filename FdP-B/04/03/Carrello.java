package it.unipr.fdpb.lecture04.es03;

public class Carrello {
    private RigaOrdine[] righe;
    private int numeroRighe;
    private static final int CAPACITA_MASSIMA = 50;

    public Carrello() {
        this.righe = new RigaOrdine[CAPACITA_MASSIMA];
        this.numeroRighe = 0;
    }

    private int trovaIndiceRiga(String codiceArticolo) {
        if (codiceArticolo == null) return -1;
        for (int i = 0; i < numeroRighe; i++) {
            if (righe[i] != null
                    && righe[i].getArticoloAcquistato() != null
                    && codiceArticolo.equals(righe[i].getArticoloAcquistato().getCodiceArticolo())) {
                return i;
            }
        }
        return -1;
    }

    public void aggiungiArticolo(ArticoloVendibile a, int quantita) {
        if (a == null)
            throw new IllegalArgumentException("Articolo non valido.");
        if (quantita <= 0)
            throw new IllegalArgumentException("La quantità deve essere positiva.");

        int indiceEsistente = trovaIndiceRiga(a.getCodiceArticolo());

        if (indiceEsistente != -1) {
            RigaOrdine riga = righe[indiceEsistente];
            riga.setQuantita(riga.getQuantita() + quantita);
        } else {
            if (numeroRighe >= righe.length)
                throw new RuntimeException("Capacità massima del carrello raggiunta.");

            righe[numeroRighe] = new RigaOrdine(a, quantita);
            numeroRighe++;
        }
    }

    public void rimuoviArticolo(String codiceArticolo) {
        int indiceDaRimuovere = trovaIndiceRiga(codiceArticolo);

        if (indiceDaRimuovere == -1)
            throw new ArticoloNonTrovatoException("Articolo con codice " + codiceArticolo + " non trovato nel carrello.");

        righe[indiceDaRimuovere] = righe[numeroRighe - 1];
        righe[numeroRighe - 1] = null;
        numeroRighe--;
    }


    public void modificaQuantita(String codiceArticolo, int nuovaQuantita) {
        if (nuovaQuantita <= 0)
            throw new IllegalArgumentException("La nuova quantità deve essere positiva.");

        int indiceRiga = trovaIndiceRiga(codiceArticolo);

        if (indiceRiga == -1)
            throw new ArticoloNonTrovatoException("Articolo con codice " + codiceArticolo + " non trovato nel carrello.");

        righe[indiceRiga].setQuantita(nuovaQuantita);
    }

    public double calcolaTotale() {
        double totale = 0.0;
        for (int i = 0; i < numeroRighe; i++) {
            if (righe[i] != null) {
                totale += righe[i].calcolaSubtotale();
            }
        }
        return totale;
    }

    public int getNumeroRighe() {
        return numeroRighe;
    }

    public ArticoloVendibile[] getProdottiFisiciNelCarrello() {
        int count = 0;
        for (int i = 0; i < numeroRighe; i++) {
            if (righe[i] != null
                    && righe[i].getArticoloAcquistato() instanceof ProdottoFisico) {
                count++;
            }
        }

        ArticoloVendibile[] risultato = new ArticoloVendibile[count];
        int indexRisultato = 0;
        for (int i = 0; i < numeroRighe; i++) {
            if (righe[i] != null
                    && righe[i].getArticoloAcquistato() instanceof ProdottoFisico) {
                risultato[indexRisultato++] = righe[i].getArticoloAcquistato();
            }
        }
        return risultato;
    }

    public ArticoloVendibile[] getServiziNelCarrello() {
        int count = 0;
        for (int i = 0; i < numeroRighe; i++) {
            if (righe[i] != null
                    && righe[i].getArticoloAcquistato() instanceof Servizio) {
                count++;
            }
        }

        ArticoloVendibile[] risultato = new ArticoloVendibile[count];
        int indexRisultato = 0;
        for (int i = 0; i < numeroRighe; i++) {
            if (righe[i] != null
                    && righe[i].getArticoloAcquistato() instanceof Servizio) {
                risultato[indexRisultato++] = righe[i].getArticoloAcquistato();
            }
        }
        return risultato;
    }
}