package it.unipr.fdpb.lecture06.es02;

public abstract class MaterialeDidattico {
    protected String titolo;
    protected String idMateriale;

    public MaterialeDidattico(String titolo, String idMateriale) {
        this.titolo = titolo;
        this.idMateriale = idMateriale;
    }

    public String getTitolo() {
        return titolo;
    }

    public String getIdMateriale() {
        return idMateriale;
    }

    public abstract int getDurataStimataMinuti();

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || !(o instanceof MaterialeDidattico)) return false;
        MaterialeDidattico that = (MaterialeDidattico) o;
        return idMateriale.equals(that.idMateriale);
    }

    @Override
    public int hashCode() {
        return idMateriale.hashCode();
    }

    @Override
    public String toString() {
        return "MaterialeDidattico{" +
                "titolo='" + titolo + '\'' +
                ", id='" + idMateriale + '\'' +
                '}';
    }
}
