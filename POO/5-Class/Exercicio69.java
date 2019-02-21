import java.util.*;

public class Exercicio69{
	
	public static void main(String[] args){

		Scanner input = new Scanner(System.in);
		double x, y;

		System.out.printf("Escreva o valor que deseja arredondar: ");
		x =input.nextDouble();

		y =Math.floor(x + 0.5);
		System.out.printf("O valor arredondado de %f é %.0f\n\n", x, y);



	}
}