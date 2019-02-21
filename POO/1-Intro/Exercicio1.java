import java.util.*;


public class Welcome1{
	public static void main(String[] args){
		Scanner input = new Scanner(System.in);
		
		int numero1;
		int numero2;
		int soma, dif, prod, quo;

		System.out.println("Digite o primeiro numero:");
		numero1 = input.nextInt();

		System.out.println("Digite o segundo numero:");
		numero2 = input.nextInt();

		soma = numero1 + numero2;
		dif = numero1 - numero2;
		prod = numero1*numero2;
		quo = numero1 % numero2;

		System.out.printf("A soma eh %d%n",soma);
		System.out.printf("A diferenca eh %d%n",dif);
		System.out.printf("O produto eh %d%n",prod);
		System.out.printf("O quociente eh %d%n",quo);
	}
}