package it.unipr.fdpb.es10;

public class Registro {

	private Iscrizione[] container;
	private int size;
	private int capacity;
	
	private void enlarge() {
		capacity *= 2;
		Iscrizione[] aux = new Iscrizione[capacity];
		for(int i = 0; i < size; i++) {
			aux[i] = container[i];
		}
		container = aux;
	}
	
	public Registro() {
		capacity = 5;
		size = 0;
		container = new Iscrizione[capacity];
	}
	
	public void add(Iscrizione other) {
		if(size == capacity) {
			enlarge();
		}
		for(int i = 0; i < size; i++) {
			if(container[i].getUtente().equals(other.getUtente()) && container[i].overlapsWith(other)) {
				throw new IscrizioneNonControllataException("Iscrizione sovrapposta!");
			}
		}
		container[size++] = other;
	}
	
	public Registro project(int anno) {
		
		Registro res = new Registro();
		
		for(int i = 0; i < size; i++) {
			if(container[i].getAnnoF() == anno || container[i].getAnnoI() == anno)
				res.add(container[i]);
		}
		
		return res;
	}
}
