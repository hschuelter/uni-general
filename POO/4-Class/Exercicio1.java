import java.util.*;

public class Exercicio1{
	
	public static void main(String[] args){
		int i, aux, leitor, num;
		Scanner input = new Scanner(System.in);

		System.out.printf("Insira o numero de inteiros:\n");
		num = input.nextInt();

		aux = 0;
		i = 0;

		while(i<num){
			System.out.printf("Escreva o %dº inteiro:\n", i+1);
			leitor = input.nextInt();

			if(i==0){
				aux = leitor;
			} else if(leitor < aux){
				aux = leitor;
			}

			i++;
		}

		System.out.printf("O menor é: %d\n",aux);
	}

}