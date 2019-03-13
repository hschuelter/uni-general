
/** HelloServer.java **/

import java.rmi.*;
import java.rmi.server.*;
import java.rmi.registry.*;

import java.util.*;


public class ChatServer implements HelloWorld {
	public ChatServer() {}
	// main()
	// hello()

	ArrayList<String> msgList = new ArrayList<String>();

	public static void clearScreen(){
		System.out.print("\033[H\033[2J");
		System.out.flush();
	}

	public static void main(String[] args) {
		try {
			// Instancia o objeto servidor e a sua stub

			clearScreen();
			System.out.println("Top - Servidor pronto");
			ChatServer server = new ChatServer();
			HelloWorld stub = (HelloWorld) UnicastRemoteObject.exportObject(server, 0);

			// Registra a stub no RMI Registry para que ela seja obtida pelos clientes
			Registry registry = LocateRegistry.createRegistry(6900);

			//Registry registry = LocateRegistry.getRegistry(9999);
			registry.bind("Hello", stub);
		}
		catch (Exception ex) {
			ex.printStackTrace();
		}
	}

	public int connect(String s) throws RemoteException{
		System.out.println(s + " se conectou!");
		msgList.add(s + " se conectou");
		return msgList.size();
	}

	public String sendMessage(String s) throws RemoteException {
		System.out.println(s);
		msgList.add(s);
		return msgList.get(0);
	}

	public String getMessage(int pos) throws RemoteException {
		if(pos > msgList.size()){
			return "\n";
		}
		return msgList.get(pos-1);
	}
}
