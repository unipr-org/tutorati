package it.unipr.fdpb.lecture05.es01;

public class ProdottoFisico implements Catalogabile {
    private String codiceUnivoco;
    private String descrizione;
    private double valore;
    private double peso;
    private String dimensioni;

    public ProdottoFisico(String codiceUnivoco, String descrizione, double valore, double peso, String dimensioni) {
        this.codiceUnivoco = codiceUnivoco;
        this.descrizione = descrizione;
        this.valore = valore;
        this.peso = peso;
        this.dimensioni = dimensioni;
    }

    @Override
    public String getCodiceUnivoco() {
        return codiceUnivoco;
    }

    @Override
    public String getDescrizione() {
        return descrizione;
    }

    @Override
    public double getValore() {
        return valore;
    }

    public double getPeso() {
        return peso;
    }

    public String getDimensioni() {
        return dimensioni;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || !(obj instanceof ProdottoFisico)) return false;
        ProdottoFisico that = (ProdottoFisico) obj;
        return codiceUnivoco.equals(that.codiceUnivoco);
    }

    @Override
    public String toString() {
        return "ProdottoFisico{" +
                "codiceUnivoco='" + codiceUnivoco + '\'' +
                ", descrizione='" + descrizione + '\'' +
                ", valore=" + valore +
                ", peso=" + peso +
                ", dimensioni='" + dimensioni + '\'' +
                '}';
    }
}