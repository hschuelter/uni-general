import java.util.*;

public class Employee_Test {

	public static void main(String[] args){

		Employee a = new Employee("Tuca", "Schuelter", 3150.00);
		Employee b = new Employee("Felipe", "Weiss", 1200.00);

		System.out.println(a.getNome() + " " + a.getSobrenome() + " recebe anualmente: R$" + a.getSalario()*12 + "0");
		System.out.println(b.getNome() + " " + b.getSobrenome() + " recebe anualmente: R$" + b.getSalario()*12 + "0");

		a.setSalario(a.getSalario() * 1.1);
		b.setSalario(b.getSalario() * 1.1);

		System.out.println();

		System.out.printf("%s %s recebe - apos aumento - anualmente: R$ %.2f\n", a.getNome(), a.getSobrenome(), a.getSalario() * 12);
		System.out.println(b.getNome() + " " + b.getSobrenome() + " recebe - apos aumento - anualmente: R$" + b.getSalario()*12 + "0");


	}

}