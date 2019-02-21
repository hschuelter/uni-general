/*
	Enquanto a entrada for 1
		se o numero de horas for maior que 40
			calcula a hora extra
		senao
			calcula o salario sem hora extra

		printa o numero do empregado com o salario

		mensagem para continuar (1 sim, 0 não)

*/

import java.util.*;

public class salario{

	public static void main(String[] args){

		int horas, i, j;
		double salario, total;
		Scanner input = new Scanner(System.in);
		total = 0;
		i = 1;
		j = 1;
		while(i == 1){
			System.out.printf("Coloque o numero de horas trabalhadas: ");
			horas = input.nextInt();
			System.out.printf("Coloque o salario: ");
			salario = input.nextDouble();

			if(horas > 40){
				total  = (40*salario) + (horas-40)*1.5*salario;
			} else {
				total = horas*salario;
			}

			System.out.printf("O empregado %d recebeu: %.2f\n", j, total);
			j++;

			System.out.printf("Deseja continuar?(1 para sim/ 0 para não!)");
			i = input.nextInt();
		}

	}
}