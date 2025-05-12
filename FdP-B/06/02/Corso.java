package it.unipr.fdpb.lecture06.es02;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Corso {
    private String titoloCorso;
    private String idCorso;
    private String docente;
    private List<Modulo> moduli;

    public Corso(String titoloCorso, String idCorso, String docente) {
        this.titoloCorso = titoloCorso;
        this.idCorso = idCorso;
        this.docente = docente;
        this.moduli = new ArrayList<>();
    }

    public void aggiungiModulo(Modulo m) {
        if (m != null && !this.moduli.contains(m)) {
            this.moduli.add(m);
            Collections.sort(this.moduli); // Mantiene ordinato per 'ordine'
        }
    }

    public int getDurataTotaleCorsoMinuti() {
        int durataTotale = 0;
        for (Modulo mod : moduli) {
            if (mod != null) {
                durataTotale += mod.getDurataTotaleModuloMinuti();
            }
        }
        return durataTotale;
    }

    public String getTitoloCorso() {
        return titoloCorso;
    }

    public String getIdCorso() {
        return idCorso;
    }

    public String getDocente() {
        return docente;
    }

    public List<Modulo> getModuli() {
        return new ArrayList<>(moduli); // Ritorna una copia
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || !(o instanceof Corso)) return false;
        Corso corso = (Corso) o;
        return idCorso.equals(corso.idCorso);
    }

    @Override
    public int hashCode() {
        return idCorso.hashCode();
    }

    @Override
    public String toString() {
        return "Corso{" +
                "titolo='" + titoloCorso + '\'' +
                ", id='" + idCorso + '\'' +
                ", docente='" + docente + '\'' +
                ", durata=" + getDurataTotaleCorsoMinuti() + "min" +
                '}';
    }
}
