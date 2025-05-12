package it.unipr.fdpb.lecture06.es01;

import java.time.LocalDateTime;

public abstract class Post implements Comparable<Post> {
    protected String idPost;
    protected Utente autore;
    protected LocalDateTime timestamp;

    public Post(String idPost, Utente autore, LocalDateTime timestamp) {
        this.idPost = idPost;
        this.autore = autore;
        this.timestamp = timestamp;
    }

    public String getIdPost() {
        return idPost;
    }

    public Utente getAutore() {
        return autore;
    }

    public LocalDateTime getTimestamp() {
        return timestamp;
    }

    public abstract String getContenutoTestuale();

    @Override
    public int compareTo(Post other) {
        return other.timestamp.compareTo(this.timestamp);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || !(o instanceof Post)) return false;
        Post post = (Post) o;
        return idPost.equals(post.idPost);
    }

    @Override
    public int hashCode() {
        return idPost.hashCode();
    }

    @Override
    public String toString() {
        return "Post{" +
                "id='" + idPost + '\'' +
                ", autore=" + autore.getNomeVisualizzato() +
                ", timestamp=" + timestamp +
                '}';
    }
}
