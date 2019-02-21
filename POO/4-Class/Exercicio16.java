import java.util.*;

public class Exercicio16{

	public static void main(String[] args){
		int a,b,c,d,e;
		int i = 0;
		Scanner input = new Scanner(System.in);

		System.out.printf("Escreva os cinco numeros:\n");
		a = input.nextInt();
		b = input.nextInt();
		c = input.nextInt();
		d = input.nextInt();
		e = input.nextInt();

		
		System.out.printf("Palavra 1:\n");
		for(i=0;i<a;i++){
			System.out.printf("*");
		}
		System.out.printf("\n Palavra 2:\n");

		for(i=0;i<b;i++){
			System.out.printf("*");
		}
		System.out.printf("\n Palavra 3:\n");

		for(i=0;i<c;i++){
			System.out.printf("*");
		}
		System.out.printf("\n Palavra 4:\n");

		for(i=0;i<d;i++){
			System.out.printf("*");
		}
		System.out.printf("\n Palavra 5:\n");

		for(i=0;i<e;i++){
			System.out.printf("*");
		}

		System.out.printf("\n");




	}
}