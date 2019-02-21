import java.util.*;

public class Exercicio617{
	
	public static boolean isEven(int num){
		int mod;
		mod = num%2;
		if(mod == 0){
			return true;
		}else{
			return false;
		}
	}

	public static void main(String[] args){
		Scanner input = new Scanner(System.in);
		
		System.out.printf("Digite um numero: ");

		int num;
		boolean s;

		num = input.nextInt();

		s = isEven(num);

		if(s == true){
			System.out.printf("PAR\n");
		}else{
			System.out.printf("IMPAR\n");
		}

	}
}