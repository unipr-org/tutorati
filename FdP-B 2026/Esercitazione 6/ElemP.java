package it.unipr.fdpb.es6;

import it.unipr.fdpb.es5.Prodotto;

public class ElemP {

	private final Prodotto value;
	private ElemP next;
	
	ElemP(Prodotto p){
		this.value = p;
		this.next = null;
	}
	
	ElemP(Prodotto p, ElemP next){
		this.value = p;
		this.next = next;
	}
	
	public ElemP getNext() {
		return next;
	}

	public void setNext(ElemP next) {
		this.next = next;
	}
	
	public Prodotto getValue() {
		return this.value;
	}
}
