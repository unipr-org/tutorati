package it.unipr.fdpb.lecture03;

public class Magazzino {
    private Prodotto[] data;
    private int size;
    private int capacity;

    public Magazzino(int capacity) {
        if (capacity <= 0)
            throw new RuntimeException("La capacita' non puo essere negativa");

        this.data = new Prodotto[capacity];
        this.size = 0;
        this.capacity = capacity;
    }

    public Magazzino() {
        this(5);
    }

    private void enlarge(){
        int newCapacity = capacity * 2;
        Prodotto[] newData = new Prodotto[newCapacity];

        for (int i = 0; i < size; i++)
            newData[i] = data[i];

        this.data = newData;
        this.capacity = newCapacity;
        System.out.println("Capacita' raddoppiata a " + capacity);
    }

    public int getSize() {
        return this.size;
    }

    public int getCapacity() {
        return this.capacity;
    }

    public void add(Prodotto other) {
        if (size == capacity)
            enlarge();
        data[size++] = other;
    }

    public void remove(Prodotto other) {
        for (int i = 0; i < size; i++) {
            if(data[i].equals(other)) {
                for (int j = i; j < size - 1; j++)
                    data[j] = data[j + 1];
                size--;
                i--;
            }
        }
    }

    public boolean contains(Prodotto other) {
        for (int i = 0; i < size; i++)
            if(data[i].equals(other))
                return true;
        return false;
    }

    public static void main(String[] args) {
        Magazzino magazzino = new Magazzino();

        System.out.println("Size magazzino: " + magazzino.getSize());
        System.out.println("Capacity magazzino: " + magazzino.getCapacity());

        for (int i = 0; i < 9; i++)
            magazzino.add(new Prodotto(i, "Prodotto" + i));

        System.out.println("Size magazzino: " + magazzino.getSize());
        System.out.println("Capacity magazzino: " + magazzino.getCapacity());

        if (magazzino.contains(new Prodotto(1, "Prodotto1")))
            System.out.println("Prodotto1 esiste");

        if (!magazzino.contains(new Prodotto(87, "Prodotto87")))
            System.out.println("Prodotto87 non esiste");

        magazzino.remove(new Prodotto(1, "Prodotto1"));
        System.out.println("Size magazzino: " + magazzino.getSize());
        System.out.println("Capacity magazzino: " + magazzino.getCapacity());
    }
}
