import java.util.*;

public class Exercicio68{

	public  static double calculaCharges(int ti){
		double tarifa;
		int adi;

		if(ti>3){
			adi = ti - 3
;		}else{
			adi = 0;
		}

		tarifa = 2.00 + (adi*0.5);

		if(tarifa > 10){
			tarifa = 10;
		}

		return tarifa;
	}

	public static void main(String[] args){
		double tari;
		int tempo, num,i;
		Scanner input = new Scanner(System.in);
		tari = 2.00;
		i=0;

		
		System.out.printf("Digite o número de clientes:\n");
		num = input.nextInt();
		while(i<num){
			System.out.printf("Digite quantas horas o Cliente %d ficou estacionado:\n", i);
			tempo = input.nextInt();

			tari = calculaCharges(tempo);

			System.out.printf("O Cliente: %d ficou %d horas e deve: R$ %.2f\n",i++, tempo, tari);
		}

	}
}