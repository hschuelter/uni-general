import java.util.*;

public class Exercicio625{

	public static boolean isPrime(int num){

		int count=0;

		for(int i = 1;i <= num ; i++){
			if(num%i == 0){
				count++;
			}
		}
		if(count == 2){
			return true;
		}else{
			return false;
		}
	}

	public static void main(String[] args){

		Scanner input = new Scanner(System.in);

		int i=0;
		boolean s;

		System.out.printf("Os primos entre 1 e 10.000: \n");

		for( i=1 ; i<= 10000 ; i++){
			if(isPrime(i) == true){
				System.out.printf("%d\n",i);
			}
		}

		

		

	}

}