package it.unipr.fdpb.lecture06.es03;

public class Passeggero implements Persona {
    private String codiceFiscale;
    private String nome;
    private String cognome;

    public Passeggero(String codiceFiscale, String nome, String cognome) {
        this.codiceFiscale = codiceFiscale;
        this.nome = nome;
        this.cognome = cognome;
    }

    @Override
    public String getId() {
        return codiceFiscale;
    }

    @Override
    public String getNomeCompleto() {
        return nome + " " + cognome;
    }

    public String getCodiceFiscale() {
        return codiceFiscale;
    }

    public String getNome() {
        return nome;
    }

    public String getCognome() {
        return cognome;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || !(o instanceof Passeggero)) return false;
        Passeggero that = (Passeggero) o;
        return codiceFiscale.equals(that.codiceFiscale);
    }

    @Override
    public int hashCode() {
        return codiceFiscale.hashCode();
    }

    @Override
    public String toString() {
        return getNomeCompleto() + " (" + codiceFiscale + ")";
    }
}