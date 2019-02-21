import java.util.*;

public class Exercicio17{

	public static void main(String[] args){
		int i, prod, quant;
		double prod1, prod2, prod3, prod4, prod5, total;
		Scanner input = new Scanner(System.in);

		prod1 = 2.98;
		prod2 = 4.50;
		prod3 = 9.98;
		prod4 = 4.49;
		prod5 = 6.87;

		total = 0.0;
		System.out.printf("Escreva o numero do produto (ou Ctrl+d para sair):\n");
		while(input.hasNext()){			
			i = input.nextInt();

			switch(i){
				case 1:
					System.out.printf("Escreva a quantidade:\n");
					quant = input.nextInt();
					total += quant*prod1;
					break;

				case 2:
					System.out.printf("Escreva a quantidade:\n");
					quant = input.nextInt();
					total += quant*prod2;
					break;

				case 3:
					System.out.printf("Escreva a quantidade:\n");
					quant = input.nextInt();
					total += quant*prod3;
					break;

				case 4:
					System.out.printf("Escreva a quantidade:\n");
					quant = input.nextInt();
					total += quant*prod4;
					break;

				case 5:
					System.out.printf("Escreva a quantidade:\n");
					quant = input.nextInt();
					total += quant*prod5;
					break;

				default:
					break;
			}
			System.out.printf("Escreva o numero do produto (ou Ctrl+d para sair):\n");
		}

		System.out.printf("O total é: %.2f\n", total);
		

	}
}