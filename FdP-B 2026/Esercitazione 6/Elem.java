package list;

class Elem {
	private final int value;
	private Elem next;
	
	Elem() {
		value = 0;
		next = null;
	}
	
	Elem(int x) {
		this(x, null);
	}
	
	Elem(int value, Elem next) {
		this.value = value;
		this.next = next;
	}

	public Elem getNext() {
		return next;
	}

	public void setNext(Elem next) {
		this.next = next;
	}

	public int getValue() {
		return value;
	}
	
	
	
}
