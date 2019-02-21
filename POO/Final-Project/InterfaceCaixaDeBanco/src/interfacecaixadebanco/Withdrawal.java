package interfacecaixadebanco;

/**
 *
 * @author Arthur e Gabriel
 */
public class Withdrawal extends Transaction{
    private double amount;
    private Caixa caixa;
    
    public double getAmount(){
        return amount;
    }
    public void setAmount(double a){
        amount = a;
    }
    
    public Caixa getCaixa(){
        return caixa;
    }
    public void setCaixa(Caixa c){
        caixa = c;
    }
    
    public int execute(){
        Conta acc;
        Caixa cx;
        double withdraw, saldo, saldoATM;
        
        acc = super.getAccount();
        cx = getCaixa();
        saldo = acc.getSaldo();
        withdraw = getAmount();
        saldoATM = cx.getSaldoCaixa();
        
        if(saldo < withdraw){
            return 0;
        }
        
        if(saldoATM < withdraw){
            return -1;
        }
        
        saldo = saldo - withdraw;
        acc.setSaldo(saldo);               
        
        return 1;
    }
    
}
