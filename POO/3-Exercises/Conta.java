import java.util.*;

public class Conta{
	public static void main(String[] args){
		int numeroConta;
		double saldo, credito, limite, aux;
		Scanner s = new Scanner(System.in);

		System.out.printf("Cadastro novo cliente:\n");
		System.out.printf("Numero da conta: ");
		numeroConta = s.nextInt();
		System.out.printf("Saldo: ");
		saldo = s.nextDouble();
		System.out.printf("Limite: ");
		limite = s.nextDouble();

		int operation = 0;
		while(operation != 4){
			System.out.printf("\n________________________________________\n(1) Depósito\n(2) Saque\n(3) Extrato\n(4) Sair\n");
			operation = s.nextInt();

			switch(operation){
				case 1:
					System.out.printf("Digite o valor a ser depositado: ");
					aux = s.nextDouble();
					saldo += aux;
					System.out.printf("O novo saldo é: %.2f\n", saldo);
					break;

				case 2:
					System.out.printf("Digite o valor a ser sacado: ");
					aux = s.nextDouble();
					if(aux > limite)
						System.out.printf("O limite foi excedido\n");
					else if(saldo - aux >= 0){
						saldo -= aux;
						System.out.printf("Foi sacado %.2f. Seu novo saldo é %.2f\n", aux, saldo);
					}else
						System.out.printf("Impossível realizar o saque\n");
					break;

				case 3:
					System.out.printf("Número da conta: %d\nSaldo: %.2f\nLimite: %.2f\n", numeroConta, saldo, limite);

				default: break;
			}
		}


	}
}