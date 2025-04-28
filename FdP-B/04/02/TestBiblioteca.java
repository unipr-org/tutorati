package it.unipr.fdpb.lecture04.es02;

public class TestBiblioteca {

    public static void main(String[] args) {
        System.out.println("--- Test Gestione Biblioteca ---");

        // 1. Crea Biblioteca
        Biblioteca biblioteca = new Biblioteca();
        System.out.println("Biblioteca creata. Prestiti attuali: " + biblioteca.getNumeroPrestitiAttuali());

        // 2. Crea Utenti
        Utente utente1 = new Utente("Mario Rossi", "U001");
        Utente utente2 = new Utente("Anna Verdi", "U002");
        System.out.println("Utenti creati: " + utente1 + ", " + utente2);

        // 3. Crea Pubblicazioni (Libri e Riviste)
        Libro libro1 = new Libro("Il Signore degli Anelli", "978-8845210404", "J.R.R. Tolkien", 1200);
        Libro libro2 = new Libro("Fondamenti di Programmazione", "978-8891902040", "Autore Ignoto", 500);
        Rivista rivista1 = new Rivista("Focus", "ISSN11290057-2405", 5, 2024, "Mondadori Scienza");
        System.out.println("Pubblicazioni create: ");
        System.out.println("  " + libro1);
        System.out.println("  " + libro2);
        System.out.println("  " + rivista1);

        // 4. Crea e registra Prestiti
        Prestito prestito1 = new Prestito(libro1, utente1, "25/05/2025");
        Prestito prestito2 = new Prestito(rivista1, utente1, "10/05/2025");
        Prestito prestito3 = new Prestito(libro2, utente2, "30/05/2025");

        try {
            System.out.println("\nRegistrazione prestito 1...");
            biblioteca.registraPrestito(prestito1);
            System.out.println("Prestito 1 registrato.");
            System.out.println("Prestiti attuali: " + biblioteca.getNumeroPrestitiAttuali());

            System.out.println("Registrazione prestito 2...");
            biblioteca.registraPrestito(prestito2);
            System.out.println("Prestito 2 registrato.");
            System.out.println("Prestiti attuali: " + biblioteca.getNumeroPrestitiAttuali());

            System.out.println("Registrazione prestito 3...");
            biblioteca.registraPrestito(prestito3);
            System.out.println("Prestito 3 registrato.");
            System.out.println("Prestiti attuali: " + biblioteca.getNumeroPrestitiAttuali());

        } catch (PubblicazioneGiaPrestataException e) {
            System.err.println(e.getMessage());
        }
        catch (RuntimeException e) {
            System.err.println("Errore registrazione prestito: " + e.getMessage());
        }

        // 5. Testa isPubblicazionePrestata
        System.out.println("\nVerifica prestiti:");
        System.out.println("Libro '" + libro1.getTitolo() + "' (ISBN: " + libro1.getCodiceISBN() + ") è in prestito? "
                + biblioteca.isPubblicazionePrestata(libro1.getCodiceISBN()));
        System.out.println("Rivista '" + rivista1.getTitolo() + "' (ISBN: " + rivista1.getCodiceISBN() + ") è in prestito? "
                + biblioteca.isPubblicazionePrestata(rivista1.getCodiceISBN()));
        System.out.println("Libro non prestato (ISBN: FAKE-123) è in prestito? "
                + biblioteca.isPubblicazionePrestata("FAKE-123"));

        // 6. Testa registrazione duplicata (eccezione)
        System.out.println("\nTentativo registrazione duplicata (libro1):");
        Prestito prestitoDuplicato = new Prestito(libro1, utente2, "01/06/2025");
        try {
            biblioteca.registraPrestito(prestitoDuplicato);
        } catch (PubblicazioneGiaPrestataException e) {
            System.out.println("OK: Eccezione ricevuta come atteso -> " + e.getMessage());
        } catch (RuntimeException e) {
            System.err.println("Errore imprevisto: " + e.getMessage());
        }
        System.out.println("Prestiti attuali: " + biblioteca.getNumeroPrestitiAttuali());

        // 7. Testa getPrestitiUtente
        System.out.println("\nPrestiti per utente " + utente1.getIdUtente() + ":");
        Prestito[] prestitiU1 = biblioteca.getPrestitiUtente(utente1.getIdUtente());
        System.out.println("  Numero prestiti: " + prestitiU1.length);
        for (Prestito prestito : prestitiU1) {
            System.out.println("  - " + prestito.getPubblicazionePrestata().getTitolo() +
                    " (Scad: " + prestito.getDataScadenza() + ")");
        }

        System.out.println("Prestiti per utente " + utente2.getIdUtente() + ":");
        Prestito[] prestitiU2 = biblioteca.getPrestitiUtente(utente2.getIdUtente());
        System.out.println("  Numero prestiti: " + prestitiU2.length);
        for (Prestito prestito : prestitiU2) {
            System.out.println("  - " + prestito.getPubblicazionePrestata().getTitolo() +
                    " (Scad: " + prestito.getDataScadenza() + ")");
        }

        System.out.println("Prestiti per utente 'U999' (inesistente):");
        Prestito[] prestitiU999 = biblioteca.getPrestitiUtente("U999");
        System.out.println("  Numero prestiti: " + prestitiU999.length);

        // 8. Testa conteggio tipi pubblicazione
        System.out.println("\nConteggio tipi pubblicazione in prestito:");
        System.out.println("  Libri in prestito: " + biblioteca.contaLibriInPrestito());
        System.out.println("  Riviste in prestito: " + biblioteca.contaRivisteInPrestito());

        System.out.println("\n--- Fine Test Gestione Biblioteca ---");
    }
}
