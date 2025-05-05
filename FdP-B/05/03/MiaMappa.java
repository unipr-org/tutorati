package it.unipr.fdpb.lecture05.es03;

public class MiaMappa<K, V> implements Mappa<K, V> {
    private Coppia<K, V>[] associazioni;
    private int numeroAssociazioni;
    private static final int CAPACITA_MASSIMA = 100;

    public MiaMappa() {
        this.associazioni = new Coppia[CAPACITA_MASSIMA];
        this.numeroAssociazioni = 0;
    }

    private int trovaIndiceChiave(K chiave) {
        for (int i = 0; i < numeroAssociazioni; i++) {
            if (associazioni[i] != null
                    && chiave.equals(associazioni[i].getChiave())) {
                return i;
            }
        }
        return -1;
    }

    @Override
    public void put(K chiave, V valore) {
        int indice = trovaIndiceChiave(chiave);
        if (indice != -1) {
            associazioni[indice].setValore(valore);
        } else {
            if (numeroAssociazioni >= associazioni.length) {
                throw new RuntimeException("Capacita' massima della mappa raggiunta.");
            }
            associazioni[numeroAssociazioni++] = new Coppia<>(chiave, valore);
        }
    }

    @Override
    public V get(K chiave) {
        int indice = trovaIndiceChiave(chiave);
        return (indice != -1) ? associazioni[indice].getValore() : null;
    }

    @Override
    public V remove(K chiave) {
        int indice = trovaIndiceChiave(chiave);
        if (indice == -1) {
            return null;
        }
        V vecchioValore = associazioni[indice].getValore();

        for (int i = 0; i < numeroAssociazioni - 1; i++) {
            associazioni[i] = associazioni[i + 1];
        }
        numeroAssociazioni--;

        return vecchioValore;
    }

    @Override
    public boolean containsKey(K chiave) {
        return trovaIndiceChiave(chiave) != -1;
    }

    @Override
    public int size() {
        return numeroAssociazioni;
    }

    @Override
    public boolean isEmpty() {
        return numeroAssociazioni == 0;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("{");
        for(int i = 0; i < numeroAssociazioni; i++) {
            sb.append(associazioni[i].getChiave()).append("=").append(associazioni[i].getValore());
            if(i < numeroAssociazioni - 1) sb.append(", ");
        }
        sb.append("}");
        return sb.toString();
    }
}