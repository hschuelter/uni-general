/** HelloWorld.java **/
import java.rmi.*;

public interface HelloWorld extends Remote {
    public int connect(String s) throws RemoteException;
	public String sendMessage(String s) throws RemoteException;
    public String getMessage(int pos) throws RemoteException;


}
