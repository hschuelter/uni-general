import java.util.*;

public class Exercicio86{
	public static void main(String[] args){
		SavingsAccount saver1 = new SavingsAccount();
		SavingsAccount saver2 = new SavingsAccount();
		int i;
		double aux1, aux2;

		saver1.setBalance(2000.0);
		saver2.setBalance(3000.0);
		SavingsAccount.modifyInterestRate(4.0);
		
		System.out.printf("\nCom 4%%:\n");
		System.out.printf("Mês: \tSaver1: \tSaver2:\n");
		for(i=1; i<=12; i++){
			aux1 = saver1.calculeMonthlyInterest();
			aux2 = saver2.calculeMonthlyInterest();

			System.out.printf("%02d \t%.3f \t%.3f \n",i,aux1, aux2);
		}

		saver1.setBalance(2000.0);
		saver2.setBalance(3000.0);
		SavingsAccount.modifyInterestRate(5.0);
		
		System.out.printf("\n\nCom 5%%:\n");
		System.out.printf("Mês: \tSaver1: \tSaver2:\n");
		for(i=1; i<=12; i++){
			aux1 = saver1.calculeMonthlyInterest();
			aux2 = saver2.calculeMonthlyInterest();

			System.out.printf("%02d \t%.3f \t%.3f \n",i,aux1, aux2);
		}

		System.out.printf("\n");





	}

}

class SavingsAccount{

	static double annualInterestRate;
	private double savingsBalance;

	public void setBalance(double balance){
		this.savingsBalance = balance;
	}

	public double calculeMonthlyInterest(){
		double interest;

		interest = (savingsBalance*(annualInterestRate/100))/12.0;
		this.savingsBalance += interest;
		return savingsBalance;
	}

	public static void modifyInterestRate(double interest){
		annualInterestRate = interest;
	}
}