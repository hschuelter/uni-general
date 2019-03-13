package chatserver;

import javax.xml.ws.Endpoint;
import java.util.*;

public class HelloWorldServerPublisher {


	public static void main(String[] args) {

		System.out.println("Publicando...");
		Endpoint.publish("http://192.168.100.7:9998/WSHello", new HelloWorldServerImpl());
		System.out.println("Servidor online!\n");
	}

}
