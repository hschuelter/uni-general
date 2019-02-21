package interfacecaixadebanco;

/**
 *
 * @author Arthur e Gabriel
 */

public class Transaction{
    private String accountNumber;
    private Conta account;

    public void setAccountNumber(String acc){
        accountNumber = acc;
    }

    public String getAccountNumber(){
        return accountNumber;
    }
    
    public void setAccount(Conta acc){
        account  = acc;
    }
    
    public Conta getAccount(){
        return account;
    }
    
    
}

