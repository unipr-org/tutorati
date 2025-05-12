package it.unipr.fdpb.lecture06.es01;

public class UtenteSemplice implements Utente {
    private String idUnivoco;
    private String nomeVisualizzato;

    public UtenteSemplice(String idUnivoco, String nomeVisualizzato) {
        this.idUnivoco = idUnivoco;
        this.nomeVisualizzato = nomeVisualizzato;
    }

    @Override
    public String getIdUnivoco() {
        return idUnivoco;
    }

    @Override
    public String getNomeVisualizzato() {
        return nomeVisualizzato;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || !(o instanceof UtenteSemplice)) return false;
        UtenteSemplice that = (UtenteSemplice) o;
        return idUnivoco.equals(that.idUnivoco);
    }

    @Override
    public int hashCode() {
        return idUnivoco.hashCode();
    }

    @Override
    public String toString() {
        return nomeVisualizzato + " (" + idUnivoco + ")";
    }
}
