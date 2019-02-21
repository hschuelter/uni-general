import java.util.*;

public class Exercicio614{
	
	public static int integerPower(int base, int exp){

		if(exp == 0){
			return 1;
		}
		else if(exp == 1){
			return base;
		}
		else{
			return base*integerPower(base, exp-1);
		}
	}

	public static void main(String[] args){

		Scanner input = new Scanner(System.in);
		int b, e, valor;

		System.out.printf("Escreva a base:\n");
		b = input.nextInt();
		System.out.printf("Escreva o expoente:\n");
		e = input.nextInt();

		valor = integerPower(b,e);

		System.out.printf("O valor é: %d\n", valor);	

	}
}