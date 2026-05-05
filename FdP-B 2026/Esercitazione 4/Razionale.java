package r;

import java.util.Scanner;

public class Razionale {

	private int n;
	private int d;
	
	private boolean denominatoreValido (int a) {
		if(a > 0) {
			return true;
		}
		return false;
	}
	
	private void semplifica() {
		// Algoritmo di Euclide
		int a,b,resto;
		
		a = this.n;
		b = this.d;
		
		while(b != 0) {
			resto = a % b;
			a = b;
			b = resto;
		}
		
		this.n = this.n/a;
		this.d = this.d/a;
		
	}
	
	public Razionale(){
		this.n = 0;
		this.d = 1;
	}
	
	public Razionale(int n, int d){
		if(denominatoreValido(d) && n != 0) {
			this.d = d;
			this.n = n;
			this.semplifica();
		} else {
			if(n != 0) {
				System.out.println("Denominatore non valido, imposto valore di default!!");
			}
			this.n = 0;
			this.d = 1;
		}
	}
	
	public void leggi() {
		int x,y;
		
		System.out.println("Inserisci numeratore: ");
		Scanner sc = new Scanner(System.in);
		x = sc.nextInt();
		System.out.println("Inserisci denominatore: ");
		y = sc.nextInt();
		
		if(denominatoreValido(y) && x != 0) {
			this.n = x;
			this.d = y;
			this.semplifica();
		} else {
			if(x != 0) {
				System.out.println("Denominatore non valido, imposto valore di default!!");
			}
			this.n = 0;
			this.d = 1;
		}
		
		sc.close();
		
	}
	
	public void stampa(){
		if(this.d == 1) {
			System.out.println(this.n);
		} else {
			System.out.println(this.n + "/" + this.d);

		}
	}
	
	public Razionale somma(Razionale other){
		
		int num,den;
		
		Razionale res;
		
		if(this.n == 0) {
			return other;
		}
		
		if(other.n == 0) {
			return this;
		}
		
		if(this.d == other.d){
			res = new Razionale(this.n + other.n, this.d);
		} else {
			num = (this.n * other.d) + (other.n * this.d);
			den = this.d * other.d;
			res = new Razionale(num,den);
			// res = new Razionale((this.n * other.d) + (other.n * this.d), this.d * other.d);
		}
		return res;	
	}
	
	public static void main(String[] args) {
		
		Razionale r1 = new Razionale();
		
		r1.leggi();
		r1.stampa();
		
		Razionale r2 = new Razionale(4,7);
		
		Razionale r3 = r1.somma(r2);
		r3.stampa();
	}
	
}
