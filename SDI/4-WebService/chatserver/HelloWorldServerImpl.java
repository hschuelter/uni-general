package chatserver;

import javax.jws.WebService;
import java.util.*;

@WebService(endpointInterface = "chatserver.HelloWorldServer")
public class HelloWorldServerImpl implements HelloWorldServer {

	ArrayList<String> msgList = new ArrayList<String>();

	public int chatConnect(String name) {
		msgList.add(name + " se conectou");
		System.out.println(name + " se conectou!");

		return msgList.size() - 1;
	}

	public void sendMessage(String msg, String name){
		String mensagem;
		if( msg.equals("/quit") ){
			mensagem = name + " se desconectou...";;
		}
		else{
			mensagem = name + ": " + msg;
		}
		msgList.add(mensagem);
		System.out.println(mensagem);
	}

	public String getMessage(int pos){
		if(pos >= msgList.size()){
			return "\n";
		}
		return msgList.get(pos);
	}

	public boolean compareSizes(int size){
		if(size >= msgList.size()){
			return false;
		}
		return true;
	}
}
