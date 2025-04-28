package it.unipr.fdpb.lecture04.es02;

public class Prestito {
    private Pubblicazione pubblicazionePrestata;
    private Utente utenteAssegnatario;
    private String dataScadenza;

    public Prestito(Pubblicazione pubblicazionePrestata, Utente utenteAssegnatario, String dataScadenza) {
        this.pubblicazionePrestata = pubblicazionePrestata;
        this.utenteAssegnatario = utenteAssegnatario;
        this.dataScadenza = dataScadenza;
    }

    public Pubblicazione getPubblicazionePrestata() {
        return pubblicazionePrestata;
    }

    public Utente getUtenteAssegnatario() {
        return utenteAssegnatario;
    }

    public String getDataScadenza() {
        return dataScadenza;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Prestito prestito = (Prestito) obj;
        return pubblicazionePrestata != null && pubblicazionePrestata.equals(prestito.getPubblicazionePrestata());
    }

    @Override
    public int hashCode() {
        return pubblicazionePrestata != null ? pubblicazionePrestata.hashCode() : 0;
    }

    @Override
    public String toString() {
        return "Prestito [pubblicazione=" + pubblicazionePrestata.getCodiceISBN() +
                ", utente=" + utenteAssegnatario.getIdUtente() +
                ", scadenza=" + dataScadenza + "]";
    }
}