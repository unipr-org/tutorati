package it.unipr.fdpb.lecture06.es02;

public class LezioneVideo extends MaterialeDidattico {
    private String urlVideo;
    private int durataEffettivaMinuti;

    public LezioneVideo(String titolo, String idMateriale, String urlVideo, int durataEffettivaMinuti) {
        super(titolo, idMateriale);
        this.urlVideo = urlVideo;
        this.durataEffettivaMinuti = durataEffettivaMinuti;
    }

    public String getUrlVideo() {
        return urlVideo;
    }

    @Override
    public int getDurataStimataMinuti() {
        return durataEffettivaMinuti;
    }

    @Override
    public String toString() {
        return "LezioneVideo{" +
                "titolo='" + titolo + '\'' +
                ", id='" + idMateriale + '\'' +
                ", url='" + urlVideo + '\'' +
                ", minuti=" + durataEffettivaMinuti +
                '}';
    }
}