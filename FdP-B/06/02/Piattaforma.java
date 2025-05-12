package it.unipr.fdpb.lecture06.es02;

import java.util.*;

public class Piattaforma {
    private Map<String, Corso> corsiDisponibili;
    private Map<String, Set<String>> iscrizioni;

    public Piattaforma() {
        this.corsiDisponibili = new HashMap<>();
        this.iscrizioni = new HashMap<>();
    }

    public void aggiungiCorso(Corso c) {
        if (c != null && c.getIdCorso() != null) {
            this.corsiDisponibili.put(c.getIdCorso(), c);
        }
    }

    public Corso getCorso(String idCorso) {
        return this.corsiDisponibili.get(idCorso);
    }

    public void iscriviStudente(String idStudente, String idCorso) {
        if (idStudente == null || idCorso == null) {
            throw new IllegalArgumentException("ID studente o ID corso nullo.");
        }
        if (!this.corsiDisponibili.containsKey(idCorso)) {
            throw new NoSuchElementException("Corso con ID " + idCorso + " non trovato.");
        }
        
        Set<String> corsiIscritti;
        if (this.iscrizioni.containsKey(idStudente)) {
            corsiIscritti = this.iscrizioni.get(idStudente);
        } else {
            corsiIscritti = new HashSet<>();
            this.iscrizioni.put(idStudente, corsiIscritti);
        }

        corsiIscritti.add(idCorso);
    }

    public Set<Corso> getCorsiStudente(String idStudente) {
        Set<Corso> corsiIscritti = new HashSet<>();
        
        Set<String> idCorsiIscritti = this.iscrizioni.containsKey(idStudente) 
                ? this.iscrizioni.get(idStudente) 
                : Collections.emptySet();
        
        for (String idCorso : idCorsiIscritti) {
            Corso corso = this.corsiDisponibili.get(idCorso);
            if (corso != null) {
                corsiIscritti.add(corso);
            }
        }
        return corsiIscritti;
    }

    public Set<String> getStudentiIscritti(String idCorso) {
        Set<String> studentiIscritti = new HashSet<>();
        if (idCorso == null || !this.corsiDisponibili.containsKey(idCorso)) {
            return studentiIscritti; // Ritorna set vuoto se corso non valido
        }
        for (String idStudente : this.iscrizioni.keySet()) {
            Set<String> corsiStudente = this.iscrizioni.get(idStudente);
            if (corsiStudente != null && corsiStudente.contains(idCorso)) {
                studentiIscritti.add(idStudente);
            }
        }
        return studentiIscritti;
    }
}
