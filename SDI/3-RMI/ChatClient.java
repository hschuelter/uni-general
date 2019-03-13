/** HelloClient.java **/
import java.rmi.registry.*;
import java.util.*;

public class ChatClient {

	static HelloWorld stub;
	static String name;
	static int num;

	public static void main(String[] args) {
		clearScreen();
		String host = (args.length < 1) ? null : args[0];
		Scanner input = new Scanner(System.in);
		String message;

		try {
			// Obtém uma referência para o registro do RMI
			Registry registry = LocateRegistry.getRegistry("192.168.100.7",6900);
			stub= (HelloWorld) registry.lookup("Hello");

			System.out.printf("Digite seu nome: ");
			name = input.nextLine();
			num = stub.connect(name);

			new Thread(t1).start();
			sendMsg(name, num);
		}

		catch (Exception ex) {
			ex.printStackTrace();
		}
	}

	public static void receiveMsg(int pos){
		String message = "";
		Scanner input = new Scanner(System.in);
		clearScreen();
		boolean b = true;

		try{
			while( b ){
				message = stub.getMessage(pos);
				if(message.equals("\n")){
					b = false;
				}
				else{
					System.out.println(message);
					pos = pos+1;
				}
			}
		}
		catch (Exception ex){
			ex.printStackTrace();
		}

		return;
	}

	public static void sendMsg(String nick, int pos){
		String message = "";
		Scanner input = new Scanner(System.in);
		try{
			while( message.equals(nick + ": /quit") == false ){
				receiveMsg(num);
				System.out.printf(">> ");
				message = input.nextLine();
				message = nick + ": " + message;

				message = stub.sendMessage(message);
			}
		}
		catch (Exception ex){
			ex.printStackTrace();
		}

		return;
	}

	private static Runnable t1 = new Runnable() {
        public void run() {
            try{
				while(true){
					Thread.sleep(4000);
	                receiveMsg(num);
					System.out.printf(">> ");
				}
            } catch (Exception e){}

        }
    };


	public static void clearScreen(){
		System.out.print("\033[H\033[2J");
		System.out.flush();
	}
}
