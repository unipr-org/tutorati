package it.unipr.fdpb.lecture05.es02;

import java.util.NoSuchElementException;

public class TestAgenda {

    public static void main(String[] args) {
        System.out.println("--- Test Gestione Task con Priorita ---");

        AgendaTask<TaskSemplice> agenda = new AgendaTask<>();
        System.out.println("Agenda creata. Numero task: " + agenda.getNumeroTask());

        TaskSemplice t1 = new TaskSemplice(5, "Preparare report", "10/05/2025");
        TaskSemplice t2 = new TaskSemplice(10, "Chiamare cliente X", "08/05/2025");
        TaskSemplice t3 = new TaskSemplice(5, "Revisione codice", "15/05/2025");
        TaskSemplice t4 = new TaskSemplice(8, "Meeting team", "08/05/2025");
        TaskRipetitivo t5 = new TaskRipetitivo(3, "Backup dati", "05/05/2025", 7);

        System.out.println("\nAggiungo task...");
        try {
            agenda.aggiungiTask(t1); System.out.print("Aggiunto t1. Agenda: "); agenda.stampaAgenda();
            agenda.aggiungiTask(t2); System.out.print("Aggiunto t2. Agenda: "); agenda.stampaAgenda();
            agenda.aggiungiTask(t3); System.out.print("Aggiunto t3. Agenda: "); agenda.stampaAgenda();
            agenda.aggiungiTask(t4); System.out.print("Aggiunto t4. Agenda: "); agenda.stampaAgenda();
        } catch (RuntimeException e) {
            System.err.println("Errore aggiunta: " + e.getMessage());
        }
        System.out.println("Numero task: " + agenda.getNumeroTask());


        try {
            System.out.println("\nProssimo task (peek): " + agenda.getProssimoTask());
        } catch (NoSuchElementException e) {
            System.err.println("Errore: " + e.getMessage());
        }

        try {
            System.out.println("\nCompleto prossimo task...");
            TaskSemplice completato = agenda.completaProssimoTask();
            System.out.println("  Completato: " + completato);
            System.out.print("  Agenda ora: "); agenda.stampaAgenda();
            System.out.println("  Numero task: " + agenda.getNumeroTask());

            System.out.println("Completo prossimo task...");
            completato = agenda.completaProssimoTask();
            System.out.println("  Completato: " + completato);
            System.out.print("  Agenda ora: "); agenda.stampaAgenda();
            System.out.println("  Numero task: " + agenda.getNumeroTask());

            System.out.println("Completo prossimo task...");
            completato = agenda.completaProssimoTask();
            System.out.println("  Completato: " + completato);
            System.out.print("  Agenda ora: "); agenda.stampaAgenda();
            System.out.println("  Numero task: " + agenda.getNumeroTask());

            System.out.println("Completo prossimo task...");
            completato = agenda.completaProssimoTask();
            System.out.println("  Completato: " + completato);
            System.out.print("  Agenda ora: "); agenda.stampaAgenda();
            System.out.println("  Numero task: " + agenda.getNumeroTask());

            System.out.println("\nTentativo di completare da agenda vuota...");
            completato = agenda.completaProssimoTask(); // eccezione

        } catch (NoSuchElementException e) {
            System.out.println("OK: Eccezione ricevuta come atteso -> " + e.getMessage());
        }

        System.out.println("\n--- Fine Test Gestione Task ---");
    }
}
