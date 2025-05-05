package it.unipr.fdpb.lecture05.es03;

public interface Mappa<K, V> {
    void put(K chiave, V valore);
    V get(K chiave);
    V remove(K chiave);
    boolean containsKey(K chiave);
    int size();
    boolean isEmpty();
}
