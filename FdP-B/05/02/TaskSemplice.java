package it.unipr.fdpb.lecture05.es02;

public class TaskSemplice implements Task, Comparable<TaskSemplice> {
    private int priorita;
    private String descrizione;
    private String dataScadenza;

    public TaskSemplice(int priorita, String descrizione, String dataScadenza) {
        this.priorita = priorita;
        this.descrizione = descrizione;
        this.dataScadenza = dataScadenza;
    }

    @Override
    public int getPriorita() {
        return priorita;
    }

    @Override
    public String getDescrizione() {
        return descrizione;
    }

    @Override
    public String getDataScadenza() {
        return dataScadenza;
    }

    @Override
    public int compareTo(TaskSemplice other) {
        if (this.priorita != other.priorita) {
            return Integer.compare(other.priorita, this.priorita);
        }

        // GG/MM/AAAA
        String[] thisDateParts = this.dataScadenza.split("/");
        String[] otherDateParts = other.dataScadenza.split("/");

        if (thisDateParts.length != 3 || otherDateParts.length != 3) {
            throw new IllegalArgumentException("Formato data non valido per confronto: " + this.dataScadenza + " o " + other.dataScadenza);
        }

        try {
            int thisYear = Integer.parseInt(thisDateParts[2]);
            int otherYear = Integer.parseInt(otherDateParts[2]);
            if (thisYear != otherYear) {
                return Integer.compare(thisYear, otherYear);
            }

            int thisMonth = Integer.parseInt(thisDateParts[1]);
            int otherMonth = Integer.parseInt(otherDateParts[1]);
            if (thisMonth != otherMonth) {
                return Integer.compare(thisMonth, otherMonth);
            }

            int thisDay = Integer.parseInt(thisDateParts[0]);
            int otherDay = Integer.parseInt(otherDateParts[0]);
            return Integer.compare(thisDay, otherDay);

        } catch (NumberFormatException e) {
            throw new IllegalArgumentException("Componenti data non numerici: " + this.dataScadenza + " o " + other.dataScadenza);
        }
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj)
            return true;
        if (obj == null || getClass() != obj.getClass())
            return false;
        TaskSemplice that = (TaskSemplice) obj;
        return priorita == that.priorita
                && descrizione.equals(that.descrizione)
                && dataScadenza.equals(that.dataScadenza);
    }

    @Override
    public String toString() {
        return "TaskSemplice{" +
                "priorita=" + priorita +
                ", descrizione='" + descrizione + '\'' +
                ", dataScadenza='" + dataScadenza + '\'' +
                '}';
    }
}
