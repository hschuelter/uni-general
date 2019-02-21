import java.util.*;

public class Account_Test {

	public static void main(String[] args){
		Account teste = new Account();

		teste.setName("Felipe Weiss");
		System.out.println(teste.getName());

		teste.setBalance(1500.00);

		System.out.println(teste.getBalance());

		teste.withdraw(1800.00);

		System.out.println(teste.getBalance());

		teste.withdraw(530.00);

		System.out.println(teste.getBalance());


	}

}