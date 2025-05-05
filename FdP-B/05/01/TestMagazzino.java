package it.unipr.fdpb.lecture05.es01;

public class TestMagazzino {

    public static void main(String[] args) {
        System.out.println("--- Test Gestione Magazzino ---");

        Magazzino<ProdottoFisico> magazzinoProdotti = new Magazzino<>();
        System.out.println("Magazzino creato. Articoli presenti: " + magazzinoProdotti.getNumeroArticoliPresenti());

        ProdottoFisico p1 = new ProdottoFisico("PF001", "Laptop 15 pollici", 950.0, 2.2, "38x25x2 cm");
        ProdottoFisico p2 = new ProdottoFisico("PF002", "Tastiera Meccanica", 120.0, 0.8, "45x15x4 cm");
        ProdottoFisico p3 = new ProdottoFisico("PF003", "Monitor 27 pollici", 350.0, 4.5, "65x40x10 cm");

        try {
            System.out.println("\nAggiungo prodotto PF001...");
            magazzinoProdotti.aggiungiArticolo(p1);
            System.out.println("Aggiungo prodotto PF002...");
            magazzinoProdotti.aggiungiArticolo(p2);
            System.out.println("Articoli presenti: " + magazzinoProdotti.getNumeroArticoliPresenti());
            System.out.println("Valore totale: " + magazzinoProdotti.calcolaValoreTotale());
        } catch (Exception e){
            System.err.println("Errore aggiunta: " + e.getMessage());
        }

        try {
            System.out.println("\nTentativo aggiunta duplicato PF001...");
            magazzinoProdotti.aggiungiArticolo(p1);
        } catch (IllegalArgumentException e) {
            System.out.println("OK: Eccezione ricevuta come atteso -> " + e.getMessage());
        }

        System.out.println("\nTrovo articolo PF002...");
        ProdottoFisico trovato = magazzinoProdotti.trovaArticolo("PF002");
        if (trovato != null) {
            System.out.println("  Trovato: " + trovato.getDescrizione() + ", Valore: " + trovato.getValore());
        } else {
            System.out.println("  Articolo PF002 non trovato.");
        }

        System.out.println("Trovo articolo PF999 (inesistente)...");
        trovato = magazzinoProdotti.trovaArticolo("PF999");
        System.out.println("  Trovato: " + (trovato == null ? "null (corretto)" : trovato));


        System.out.println("\nRimuovo articolo PF001...");
        boolean rimosso = magazzinoProdotti.rimuoviArticolo("PF001");
        System.out.println("  Rimosso? " + rimosso);
        System.out.println("Articoli presenti: " + magazzinoProdotti.getNumeroArticoliPresenti());
        System.out.println("Valore totale: " + magazzinoProdotti.calcolaValoreTotale());

        System.out.println("Rimuovo articolo PF001 (di nuovo)...");
        rimosso = magazzinoProdotti.rimuoviArticolo("PF001");
        System.out.println("  Rimosso? " + rimosso);

        System.out.println("\nAggiungo prodotto PF003...");
        try {
            magazzinoProdotti.aggiungiArticolo(p3);
            System.out.println("Articoli presenti: " + magazzinoProdotti.getNumeroArticoliPresenti());
            System.out.println("Valore totale: " + magazzinoProdotti.calcolaValoreTotale());
        } catch (Exception e) {
            System.err.println("Errore aggiunta: " + e.getMessage());
        }

        System.out.println("\n--- Fine Test Gestione Magazzino ---");
    }
}