import java.util.*;

public class Exercicio4{
	public static void main(String[] args){
		System.out.printf("Insira 5 inteiros\n");
		Scanner input = new Scanner(System.in);
		
		int n1 = input.nextInt();
		int n2 = input.nextInt();
		int n3 = input.nextInt();
		int n4 = input.nextInt();
		int n5 = input.nextInt();

		int auxMaior, auxMenor;
		auxMaior = n1;
		auxMenor = n1;

		if(auxMaior < n2) auxMaior = n2;
		if(auxMenor > n2) auxMenor = n2;

		if(auxMaior < n3) auxMaior = n3;
		if(auxMenor > n3) auxMenor = n3;

		if(auxMaior < n4) auxMaior = n4;
		if(auxMenor > n4) auxMenor = n4;

		if(auxMaior < n5) auxMaior = n5;
		if(auxMenor > n5) auxMenor = n5;

		System.out.printf("O maior é: %d\n", auxMaior);
		System.out.printf("O menor é: %d\n", auxMenor);
	}
}