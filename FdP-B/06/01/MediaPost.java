package it.unipr.fdpb.lecture06.es01;

import java.time.LocalDateTime;

public abstract class MediaPost extends Post {
    protected String urlMedia;

    public MediaPost(String idPost, Utente autore, LocalDateTime timestamp, String urlMedia) {
        super(idPost, autore, timestamp);
        this.urlMedia = urlMedia;
    }

    public abstract String getUrlMedia();

}
