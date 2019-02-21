import java.util.*;

public class Exercicio3{
	public static void main(String[] args){
		System.out.printf("Insira três inteiros (A,B,C)\n");
		int a, b, c;

		Scanner input = new Scanner(System.in);
		a = input.nextInt();
		b = input.nextInt();
		c = input.nextInt();

		float media = (float)(a+b+c)/3;

		if(a == b && a == c){
			System.out.printf("A, B e C são iguais\n");
		}else{
			if(a <= b && a <= c) System.out.printf("%d é o menor\n", a);
			else if(b <= c && b <= a) System.out.printf("%d é o menor\n", b);
			else if(c <= a && c <= b) System.out.printf("%d é o menor\n", c);
		
			if(a >= b && a >= c) System.out.printf("%d é o maior\n", a);
			else if(b >= c && b >= a) System.out.printf("%d é o maior\n", b);
			else if(c >= a && c >= b) System.out.printf("%d é o maior\n", c);
		}

		System.out.printf("O produto é: %d\n", a*b*c);
		System.out.printf("A soma é: %d\n", a+b+c);
		System.out.printf("A média é: %f\n\n", media);
	}
}