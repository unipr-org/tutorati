package list;

public class Main {
	public static void main(String[] args) {
		IntList l1 = new IntList();
		System.out.println(l1);
		
		l1.addFirst(34);
		l1.addFirst(4);
		l1.addFirst(7);
		l1.addFirst(3);
		
		System.out.println(l1);
		
		int x = l1.removeFirst();
		System.out.println(x);
		System.out.println(l1);
		
		l1.addFirst(23);
		System.out.println(l1);
		l1.addLast(98);
		System.out.println(l1);
		
		System.out.println(l1.containsRec(23, l1.getHead()));
	}
}
