/* Enquanto a entrada não for -1
		se a operação desejada for 1, soma o item 1 ao total;
		se a operação desejada for 2, soma o item 2 ao total;
		...
		...
		...

   printa 9% do total + salario fixo de R$200
*/
import java.util.*;

public class empresa{
	public static void main(String[] args){
		double item1, item2, item3, item4;
		int aux;
		item1 = 239.99;
		item2 = 129.75;
		item3 = 99.95;
		item4 = 350.89;

		Scanner s = new Scanner(System.in);
		int num = 0;
		double total = 0;
		while(true){
			System.out.printf("Digite o item vendido pelo vendedor (0 para sair): ");
			num = s.nextInt();
			num -= 1;
			if(num == -1) break;
			System.out.printf("Quandos do item %d foram vendidos: ", num+1);
			aux = s.nextInt();
			switch(num){
				case 0:
					total += aux *  item1;
					break;
				case 1:
					total += aux * item2;
					break;
				case 2:
					total += aux * item3;
					break;
				case 3:
					total += aux * item4;
					break;
			}
		}
		System.out.printf("\nO salário é: %.2f\n", 200 + ((9.0/100)*total));
	}
}