import java.util.*;

public class Exercicio914{

	public class Employee{
		private String firstName;
		private String lastName;
		private String socialSecurityNumber;

		public Employee(String first, String last, String ssn){
			firstName = first;
			lastName = last;
			socialSecurityNumber = ssn;
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

		public String getFirstName(){
			return firstName;			
		}
		public String getLastName(){
			return lastName;
		}
		public String getSocialSecurityNumber(){
			return socialSecurityNumber;
		}

		public String toString(){
			return String.format("%s: %s %s\n%s: %s\n", "employee", getFirstName(), getLastName(), "social security number", getSocialSecurityNumber());
		}
	}

	public class CommisionEmployee extends Employee{
		
		private double grossSales;
		private double commisionRate;


		public CommisionEmployee(String first, String last, String ssn, double sales, double rate){
			
			super(first, last, ssn); 
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

	public class BasePlusCommissionEmployee extends CommisionEmployee{

			private double baseSalary;

			public BasePlusCommissionEmployee(String first, String last, String ssn, double sales, double rate, double salary){
				super(first, last, ssn, sales, rate);
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

	//Exercicio915

	public class HourlyEmployee extends Employee{
		private double hours;
		private double wage;

		public HourlyEmployee(String first, String last, String ssn, double h, double w){
			super(first, last, ssn);
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
}