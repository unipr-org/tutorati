package it.unipr.fdpb.lecture06.es01;

import java.time.LocalDateTime;

public class ImagePost extends MediaPost {

    public ImagePost(String idPost, Utente autore, LocalDateTime timestamp, String urlImmagine) {
        super(idPost, autore, timestamp, urlImmagine);
    }

    @Override
    public String getUrlMedia() {
        return "[Immagine: " + super.urlMedia + "]";
    }

    @Override
    public String getContenutoTestuale() {
        return "[Immagine: " + super.urlMedia + "]";
    }

    @Override
    public String toString() {
        return super.toString() + " [" + getContenutoTestuale() + "]";
    }
}
