import java.util.*;

public class Exercicio3{
	
	public static void main(String[] args){
		int i, n;
		long resultado = 1;
		Scanner input = new Scanner(System.in);
		
		System.out.printf("Escreva o fatorial:\n");
		n = input.nextInt();

		System.out.printf("n: \t\t Fatorial:\n");

		for(i=1; i<=n;i++){
			resultado *= i;
			System.out.printf("%d \t\t %d\n", i, resultado);
		} 
	}

}