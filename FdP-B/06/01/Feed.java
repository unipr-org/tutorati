package it.unipr.fdpb.lecture06.es01;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.stream.Collectors;

public class Feed {
    private List<Post> posts;

    public Feed() {
        this.posts = new ArrayList<>();
    }

    public void aggiungiPost(Post p) {
        if (p != null && !this.posts.contains(p)) {
            this.posts.add(p);
            Collections.sort(this.posts); // Mantiene ordinato per timestamp decrescente
        }
    }

    public List<Post> getPostsRecenti(int N) {
        if (N <= 0) {
            return new ArrayList<>();
        }

        List<Post> result = new ArrayList<>();
        int count = 0;
        for (Post p : this.posts) {
            if (count < N)
                result.add(p);
            else
                break;
            count++;
        }
        return result;
    }

    public List<Post> getPostsByAutore(Utente u) {
        if (u == null) {
            return new ArrayList<>();
        }
        List<Post> result = new ArrayList<>();
        for (Post p : this.posts) {
            if (u.equals(p.getAutore())) {
                result.add(p);
            }
        }
        return result;
    }

    public List<Post> getAllPosts() {
        return new ArrayList<>(this.posts);
    }
}
