package it.unipr.fdpb.lecture06.es02;

import java.util.NoSuchElementException;
import java.util.Set;

public class TestPiattaforma {

    public static void main(String[] args) {
        System.out.println("--- Test Piattaforma Corsi Online ---");

        Piattaforma piattaforma = new Piattaforma();

        Corso c1 = new Corso("Java Base", "JAVAB", "Mario Rossi");
        Modulo m1_1 = new Modulo("Introduzione", 1);
        m1_1.aggiungiContenuto(new LezioneVideo("Setup Ambiente", "L1", "http://...", 30));
        m1_1.aggiungiContenuto(new Quiz("Quiz Intro", "Q1", 5, 15));
        Modulo m1_2 = new Modulo("Variabili e Tipi", 2);
        m1_2.aggiungiContenuto(new LezioneVideo("Tipi Primitivi", "L2", "http://...", 45));
        c1.aggiungiModulo(m1_1);
        c1.aggiungiModulo(m1_2);

        Corso c2 = new Corso("Database SQL", "SQLDB", "Anna Verdi");
        Modulo m2_1 = new Modulo("SELECT", 1);
        m2_1.aggiungiContenuto(new LezioneVideo("Query Base", "L3", "http://...", 60));
        c2.aggiungiModulo(m2_1);

        piattaforma.aggiungiCorso(c1);
        piattaforma.aggiungiCorso(c2);
        System.out.println("Corsi aggiunti alla piattaforma.");
        System.out.println("Corso JAVAB: " + piattaforma.getCorso("JAVAB"));
        System.out.println("Durata totale JAVAB: " + piattaforma.getCorso("JAVAB").getDurataTotaleCorsoMinuti() + " min");
        System.out.println("Durata totale SQLDB: " + piattaforma.getCorso("SQLDB").getDurataTotaleCorsoMinuti() + " min");

        String studente1 = "S001";
        String studente2 = "S002";

        System.out.println("\nIscrizione studenti...");
        try {
            piattaforma.iscriviStudente(studente1, "JAVAB");
            piattaforma.iscriviStudente(studente1, "SQLDB");
            piattaforma.iscriviStudente(studente2, "JAVAB");
            System.out.println("Iscrizioni completate.");
        } catch (NoSuchElementException e) {
            System.err.println("Errore iscrizione: " + e.getMessage());
        }

        try {
            System.out.println("\nTentativo iscrizione a corso inesistente...");
            piattaforma.iscriviStudente(studente1, "PYTHON");
        } catch (NoSuchElementException e) {
            System.out.println("OK: Eccezione ricevuta come atteso -> " + e.getMessage());
        }


        System.out.println("\nCorsi a cui è iscritto " + studente1 + ":");
        Set<Corso> corsiS1 = piattaforma.getCorsiStudente(studente1);
        for(Corso c : corsiS1) {
            System.out.println("  - " + c.getTitoloCorso());
        }

        System.out.println("\nCorsi a cui è iscritto " + studente2 + ":");
        Set<Corso> corsiS2 = piattaforma.getCorsiStudente(studente2);
        for(Corso c : corsiS2) {
            System.out.println("  - " + c.getTitoloCorso());
        }

        System.out.println("\nStudenti iscritti a JAVAB:");
        Set<String> studentiJava = piattaforma.getStudentiIscritti("JAVAB");
        System.out.println("  " + studentiJava);

        System.out.println("\nStudenti iscritti a SQLDB:");
        Set<String> studentiSql = piattaforma.getStudentiIscritti("SQLDB");
        System.out.println("  " + studentiSql);


        System.out.println("\n--- Fine Test Piattaforma ---");
    }
}
