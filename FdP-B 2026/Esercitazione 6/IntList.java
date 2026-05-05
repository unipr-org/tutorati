package list;


public class IntList {
	private Elem list;
	private int n;
	
	public IntList() {
		this.list = null;
		this.n = 0;
	}
	
	public int size() {
		return n;
	}
	
	public void addFirst(int x) {
		Elem newElem = new Elem(x, list);
		list = newElem;
		n++;
	}
	
	public int removeFirst() {
		if (list == null)
			throw new RuntimeException();
		
		int v = list.getValue();
		list = list.getNext();
		n--;
		
		return v;
	}
	
	public void addLast(int x) {
		if (list == null)
			addFirst(x);
		else {
			Elem tmp = list;
			Elem newElem = new Elem(x);
			n++;
			while (tmp.getNext() != null)
				tmp = tmp.getNext();
			
			tmp.setNext(newElem);
		}
	}
	
	public boolean contains(int x) {
		Elem tmp = list;
		while (tmp.getNext() != null)
			if (tmp.getValue() == x)
				return true;
			else
				tmp = tmp.getNext();
		if (tmp.getValue() == x)
			return true;
		return false;
	}
	
	public boolean containsRec(int x, Elem other) {
				
		if (other == null)
			return false;
		else if (other.getValue() == x)
			return true;
		else
			return containsRec(x, other.getNext());
		
	}
	
	public int max() {
		if (list == null)
			throw new RuntimeException();
		
		int max = list.getValue();
		Elem copy = list.getNext();
		
		while(copy != null) 
			if (copy.getValue() > max)
				max = copy.getValue();
			else
				copy = copy.getNext();
		
		return max;
	}
	
	public Elem getHead() {
		return list;
	}
	
	public String toString() {
		String result = "[";
		Elem copy = list;
		while (copy != null) {
			result += copy.getValue();
			if (copy.getNext() != null)
				result += ", ";
			copy = copy.getNext();
		}
		
		return result + "]";
	}
	
	
}
