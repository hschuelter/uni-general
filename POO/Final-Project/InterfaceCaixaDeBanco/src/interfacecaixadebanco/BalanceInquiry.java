package interfacecaixadebanco;

/**
 *
 * @author Arthur e Gabriel
 */

public class BalanceInquiry extends Transaction{
    
    public double execute(){
        Conta acc;        
        acc = super.getAccount();        
        return acc.getSaldo();
    }
    
}
