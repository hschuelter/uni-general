import java.util.*;

public class Exercicio5{
	public static void main(String[] args){
		Scanner input = new Scanner(System.in);
		int n;

		n = input.nextInt();

		if(n%2 == 0)
			System.out.printf("O número é par\n");
		else
			System.out.printf("O número é ímpar\n");
	}
}