package it.unipr.fdpb.lecture06.es01;

import java.time.LocalDateTime;

public class VideoPost extends MediaPost {
    private int durataSecondi;

    public VideoPost(String idPost, Utente autore, LocalDateTime timestamp, String urlVideo, int durataSecondi) {
        super(idPost, autore, timestamp, urlVideo);
        this.durataSecondi = durataSecondi;
    }

    public int getDurataSecondi() {
        return durataSecondi;
    }

    @Override
    public String getUrlMedia() {
        return "[Video: " + super.urlMedia + " (" + durataSecondi + "s)]";
    }

    @Override
    public String getContenutoTestuale() {
        return "[Video: " + super.urlMedia + " (" + durataSecondi + "s)]";
    }

    @Override
    public String toString() {
        return super.toString() + " [" + getContenutoTestuale() + "]";
    }
}