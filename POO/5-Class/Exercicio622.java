import java.util.*;

public class Exercicio622{
	
	public static double transformaTemperatura(double temperatura, int c){

		if(c == 0){
			return ((9.0/5.0) * temperatura) + 32;
		} else if (c == 1){
			return (5.0/9.0) * (temperatura - 32);
		} else{
			return -10000;
		}

	}


	public static void main(String[] args){
		Scanner input = new Scanner(System.in);
		int tipo;
		double temp;

		System.out.printf("Escreva a temperatura:");
		temp = input.nextDouble();
		System.out.printf("Escreva em que escala está a temperatura (0 para Celsius e 1 para Fahrenheit):");
		tipo = input.nextInt();

		temp = transformaTemperatura(temp, tipo);
		if (temp == -10000){
			System.out.printf("ERROOU\n");
		}else if(tipo == 0){
			System.out.printf("A temperatura é %.2f F\n", temp);
		}else if(tipo == 1){
			System.out.printf("A temperatura é %.2f ºC\n", temp);
		} else{
			System.out.printf("ERROOU\n");
		}

	}
}