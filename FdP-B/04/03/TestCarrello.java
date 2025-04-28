package it.unipr.fdpb.lecture04.es03;

public class TestCarrello {

    public static void main(String[] args) {
        System.out.println("--- Test Gestione Carrello E-commerce ---");

        // 1. Crea Carrello
        Carrello carrello = new Carrello();
        System.out.println("Carrello creato. Numero righe: " + carrello.getNumeroRighe());

        // 2. Crea Articoli Vendibili (Prodotti Fisici e Servizi)
        ProdottoFisico laptop = new ProdottoFisico("LAP001", "Laptop Performante", 1200.00, 2.1);
        ProdottoFisico mouse = new ProdottoFisico("MOU002", "Mouse Wireless", 25.00, 0.1);
        Servizio consulenza = new Servizio("SRV001", "Consulenza Tecnica", 80.00, 1.0);
        Servizio installazione = new Servizio("SRV002", "Installazione Software", 50.00, 0.5);

        System.out.println("Articoli creati:");
        System.out.println("  " + laptop + " -> Prezzo Finale: " + laptop.calcolaPrezzoFinale());
        System.out.println("  " + mouse + " -> Prezzo Finale: " + mouse.calcolaPrezzoFinale());
        System.out.println("  " + consulenza + " -> Prezzo Finale: " + consulenza.calcolaPrezzoFinale());
        System.out.println("  " + installazione + " -> Prezzo Finale: " + installazione.calcolaPrezzoFinale());

        // 3. Aggiungi articoli al carrello
        try {
            System.out.println("\nAggiungo 1 Laptop...");
            carrello.aggiungiArticolo(laptop, 1);
            System.out.println("Numero righe: " + carrello.getNumeroRighe() + ", Totale: " + carrello.calcolaTotale()); 

            System.out.println("Aggiungo 2 Mouse...");
            carrello.aggiungiArticolo(mouse, 2);
            System.out.println("Numero righe: " + carrello.getNumeroRighe() + ", Totale: " + carrello.calcolaTotale());

            System.out.println("Aggiungo 1 Consulenza...");
            carrello.aggiungiArticolo(consulenza, 1);
            System.out.println("Numero righe: " + carrello.getNumeroRighe() + ", Totale: " + carrello.calcolaTotale());

            System.out.println("Aggiungo un altro Laptop (incrementa quantità)...");
            carrello.aggiungiArticolo(laptop, 1);
            System.out.println("Numero righe: " + carrello.getNumeroRighe() + ", Totale: " + carrello.calcolaTotale());

        } catch (Exception e) {
            System.err.println("Errore aggiunta articolo: " + e.getMessage());
        }

        // 5. Modifica quantità
        try {
            System.out.println("\nModifico quantità Mouse a 3...");
            carrello.modificaQuantita(mouse.getCodiceArticolo(), 3);
            System.out.println("Numero righe: " + carrello.getNumeroRighe() + ", Totale: " + carrello.calcolaTotale());
        } catch (ArticoloNonTrovatoException | IllegalArgumentException e) {
            System.err.println("Errore modifica quantità: " + e.getMessage());
        }

        // 6. Rimuovi articolo
        try {
            System.out.println("\nRimuovo Consulenza...");
            carrello.rimuoviArticolo(consulenza.getCodiceArticolo());
            System.out.println("Numero righe: " + carrello.getNumeroRighe() + ", Totale: " + carrello.calcolaTotale());
        } catch (ArticoloNonTrovatoException e) {
            System.err.println("Errore rimozione articolo: " + e.getMessage());
        }

        // 7. Test eccezioni
        System.out.println("\nTest eccezioni:");
        try {
            System.out.print("  Aggiunta con quantità 0: ");
            carrello.aggiungiArticolo(installazione, 0);
        } catch (IllegalArgumentException e) {
            System.out.println("OK -> " + e.getMessage());
        }
        try {
            System.out.print("  Rimozione articolo inesistente (SRV999): ");
            carrello.rimuoviArticolo("SRV999");
        } catch (ArticoloNonTrovatoException e) {
            System.out.println("OK -> " + e.getMessage());
        }
        try {
            System.out.print("  Modifica quantità articolo inesistente (SRV999): ");
            carrello.modificaQuantita("SRV999", 1);
        } catch (ArticoloNonTrovatoException e) {
            System.out.println("OK -> " + e.getMessage());
        }
        try {
            System.out.print("  Modifica quantità a 0: ");
            carrello.modificaQuantita(laptop.getCodiceArticolo(), 0);
        } catch (IllegalArgumentException e) {
            System.out.println("OK -> " + e.getMessage());
        }

        // 8. Filtra articoli per tipo
        System.out.println("\nArticoli nel carrello per tipo:");
        ArticoloVendibile[] prodottiFisici = carrello.getProdottiFisiciNelCarrello();
        System.out.println("  Prodotti Fisici (" + prodottiFisici.length + "):");
        for (ArticoloVendibile vendibile : prodottiFisici) {
            System.out.println("    - " + vendibile.getNome());
        }

        ArticoloVendibile[] servizi = carrello.getServiziNelCarrello();
        System.out.println("  Servizi (" + servizi.length + "):");
        for (ArticoloVendibile articoloVendibile : servizi) {
            System.out.println("    - " + articoloVendibile.getNome());
        }

        System.out.println("\nTotale finale carrello: " + carrello.calcolaTotale());
        System.out.println("--- Fine Test Gestione Carrello ---");
    }
}