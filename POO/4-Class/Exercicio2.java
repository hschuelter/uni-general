import java.util.*;

public class Exercicio2{

	public static class ContarImpares {
		private int resultado;
		private int comeco;
		private int fim;

		public void setComeco(int com){
			this.comeco = com;
		}
		public void setFim(int fim){
			this.fim = fim;
		}
		public int getResultado(){
			return this.resultado;
		}
		public void solve(){
			this.resultado = 1;
			for(int i = this.comeco; i <= this.fim; i++){
				if(i % 2 != 0){
					this.resultado *= i;
				}
			}
		}

	}

	public static void main(String[] args) {

		ContarImpares p = new ContarImpares();

		p.setComeco(1);
		p.setFim(15);
		p.solve();

		System.out.printf("O produto é: %d\n", p.getResultado());



	}

}
