package it.unipr.fdpb.lecture06.es03;

import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.LocalTime;
import java.util.List;
import java.util.NoSuchElementException;

public class TestVoli {

    public static void main(String[] args) {
        System.out.println("--- Test Sistema Prenotazione Voli ---");

        Aeroporto mxp = new Aeroporto("MXP", "Milano Malpensa", "Milano");
        Aeroporto lhr = new Aeroporto("LHR", "London Heathrow", "Londra");
        Aeroporto fco = new Aeroporto("FCO", "Roma Fiumicino", "Roma");

        LocalDateTime oggiPomeriggio = LocalDateTime.of(LocalDate.now(), LocalTime.of(15, 30));
        LocalDateTime oggiSera = LocalDateTime.of(LocalDate.now(), LocalTime.of(20, 0));
        LocalDateTime domaniMattina = LocalDateTime.of(LocalDate.now().plusDays(1), LocalTime.of(9, 0));

        Volo v1 = new Volo("AZ123", mxp, lhr, oggiPomeriggio, oggiPomeriggio.plusHours(2), 4);
        Volo v2 = new Volo("BA456", mxp, lhr, oggiSera, oggiSera.plusHours(2), 180);
        Volo v3 = new Volo("AZ789", mxp, fco, domaniMattina, domaniMattina.plusHours(1), 150);

        SistemaPrenotazioni sistema = new SistemaPrenotazioni();
        sistema.aggiungiVolo(v1);
        sistema.aggiungiVolo(v2);
        sistema.aggiungiVolo(v3);
        System.out.println("Voli aggiunti al sistema.");
        System.out.println("Volo AZ123: " + sistema.getVolo("AZ123"));

        Passeggero pass1 = new Passeggero("RSSMRA80A01H501A", "Mario", "Rossi");
        Passeggero pass2 = new Passeggero("VRDANN85B41H501B", "Anna", "Verdi");
        Passeggero pass3 = new Passeggero("BNCLCU90C02H501C", "Luca", "Bianchi");
        Passeggero pass4 = new Passeggero("GLLGIA95D43H501D", "Giulia", "Galli");

        System.out.println("\nCreazione prenotazioni...");
        Prenotazione p1 = null, p2 = null, p3 = null;
        try {
            p1 = sistema.creaPrenotazione("AZ123", pass1, "1A");
            System.out.println("  Creata prenotazione: " + p1.getIdPrenotazione() + " per " + p1.getPasseggero().getNomeCompleto());
            System.out.println("  Posti disponibili su AZ123: " + v1.getPostiDisponibili());

            p2 = sistema.creaPrenotazione("AZ123", pass2, "1B");
            System.out.println("  Creata prenotazione: " + p2.getIdPrenotazione() + " per " + p2.getPasseggero().getNomeCompleto());
            System.out.println("  Posti disponibili su AZ123: " + v1.getPostiDisponibili());

            p3 = sistema.creaPrenotazione("AZ123", pass3, "2A");
            System.out.println("  Creata prenotazione: " + p3.getIdPrenotazione() + " per " + p3.getPasseggero().getNomeCompleto());
            System.out.println("  Posti disponibili su AZ123: " + v1.getPostiDisponibili());

        } catch(NoSuchElementException | IllegalStateException | IllegalArgumentException e) {
            System.err.println("Errore prenotazione: " + e.getMessage());
        }

        System.out.println("\nTest eccezioni prenotazione:");
        try {
            System.out.print("  Prenotazione posto 1A (occupato): ");
            sistema.creaPrenotazione("AZ123", pass4, "1A");
        } catch(IllegalArgumentException e) {
            System.out.println("OK -> " + e.getMessage());
        }

        try {
            System.out.print("  Prenotazione su volo inesistente (XX999): ");
            sistema.creaPrenotazione("XX999", pass4, "1A");
        } catch(NoSuchElementException e) {
            System.out.println("OK -> " + e.getMessage());
        }

        System.out.println("\nPrenotazioni per volo AZ123:");
        List<Prenotazione> prenotazioniV1 = sistema.getPrenotazioniVolo("AZ123");
        for(Prenotazione pr : prenotazioniV1) {
            System.out.println("  - ID: " + pr.getIdPrenotazione() + ", Passeggero: " + pr.getPasseggero().getNomeCompleto() + ", Posto: " + pr.getPostoAssegnato());
        }
        System.out.println("  Posti prenotati (verifica interna): " + v1.getPostiPrenotati());


        if (p2 != null) {
            System.out.println("\nCancellazione prenotazione " + p2.getIdPrenotazione() + "...");
            boolean cancellata = sistema.cancellaPrenotazione(p2.getIdPrenotazione());
            System.out.println("  Cancellata? " + cancellata);
            System.out.println("  Posti disponibili su AZ123: " + v1.getPostiDisponibili());
            System.out.println("  Posti prenotati (verifica interna): " + v1.getPostiPrenotati());

            System.out.println("Tentativo cancellazione stessa prenotazione:");
            cancellata = sistema.cancellaPrenotazione(p2.getIdPrenotazione());
            System.out.println("  Cancellata? " + cancellata);
        }

        System.out.println("\nRicerca voli MXP -> LHR per oggi (" + LocalDate.now() + "):");
        List<Volo> voliOggi = sistema.cercaVoli("MXP", "LHR", LocalDate.now());
        for (Volo v : voliOggi) {
            System.out.println("  - " + v.getNumeroVolo() + " alle " + v.getOrarioPartenza().toLocalTime());
        }

        System.out.println("\nRicerca voli MXP -> FCO per domani (" + LocalDate.now().plusDays(1) + "):");
        List<Volo> voliDomani = sistema.cercaVoli("MXP", "FCO", LocalDate.now().plusDays(1));
        for (Volo v : voliDomani) {
            System.out.println("  - " + v.getNumeroVolo() + " alle " + v.getOrarioPartenza().toLocalTime());
        }

        System.out.println("\n--- Fine Test Sistema Prenotazione Voli ---");
    }
}