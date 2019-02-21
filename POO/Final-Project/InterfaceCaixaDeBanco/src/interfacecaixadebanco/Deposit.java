package interfacecaixadebanco;

/**
 *
 * @author Arthur e Gabriel
 */

public class Deposit extends Transaction{
    private double amount;
    
    public double getAmount(){
        return amount;
    }
    public void setAmount(double a){
        amount = a;
    }
    
    public void execute(){
        Conta acc;
        double depo,saldo;
             
        acc = super.getAccount();              
        saldo = acc.getSaldo();
        depo = getAmount();   
        
        if(depo > 0){
            saldo += depo;
            acc.setSaldo(saldo);
        }
        
        
    }
    
}
