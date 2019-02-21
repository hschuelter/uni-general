package interfacecaixadebanco;

/**
 *
 * @author Arthur e Gabriel
 */
public class Conta {
    private String user;
    private String pin;
    private double saldo;
    
    public Conta(String u, String p, double s){
        user = u;
        pin = p;
        saldo = s;
    }
    
    public String getUser(){
        return user;
    }
    public void setUser(String u){
        user = u;
    }
    
    public String getPin(){
        return pin;
    }
    public void setPin(String p){
        pin = p;
    }
    
    public double getSaldo(){
        return saldo;
    }
    public void setSaldo(double s){
        saldo = s;
    }
    
}
