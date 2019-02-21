public class mystery{
	public static void main(String[] args){
		int x = 1;
		int total = 0;

		while(x <= 10){
			int y = x * x;
			System.out.printf("%d\n", y);
			total += y;
			++x;
		}

		System.out.printf("Total is %d\n", total);
	}
}
/* A função Mystery imprime os quadrados de 1 a 10 
 e depois realiza a soma deles.*/