package it.unipr.fdpb.lecture04.es02;

public class Biblioteca {
    private Prestito[] prestiti;
    private int numeroPrestitiAttuali;
    private static final int CAPACITA_DEFAULT = 100;

    public Biblioteca() {
        this.prestiti = new Prestito[CAPACITA_DEFAULT];
        this.numeroPrestitiAttuali = 0;
    }

    public boolean isPubblicazionePrestata(String isbn) {
        if (isbn == null) return false;
        for (int i = 0; i < numeroPrestitiAttuali; i++) {
            if (prestiti[i] != null
                    && prestiti[i].getPubblicazionePrestata() != null
                    && isbn.equals(prestiti[i].getPubblicazionePrestata().getCodiceISBN())) {
                return true;
            }
        }
        return false;
    }

    public void registraPrestito(Prestito p) {
        if (p == null || p.getPubblicazionePrestata() == null) {
            throw new IllegalArgumentException("Prestito o pubblicazione non validi.");
        }

        if (isPubblicazionePrestata(p.getPubblicazionePrestata().getCodiceISBN())) {
            throw new PubblicazioneGiaPrestataException(
                    "La pubblicazione con ISBN " + p.getPubblicazionePrestata().getCodiceISBN() + " è già in prestito."
            );
        }

        if (numeroPrestitiAttuali >= prestiti.length) {
            throw new RuntimeException("Capacità massima prestiti raggiunta.");
        }

        prestiti[numeroPrestitiAttuali] = p;
        numeroPrestitiAttuali++;
    }

    public Prestito[] getPrestitiUtente(String idUtente) {
        if (idUtente == null) return new Prestito[0];

        int count = 0;
        for (int i = 0; i < numeroPrestitiAttuali; i++) {
            if (prestiti[i] != null
                    && prestiti[i].getUtenteAssegnatario() != null
                    && idUtente.equals(prestiti[i].getUtenteAssegnatario().getIdUtente())) {
                count++;
            }
        }

        Prestito[] risultato = new Prestito[count];
        if (count == 0) return risultato;

        int indexRisultato = 0;
        for (int i = 0; i < numeroPrestitiAttuali; i++) {
            if (prestiti[i] != null
                    && prestiti[i].getUtenteAssegnatario() != null
                    && idUtente.equals(prestiti[i].getUtenteAssegnatario().getIdUtente())) {
                risultato[indexRisultato++] = prestiti[i];
            }
        }
        return risultato;
    }

    public int getNumeroPrestitiAttuali() {
        return numeroPrestitiAttuali;
    }

    public int contaLibriInPrestito() {
        int count = 0;
        for (int i = 0; i < numeroPrestitiAttuali; i++) {
            if (prestiti[i] != null
                    && prestiti[i].getPubblicazionePrestata() instanceof Libro) {
                count++;
            }
        }
        return count;
    }

    public int contaRivisteInPrestito() {
        int count = 0;
        for (int i = 0; i < numeroPrestitiAttuali; i++) {
            if (prestiti[i] != null
                    && prestiti[i].getPubblicazionePrestata() instanceof Rivista) {
                count++;
            }
        }
        return count;
    }
}