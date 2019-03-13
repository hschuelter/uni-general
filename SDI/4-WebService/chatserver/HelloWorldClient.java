package chatserver;

import java.net.URL;
import javax.xml.namespace.QName;
import javax.xml.ws.Service;

public class HelloWorldClient {

	public static void main(String[] args) {

		try {

			URL url = new URL("http://192.168.100.7:9876/WSHello?wsdl");
			QName qname = new QName("http://chatserver/",
					"HelloWorldServerImplService");

			Service service = Service.create(url, qname);

			HelloWorldServer server = service.getPort(HelloWorldServer.class);
			String name = "prasad";
			System.out.println(server.chatConnect(name));

		} catch (Exception e) {
			e.printStackTrace();
		}
	}
}
