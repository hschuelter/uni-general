import java.util.*;

public class Exercicio712{
	public static void main(String[] args){		
		Scanner input = new Scanner(System.in);
		int[] vet = new int[5];
		int i=0,j=0,aux=0,flag=0;
		int cont=0;

		vet[0] = input.nextInt();
		cont++;

		for(i=1; i<5; i++){
			aux = input.nextInt();

			while(j<cont){
				if(vet[j] == aux){
					flag++;
				}
				j++;
			}
			j=0;

			if(flag==0){
				vet[cont] = aux;
				cont++;
			}
			flag =0;
		}
		System.out.printf("O vetor é:\n");
		for(i=0; i< cont; i++){
			System.out.printf("\t%d\n", vet[i]);
		}

	}
}