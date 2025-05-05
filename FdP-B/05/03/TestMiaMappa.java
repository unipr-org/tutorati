package it.unipr.fdpb.lecture05.es03;

public class TestMiaMappa {

    public static void main(String[] args) {
        System.out.println("--- Test Implementazione Mappa Generica ---");

        Mappa<String, Integer> mappaEta = new MiaMappa<>();
        System.out.println("Mappa creata. Vuota? " + mappaEta.isEmpty() + ", Size: " + mappaEta.size());

        System.out.println("\nAggiungo elementi...");
        mappaEta.put("Mario", 30);
        mappaEta.put("Anna", 25);
        mappaEta.put("Luca", 35);
        System.out.println("Mappa dopo aggiunte: " + mappaEta);
        System.out.println("Size: " + mappaEta.size());

        System.out.println("\nAggiorno eta' di Mario...");
        mappaEta.put("Mario", 31);
        System.out.println("Mappa dopo aggiornamento: " + mappaEta);

        System.out.println("\nRecupero eta':");
        System.out.println("  Eta' di Anna: " + mappaEta.get("Anna"));
        System.out.println("  Eta' di Paolo (inesistente): " + mappaEta.get("Paolo"));

        System.out.println("\nVerifica presenza chiavi:");
        System.out.println("  Contiene 'Luca'? " + mappaEta.containsKey("Luca"));
        System.out.println("  Contiene 'Paolo'? " + mappaEta.containsKey("Paolo"));

        System.out.println("\nRimuovo 'Anna'...");
        Integer etaRimossa = mappaEta.remove("Anna");
        System.out.println("  Eta' rimossa: " + etaRimossa);
        System.out.println("Mappa dopo rimozione: " + mappaEta);
        System.out.println("Size: " + mappaEta.size());

        System.out.println("Rimuovo 'Anna' (di nuovo)...");
        etaRimossa = mappaEta.remove("Anna");
        System.out.println("  Eta' rimossa: " + etaRimossa);

        System.out.println("\nAggiungo altri elementi...");
        mappaEta.put("Giulia", 28);
        mappaEta.put("Marco", 40);
        System.out.println("Mappa finale: " + mappaEta);
        System.out.println("Size finale: " + mappaEta.size());
        System.out.println("Vuota? " + mappaEta.isEmpty());

        System.out.println("\n--- Fine Test Implementazione Mappa ---");
    }
}