import java.util.*;
 
public class Exercicio12{
 
    public static class Employee{
        private String firstName;
        private String lastName;
        private String socialSecurityNumber;
        private String aniversario;
       	private Date birthDate = new Date();
 
        public Employee(String first, String last, String ssn, int d, int m, int y){
            firstName = first;
            lastName = last;
            socialSecurityNumber = ssn;
            birthDate.setDate(d,m,y);
            aniversario = birthDate.convertToAmericanFormat();
        }
 
 
        public void setFirstName( String first ){
            firstName = first;          
        }
        public void setLastName( String last ){
            lastName = last;
        }
        public void setSocialSecurityNumber( String ssn ){
            socialSecurityNumber = ssn;
        }
        public void setBirthDate( int date, int month, int year ){
        	birthDate.setDate(date, month, year);
        	aniversario = birthDate.convertToAmericanFormat();
        }
 
        public String getFirstName(){
            return firstName;           
        }
        public String getLastName(){
            return lastName;
        }
        public String getSocialSecurityNumber(){
            return socialSecurityNumber;
        }
        public String getBirthDate(){
        	return aniversario;
        }
 
        public String toString(){
            return String.format("%s: %s %s\n%s: %s\n%s: %s\n", "employee", getFirstName(), getLastName(), "social security number", getSocialSecurityNumber(), "birth date", getBirthDate());
        }

    }
 
    public static class CommisionEmployee extends Employee{
         
        private double grossSales;
        private double commisionRate;
 
 
        public CommisionEmployee(String first, String last, String ssn, int d, int m, int y, double sales, double rate){
             
            super(first, last, ssn, d, m, y); 
            grossSales = sales;
            commisionRate = rate;
        }
        public void setGrossSales( double sales ){
            grossSales = sales;
        }
        public void setCommisionRate( double rate ){
            commisionRate = rate;
        }
 
 
        public double getGrossSales(){
            return grossSales;
        }
        public double getCommisionRate(){
            return commisionRate;
        }
 
        public double earnings(){
            return commisionRate * grossSales;
        }
 
        @Override
        public String toString(){
            return String.format("%s: %s\n%s: %.2f\n%s: %.2f", "commision employee", super.toString(), "gross sales", grossSales, "commision rate", commisionRate);
        }
 
    }
 
    public static class BasePlusCommissionEmployee extends CommisionEmployee{
 
            private double baseSalary;
 
            public BasePlusCommissionEmployee(String first, String last, String ssn, int d, int m, int y, double sales, double rate, double salary){
                super(first, last, ssn, d, m, y, sales, rate);
                setBaseSalary( salary );
            }
 
            public void setBaseSalary(double salary){
                baseSalary = (salary < 0.0 ) ? 0.0 : salary;
            }
 
            public double getBaseSalary(){
                return baseSalary;
            }
 
            @Override
            public double earnings(){
                return baseSalary + super.earnings();
            }
 
            @Override
            public String toString(){
                return String.format("%s %s\n%s: %.2f", "base-salaried", super.toString(), "base salary", getBaseSalary());
            }
 
    }
 
    public static class HourlyEmployee extends Employee{
        private double hours;
        private double wage;
 
        public HourlyEmployee(String first, String last, String ssn, int d, int m, int y, double h, double w){
            super(first, last, ssn, d, m , y);
            hours = h;
            wage = w;
        }
 
        public void setHours(double h){
            if (h > 0 && h < 168) hours = h;
            else hours = 0;
        }
        public double getHours(){
            return hours;
        }
 
        public void setWage(double w){
            if(w > 0) wage = w;
            else wage = 0;
        }
        public double getWage(){
            return wage;
        }
 
        public double earnings(){
            return hours * wage;
        }
 
        @Override
        public String toString(){
            return String.format("%s %s\n%s: %.2f\n%s: %.2f\n%s: %.2f\n", "hourly employee", super.toString(), "hours", hours, "wage per hour", wage, "salary", earnings());
        }
 

 
    }

 	public static class Date{

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
	 
	    public String convertToAmericanFormat(){
	        return String.format("%02d/%02d/%d\n",date, month, year);
	    }
	 
	    public String convertToUniversalFormat(){
	        return String.format("%s %02d, %d\n", mes, date, year);
	         
	    }
	    public String convertToThirdFormat(){
	        return String.format("%03d %d\n",date, year);
	    }
	 
	 
}


 	public static void main(String args[]){
 		
 		Employee[] emp = new Employee[4];
 		Scanner input = new Scanner(System.in);
 		int currentMonth, i;
 		String first, last, ssn, lixo;
 		double wage, hours;
 		int d,m,y;


 		System.out.printf("Digite o mes que estamos:");
 		currentMonth = input.nextInt();

 		for(i=0; i<4; i++){ 			
 			
 			System.out.printf("Digite o nome: ");
 			first = input.next();
 			System.out.printf("Digite o sobrenome: ");
 			last = input.next();
 			System.out.printf("Digite o ssn: ");
 			ssn = input.next();

 			System.out.printf("Digite o salario: ");
 			wage = input.nextDouble();
 			System.out.printf("Digite as horas de trabalho: ");
 			hours = input.nextDouble();


 			System.out.printf("Digite o dia: ");
 			d = input.nextInt();
 			System.out.printf("Digite o mes: ");
 			m = input.nextInt();
 			System.out.printf("Digite o anbo: ");
 			y = input.nextInt();

 			emp[i] = new HourlyEmployee(first, last, ssn, d, m, y, hours, wage);
 			if(m == currentMonth){
 				System.out.printf("%s %s\n%s: %.2f\n%s: %.2f\n%s: %.2f (ANIVERSARIANTE)\n", "hourly employee", emp[i].super.toString(), "hours", hours, "wage per hour", wage, "salary", emp[i].earnings() + 100.0);
 			}else
 				System.out.printf("%s\n", emp[i].toString());
 		}


 	}
}
