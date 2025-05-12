package it.unipr.fdpb.lecture06.es03;

import java.util.Objects;

public class Aeroporto {
    private String codiceIATA;
    private String nomeCompleto;
    private String citta;

    public Aeroporto(String codiceIATA, String nomeCompleto, String citta) {
        this.codiceIATA = codiceIATA;
        this.nomeCompleto = nomeCompleto;
        this.citta = citta;
    }

    public String getCodiceIATA() {
        return codiceIATA;
    }

    public String getNomeCompleto() {
        return nomeCompleto;
    }

    public String getCitta() {
        return citta;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || !(o instanceof Aeroporto)) return false;
        Aeroporto aeroporto = (Aeroporto) o;
        return codiceIATA.equals(aeroporto.codiceIATA);
    }

    @Override
    public int hashCode() {
        return codiceIATA.hashCode();
    }

    @Override
    public String toString() {
        return codiceIATA + " (" + nomeCompleto + ", " + citta + ")";
    }
}
