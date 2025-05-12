package it.unipr.fdpb.lecture06.es01;

import java.time.LocalDateTime;

public class TextPost extends Post {
    private String testo;

    public TextPost(String idPost, Utente autore, LocalDateTime timestamp, String testo) {
        super(idPost, autore, timestamp);
        this.testo = testo;
    }

    @Override
    public String getContenutoTestuale() {
        return testo;
    }

    @Override
    public String toString() {
        return super.toString() + " [Text: \"" + testo + "\"]";
    }
}
