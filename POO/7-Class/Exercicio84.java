import java.util.*;

public class Exercicio84{

	public static void main(String[] args){
		double l, w, peri;
		Rectangle rec = new Rectangle();
		Scanner input = new Scanner(System.in);

		System.out.printf("Digite as medidas do retângulo:\n");
		l = input.nextDouble();
		w = input.nextDouble();
		
		rec.setRectangle(l,w);
		
		peri = rec.calculaPerimetro();

		System.out.printf("O perimetro é: %.2f\n", peri);

	}
}

class Rectangle{

	private double length;
	private double width;

	public void setRectangle(double length, double width){
		if(length <= 0 || length >= 20){
			this.length = 1;
			this.width = width;
			return;
		}
		if(width <= 0  || width >= 20){
			this.length = length;
			this.width = 1;
			return;
		}

		this.length = length;
		this.width = width;
	}

	public double calculaPerimetro(){
		return (this.length + this.width)*2;
	}

}