package it.unipr.fdpb.lecture06.es03;

import java.time.LocalDateTime;
import java.util.HashSet;
import java.util.Objects;
import java.util.Set;

public class Volo implements Comparable<Volo> {
    private String numeroVolo;
    private Aeroporto aeroportoPartenza;
    private Aeroporto aeroportoArrivo;
    private LocalDateTime orarioPartenza;
    private LocalDateTime orarioArrivo;
    private int capacitaPosti;
    private Set<String> postiPrenotati;

    public Volo(String numeroVolo, Aeroporto aeroportoPartenza, Aeroporto aeroportoArrivo,
                LocalDateTime orarioPartenza, LocalDateTime orarioArrivo, int capacitaPosti) {
        this.numeroVolo = numeroVolo;
        this.aeroportoPartenza = aeroportoPartenza;
        this.aeroportoArrivo = aeroportoArrivo;
        this.orarioPartenza = orarioPartenza;
        this.orarioArrivo = orarioArrivo;
        this.capacitaPosti = capacitaPosti;
        this.postiPrenotati = new HashSet<>();
    }

    public String getNumeroVolo() {
        return numeroVolo;
    }

    public Aeroporto getAeroportoPartenza() {
        return aeroportoPartenza;
    }

    public Aeroporto getAeroportoArrivo() {
        return aeroportoArrivo;
    }

    public LocalDateTime getOrarioPartenza() {
        return orarioPartenza;
    }

    public LocalDateTime getOrarioArrivo() {
        return orarioArrivo;
    }

    public int getCapacitaPosti() {
        return capacitaPosti;
    }

    public int getPostiDisponibili() {
        return capacitaPosti - postiPrenotati.size();
    }

    public boolean prenotaPosto(String numeroPosto) {
        if (numeroPosto == null || numeroPosto.trim().isEmpty()) {
            return false; // Posto non valido
        }
        if (postiPrenotati.size() >= capacitaPosti) {
            return false; // Volo pieno
        }
        return postiPrenotati.add(numeroPosto.toUpperCase());
    }

    public void cancellaPrenotazionePosto(String numeroPosto) {
        if (numeroPosto != null) {
            postiPrenotati.remove(numeroPosto.toUpperCase());
        }
    }

    public Set<String> getPostiPrenotati() {
        return new HashSet<>(postiPrenotati);
    }

    @Override
    public int compareTo(Volo other) {
        return this.orarioPartenza.compareTo(other.orarioPartenza);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || !(o instanceof Volo)) return false;
        Volo volo = (Volo) o;
        return numeroVolo.equals(volo.numeroVolo)
                && orarioPartenza.equals(volo.orarioPartenza)
                && orarioArrivo.equals(volo.orarioArrivo);
    }

    @Override
    public int hashCode() {
        return numeroVolo.hashCode()
                + 13 * orarioPartenza.hashCode()
                + 31 * orarioArrivo.hashCode();
    }

    @Override
    public String toString() {
        return "Volo{" + numeroVolo +
                "[" + aeroportoPartenza.getCodiceIATA() + "->" + aeroportoArrivo.getCodiceIATA() + "]" +
                ", partenza=" + orarioPartenza +
                ", postiDisp=" + getPostiDisponibili() + "/" + capacitaPosti +
                '}';
    }
}