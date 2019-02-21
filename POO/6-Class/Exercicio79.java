import java.util.*;

public class Exercicio79{

	
	public static void main(String[] args){

		// 7.9 - a) 
		int[][] t = new int[2][3]; 
		int i=0; int j=0;
		Scanner s = new Scanner(System.in);

		// 7.9 - e)
		while(i<3){

			System.out.printf("Elemendo da 1ª linha e %dª coluna: %d\n", i, t[0][i]);
			i++;
		}

		// 7.9 - f)
		i=0;
		while(i<3){

			System.out.printf("Elemendo da 2ª linha e %dª coluna: %d\n", i, t[0][i]); 
			i++;
		}

		// 7.9 - g)
		t[0][1] = 0; 


		//7.9 - h)
		t[0][0] = 0;
		t[0][1] = 0;
		t[0][2] = 0;
		t[1][0] = 0;
		t[1][1] = 0;
		t[1][2] = 0;

		//7.9 - i)

		for( i=0; i<2; i++){
			for(j=0; j<3; j++){
				t[i][j] = 0;
			}
		}

		//7.9 - j)

		for( i=0; i<2; i++){
			for(j=0; j<3; j++){
				t[i][j] = s.nextInt();
			}
		}

		//7.9 - k)
		int aux;
		aux = t[0][0];

		for( i=0; i<2; i++){
			for(j=0; j<3; j++){

				if(aux > t[i][j]){
					aux = t[i][j];
				}				
			}
		}
		System.out.printf("O menor é: %d\n\n", aux);

		//7.9 - l)

		System.out.printf("Primeira linha: {%d, %d, %d}\n\n",t[0][0], t[0][1], t[0][2]);


		//7.9 - m)

		int somaTerceira=0;

		somaTerceira = t[0][2] + t[1][2];

		System.out.printf("Soma da terceira coluna: %d\n\n", somaTerceira);

		//7.9 - n)

		System.out.printf("       TODOS OS ELEMENTOS\n\n");

		System.out.printf("\tCol 0\tCol 1\tCol 2\n");
		System.out.printf("      ------------------------\n");

		for(i=0;i<2;i++){
			System.out.printf("Lin %d|",i);
			for(j=0; j<3;j++){
				System.out.printf("\t%d", t[i][j]);
			}
			System.out.printf("\n");

		}




	}
}


/*
b) Duas Linhas

c) Três Colunas

d) Seis elementos

*/



