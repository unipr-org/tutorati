package it.unipr.fdpb.lecture05.es03;

public class Coppia<K, V> {
    private K chiave;
    private V valore;

    public Coppia(K chiave, V valore) {
        this.chiave = chiave;
        this.valore = valore;
    }

    public K getChiave() {
        return chiave;
    }

    public V getValore() {
        return valore;
    }

    public void setValore(V nuovoValore) {
        this.valore = nuovoValore;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || !(obj instanceof Coppia)) return false;

        Coppia<K, V> coppia = (Coppia<K, V>) obj;
        return chiave.equals(coppia.chiave);
    }

    @Override
    public String toString() {
        return "Coppia{" + "chiave=" + chiave + ", valore=" + valore + '}';
    }
}