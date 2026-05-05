package it.unipr.fdpb.es6;

import it.unipr.fdpb.es5.Prodotto;

public class ListP {

	private ElemP list;
	private int n;
	
	public ListP() {
		this.list = null;
		this.n = 0;
	}
	
	public int size() {
		return n;
	}
	
	public void addFirst(Prodotto p) {
		ElemP newElem = new ElemP(p,list);
		this.list = newElem;
		n++;
	}
	
	public void addLast(Prodotto p) {
		if (list == null)
			addFirst(p);
		else {
			ElemP tmp = list;
			ElemP newElem = new ElemP(p);
			n++;
			while (tmp.getNext() != null)
				tmp = tmp.getNext();
			
			tmp.setNext(newElem);
		}
	}
	
	public boolean contains(Prodotto p) {
		ElemP tmp = list;
		while (tmp.getNext() != null)
			if (tmp.getValue() == p)
				return true;
			else
				tmp = tmp.getNext();
		if (tmp.getValue() == p)
			return true;
		return false;
	}
	
	public Prodotto removeFirst() {
		if (list == null)
			throw new RuntimeException();
		
		Prodotto v = list.getValue();
		list = list.getNext();
		n--;
		
		return v;
	}
	
	public ElemP getHead() {
		return list;
	}
	
	@Override
	public String toString() {
		String result = "[";
		ElemP copy = list;
		while (copy != null) {
			result += copy.getValue().toString();
			if (copy.getNext() != null)
				result += "\n";
			copy = copy.getNext();
		}
		
		return result + "]";
	}
	
	
}
