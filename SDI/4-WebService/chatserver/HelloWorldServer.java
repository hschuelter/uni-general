package chatserver;

import javax.jws.WebMethod;
import javax.jws.WebService;
import javax.jws.soap.SOAPBinding;
import javax.jws.soap.SOAPBinding.Style;

@WebService
@SOAPBinding(style = Style.RPC)
public interface HelloWorldServer {

	@WebMethod
	int chatConnect(String name);

	void sendMessage(String msg, String name);
	String getMessage(int pos);

	boolean compareSizes(int size);
}
