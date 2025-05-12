package it.unipr.fdpb.lecture06.es02;

public class Quiz extends MaterialeDidattico {
    private int numeroDomande;
    private int tempoLimiteMinuti;

    public Quiz(String titolo, String idMateriale, int numeroDomande, int tempoLimiteMinuti) {
        super(titolo, idMateriale);
        this.numeroDomande = numeroDomande;
        this.tempoLimiteMinuti = tempoLimiteMinuti;
    }

    public int getNumeroDomande() {
        return numeroDomande;
    }

    @Override
    public int getDurataStimataMinuti() {
        return tempoLimiteMinuti;
    }

    @Override
    public String toString() {
        return "Quiz{" +
                "titolo='" + titolo + '\'' +
                ", id='" + idMateriale + '\'' +
                ", domande=" + numeroDomande +
                ", minuti=" + tempoLimiteMinuti +
                '}';
    }
}