public class Account {
	private String name;
	private double balance;

	Account(String name, double balance){
		this.name = name;
		if(balance > 0){
			this.balance = balance;
		}
	}

	public void deposit(double money){
		this.balance += money;
	}

	public void setName(String name){
		this.name = name;
	}

	public void setBalance(double money){
		this.balance = money;
	}

	public double getBalance(){
		return balance;
	}

	public void withdraw(double money){
		if(balance < money){
			System.out.println("Withdraw amount exceeded account balance");
		} else {
			balance -= money;
		}
	}

	public String getName(){
		return name;
	}

}