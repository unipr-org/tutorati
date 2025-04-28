package it.unipr.fdpb.lecture04.es03;

public class ArticoloNonTrovatoException extends RuntimeException {
    public ArticoloNonTrovatoException(String message) {
        super(message);
    }
}