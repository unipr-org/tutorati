package it.unipr.fdpb.lecture06.es01;

import java.time.LocalDateTime;
import java.util.List;

public class TestFeed {

    public static void main(String[] args) {
        System.out.println("--- Test Simulatore Feed Social Network ---");

        Utente u1 = new UtenteSemplice("user1", "Alice");
        Utente u2 = new UtenteSemplice("user2", "Bob");

        LocalDateTime now = LocalDateTime.now();

        Post p1 = new TextPost("post1", u1, now.minusHours(2), "Primo post di Alice!");
        Post p2 = new ImagePost("post2", u2, now.minusHours(1), "http://example.com/image.jpg");
        Post p3 = new TextPost("post3", u1, now.minusMinutes(30), "Un altro post da Alice.");
        Post p4 = new VideoPost("post4", u1, now.minusMinutes(10), "http://example.com/video.mp4", 120);
        Post p5 = new TextPost("post5", u2, now.minusMinutes(5), "Ultimo post di Bob.");

        Feed feed = new Feed();
        System.out.println("Aggiungo post al feed...");
        feed.aggiungiPost(p1);
        feed.aggiungiPost(p2);
        feed.aggiungiPost(p3);
        feed.aggiungiPost(p4);
        feed.aggiungiPost(p5);

        System.out.println("\nTutti i post nel feed (ordinati):");
        List<Post> allPosts = feed.getAllPosts();
        for (Post p : allPosts) {
            System.out.println("  " + p.getIdPost() + " by " + p.getAutore().getNomeVisualizzato() + " at " + p.getTimestamp() + " -> " + p.getContenutoTestuale());
        }

        System.out.println("\nPrimi 3 post recenti:");
        List<Post> recentPosts = feed.getPostsRecenti(3);
        for (Post p : recentPosts) {
            System.out.println("  " + p.getIdPost() + " at " + p.getTimestamp());
        }

        System.out.println("\nPost dell'utente Alice (user1):");
        List<Post> alicePosts = feed.getPostsByAutore(u1);
        for (Post p : alicePosts) {
            System.out.println("  " + p.getIdPost() + " -> " + p.getContenutoTestuale());
        }

        System.out.println("\nPost dell'utente Bob (user2):");
        List<Post> bobPosts = feed.getPostsByAutore(u2);
        for (Post p : bobPosts) {
            System.out.println("  " + p.getIdPost() + " -> " + p.getContenutoTestuale());
        }

        System.out.println("\n--- Fine Test Feed ---");
    }
}
