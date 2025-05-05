package it.unipr.fdpb.lecture05.es02;

public class TaskRipetitivo extends TaskSemplice {
    private int intervalloGiorni;

    public TaskRipetitivo(int priorita, String descrizione, String dataScadenzaIniziale, int intervalloGiorni) {
        super(priorita, descrizione, dataScadenzaIniziale);
        this.intervalloGiorni = intervalloGiorni;
    }

    public int getIntervalloGiorni() {
        return intervalloGiorni;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || !(obj instanceof TaskRipetitivo)) return false;

        TaskRipetitivo that = (TaskRipetitivo) obj;
        return intervalloGiorni == that.intervalloGiorni
                && super.equals(obj);
    }

    @Override
    public String toString() {
        return "TaskRipetitivo{" +
                "priorita=" + getPriorita() +
                ", descrizione='" + getDescrizione() + '\'' +
                ", dataScadenza='" + getDataScadenza() + '\'' +
                ", intervalloGiorni=" + intervalloGiorni +
                '}';
    }
}
