package it.unipr.fdpb.lecture06.es03;

import java.time.LocalDate;
import java.util.*;

public class SistemaPrenotazioni {
    private Map<String, Volo> voliProgrammati;
    private Map<String, Prenotazione> prenotazioniEffettuate;

    public SistemaPrenotazioni() {
        this.voliProgrammati = new HashMap<>();
        this.prenotazioniEffettuate = new HashMap<>();
    }

    public void aggiungiVolo(Volo v) {
        if (v != null && v.getNumeroVolo() != null)
            this.voliProgrammati.put(v.getNumeroVolo(), v);
    }

    public Volo getVolo(String numeroVolo) {
        return this.voliProgrammati.get(numeroVolo);
    }

    public Prenotazione creaPrenotazione(String numeroVolo, Passeggero p, String postoDesiderato) {
        Volo volo = this.voliProgrammati.get(numeroVolo);
        if (volo == null)
            throw new NoSuchElementException("Volo non trovato: " + numeroVolo);

        if (volo.getPostiDisponibili() <= 0)
            throw new IllegalStateException("Volo pieno: " + numeroVolo);

        if (!volo.prenotaPosto(postoDesiderato))
            throw new IllegalArgumentException("Posto non valido o gia' occupato: " + postoDesiderato + " su volo " + numeroVolo);

        String idPrenotazione = UUID.randomUUID().toString(); // genera un ID random

        Prenotazione nuovaPrenotazione = new Prenotazione(idPrenotazione, volo, p, postoDesiderato.toUpperCase());

        this.prenotazioniEffettuate.put(idPrenotazione, nuovaPrenotazione);

        return nuovaPrenotazione;
    }

    public boolean cancellaPrenotazione(String idPrenotazione) {
        Prenotazione prenotazione = this.prenotazioniEffettuate.get(idPrenotazione);
        if (prenotazione == null)
            return false;

        Volo voloAssociato = prenotazione.getVolo();
        String postoLiberato = prenotazione.getPostoAssegnato();

        this.prenotazioniEffettuate.remove(idPrenotazione);

        if (voloAssociato != null && postoLiberato != null)
            voloAssociato.cancellaPrenotazionePosto(postoLiberato);

        return true;
    }

    public List<Prenotazione> getPrenotazioniVolo(String numeroVolo) {
        List<Prenotazione> risultato = new ArrayList<>();
        if (numeroVolo == null)
            return risultato;

        for (Prenotazione p : this.prenotazioniEffettuate.values())
            if (p != null
                    && p.getVolo() != null
                    && numeroVolo.equals(p.getVolo().getNumeroVolo()))
                risultato.add(p);

        return risultato;
    }

    public List<Volo> cercaVoli(String codiceIATA_Partenza, String codiceIATA_Arrivo, LocalDate data) {
        List<Volo> risultato = new ArrayList<>();
        if (codiceIATA_Partenza == null
                || codiceIATA_Arrivo == null
                || data == null)
            return risultato;

        for (Volo v : this.voliProgrammati.values()) {
            if (v != null &&
                    v.getAeroportoPartenza() != null &&
                    v.getAeroportoArrivo() != null &&
                    codiceIATA_Partenza.equalsIgnoreCase(v.getAeroportoPartenza().getCodiceIATA()) &&
                    codiceIATA_Arrivo.equalsIgnoreCase(v.getAeroportoArrivo().getCodiceIATA()) &&
                    v.getOrarioPartenza() != null &&
                    v.getOrarioPartenza().toLocalDate().equals(data))
            {
                risultato.add(v);
            }
        }
        Collections.sort(risultato); // Ordina per orario partenza crescente
        return risultato;
    }
}
