public class Date {
	private int dia;
	private int mes;
	private int ano;

	Date(int d, int m, int a){
		dia = d;
		mes = m;
		ano = a;
	}

	public void setDia(int day){
		dia = day;
	}

	public void setMes(int month){
		mes = month;
	}

	public void setAno(int year){
		ano = year;
	}

	public int getDia(){
		return dia;
	}

	public int getMes(){
		return mes;
	}

	public int getAno(){
		return ano;
	} 

	public void displayDate(){
		if(dia<32 && dia>0){
			if(mes<13 && mes>0){
				if(ano > -1){
					System.out.printf("%d / %d / %d\n",dia, mes, ano);
				}
				else if(ano <0){
					System.out.printf("%d / %d / %d AC\n",dia, mes, -ano);
				}
			}
			else{
				System.out.printf("Data invalida\n");
			}
		}
		else {
			System.out.printf("Data invalida\n");
		}
	}

}