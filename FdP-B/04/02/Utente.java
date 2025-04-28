package it.unipr.fdpb.lecture04.es02;

public class Utente {
    private String nome;
    private String idUtente;

    public Utente(String nome, String idUtente) {
        this.nome = nome;
        this.idUtente = idUtente;
    }

    public String getNome() {
        return nome;
    }

    public String getIdUtente() {
        return idUtente;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Utente utente = (Utente) obj;
        // Due utenti sono uguali se hanno lo stesso ID
        return idUtente != null && idUtente.equals(utente.idUtente);
    }

    @Override
    public int hashCode() {
        return idUtente != null ? idUtente.hashCode() : 0;
    }

    @Override
    public String toString() {
        return "Utente [nome=" + nome + ", idUtente=" + idUtente + "]";
    }
}