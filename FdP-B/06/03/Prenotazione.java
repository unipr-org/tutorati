package it.unipr.fdpb.lecture06.es03;

import java.time.LocalDateTime;

public class Prenotazione {
    private String idPrenotazione;
    private Volo volo;
    private Passeggero passeggero;
    private String postoAssegnato;
    private LocalDateTime dataOraPrenotazione;

    public Prenotazione(String idPrenotazione, Volo volo, Passeggero passeggero, String postoAssegnato) {
        this.idPrenotazione = idPrenotazione;
        this.volo = volo;
        this.passeggero = passeggero;
        this.postoAssegnato = postoAssegnato;
        this.dataOraPrenotazione = LocalDateTime.now();
    }

    public String getIdPrenotazione() {
        return idPrenotazione;
    }

    public Volo getVolo() {
        return volo;
    }

    public Passeggero getPasseggero() {
        return passeggero;
    }

    public String getPostoAssegnato() {
        return postoAssegnato;
    }

    public LocalDateTime getDataOraPrenotazione() {
        return dataOraPrenotazione;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || !(o instanceof Prenotazione)) return false;
        Prenotazione that = (Prenotazione) o;
        return idPrenotazione.equals(that.idPrenotazione);
    }

    @Override
    public int hashCode() {
        return idPrenotazione.hashCode();
    }

    @Override
    public String toString() {
        return "Prenotazione{" +
                "id='" + idPrenotazione + '\'' +
                ", volo=" + volo.getNumeroVolo() +
                ", passeggero=" + passeggero.getNomeCompleto() +
                ", posto='" + postoAssegnato + '\'' +
                ", timestamp=" + dataOraPrenotazione +
                '}';
    }
}