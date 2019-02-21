import java.util.*;

public class Exercicio814{
	public static void main (String[] args){
		Date data = new Date();
		Scanner input = new Scanner(System.in);

		int d, m, y;

		d = input.nextInt();
		m = input.nextInt();
		y = input.nextInt();

		data.setDate(d,m,y);

		data.convertToAmericanFormat();

		data.convertToUniversalFormat();

		data.convertToThirdFormat();

	}
}

class Date{
	private int date;
	private int month;
	private String mes;
	private int year;

	public void setDate(int date, int month, int year){
		if(date>0 && date<=30){
			this.date = date;
		}else System.out.printf("Dia invalido!\n");

		if(month>0 && month <=12){
			switch(month){
				case 1:
					mes = "January";
					break;
				case 2:
					mes = "February";
					break;
				case 3:
					mes = "March";
					break;
				case 4:
					mes = "April";
					break;
				case 5:
					mes = "May";
					break;
				case 6:
					mes = "June";
					break;
				case 7:
					mes = "July";
					break;
				case 8:
					mes = "August";
					break;
				case 9:
					mes = "September";
					break;
				case 10:
					mes = "October";
					break;
				case 11:
					mes = "November";
					break;
				case 12:
					mes = "December";
					break;
			}
			this.month = month;
		}else System.out.printf("Mês invalido!\n");

		if(year>=0){
			this.year = year;
		}else System.out.printf("Ano invalido!\n");			
	}

	public void convertToAmericanFormat(){
		System.out.printf("%02d/%02d/%d\n",date, month, year);
	}

	public void convertToUniversalFormat(){
		System.out.printf("%s %02d, %d\n", mes, date, year);
		
	}
	public void convertToThirdFormat(){
		System.out.printf("%03d %d\n",date, year);
	}


}
