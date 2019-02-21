public class Employee {

	private String nome;
	private String sobrenome;
	private double salario;

	Employee(String nome, String sobrenome, double salario){
		this.nome = nome;
		this.sobrenome = sobrenome;
		this.salario = salario;
	}

	public void setNome(String nome){
		this.nome = nome;
	}

	public String getNome(){
		return this.nome;
	}

	public void setSobrenome(String sobrenome){
		this.sobrenome = sobrenome;
	}

	public String getSobrenome(){
		return this.sobrenome;
	}

	public void setSalario(double salario){
		this.salario = salario;
	}

	public double getSalario(){
		return salario;
	}


}