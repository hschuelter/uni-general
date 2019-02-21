import java.util.*;

public class Comparador1{
	 public static void main(String[] args){
	 	int a, b;
	 	Scanner input = new Scanner(System.in);
	 	a = input.nextInt();
	 	b = input.nextInt();
	 	if(a > b)
	 		System.out.printf("%d is larger\n", a);
	 	else if(b > a)
	 		System.out.printf("%d is larger\n", b);
	 	else 
	 		System.out.printf("These numbers are equal\n");
	 }
}