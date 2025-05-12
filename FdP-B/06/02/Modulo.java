package it.unipr.fdpb.lecture06.es02;

import java.util.ArrayList;
import java.util.List;

public class Modulo implements Comparable<Modulo> {
    private String nomeModulo;
    private int ordine;
    private List<MaterialeDidattico> contenuti;

    public Modulo(String nomeModulo, int ordine) {
        this.nomeModulo = nomeModulo;
        this.ordine = ordine;
        this.contenuti = new ArrayList<>();
    }

    public void aggiungiContenuto(MaterialeDidattico md) {
        if (md != null) {
            this.contenuti.add(md);
        }
    }

    public int getDurataTotaleModuloMinuti() {
        int durataTotale = 0;
        for (MaterialeDidattico md : contenuti) {
            if (md != null) {
                durataTotale += md.getDurataStimataMinuti();
            }
        }
        return durataTotale;
    }

    public String getNomeModulo() {
        return nomeModulo;
    }

    public int getOrdine() {
        return ordine;
    }

    public List<MaterialeDidattico> getContenuti() {
        return new ArrayList<>(contenuti);
    }


    @Override
    public int compareTo(Modulo other) {
        return Integer.compare(this.ordine, other.ordine);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || !(o instanceof Modulo)) return false;
        Modulo modulo = (Modulo) o;
        return ordine == modulo.ordine
                && nomeModulo.equals(modulo.nomeModulo);
    }

    @Override
    public int hashCode() {
        return nomeModulo.hashCode() + ordine;
    }

    @Override
    public String toString() {
        return "Modulo{" +
                "nome='" + nomeModulo + '\'' +
                ", ordine=" + ordine +
                ", durata=" + getDurataTotaleModuloMinuti() + "min" +
                '}';
    }
}