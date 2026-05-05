package d;

import java.util.Scanner;

public class Data {

	private int giorno;
	private int mese;
	private int anno;
	
	private boolean valida(int g, int m, int a) {
		
		if(a < 0) {
			return false;
		}
		
		if(m <= 0 || m > 12) {
			return false;
		}
		
		if(g < 1) {
			return false;
		}
		
		switch(m) {
			case 2:
				if(g > 28) {
					return false;
				}
				break;
			case 4:
			case 6:
			case 9:
			case 11:
				if(g > 30){
					return false;
				}
				break;
			default:
				if(g > 31) {
					return false;
				}
				break;
		}
		
		return true;
		
	}
	
	public Data(){
		this.giorno = 1;
		this.mese = 1;
		this.anno = 1970;
	}
	
	public Data(int g, int m, int a){
		
		if(valida(g,m,a)) {
			this.giorno = g;
			this.mese = m;
			this.anno = a;
		} else {
			System.out.println("Data non valida, impostata data di default!!");
			this.giorno = 1;
			this.mese = 1;
			this.anno = 1970;
		}
		
	}
	
	public void leggi(){
		System.out.println("Inserisci 3 numeri:");
		
		Scanner sc = new Scanner(System.in);
		
		int x,y,z;
		
		x = sc.nextInt();
		y = sc.nextInt();
		z = sc.nextInt();
		if(valida(x,y,z)) {
			this.giorno = x;
			this.mese = y;
			this.anno = z;
		} else {
			System.out.println("Data non valida, non modificata!!");
		}
		
		sc.close();
		
	}
	
	public void stampa() {
		System.out.println("Data = " + this.giorno + "/" + this.mese + "/" + this.anno);
	}
	
	
	public static void main(String[] arg){
		
		Data d1 = new Data();
		
		d1.leggi();
		d1.stampa();
		
		Data d2 = new Data(-1,2,2000);
		d2.stampa();
		
	}
	
	
}
