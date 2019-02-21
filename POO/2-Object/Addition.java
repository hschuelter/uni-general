import javax.swing.JOptionPane;
//import java.util.*;

public class Addition{
	private int num1;
	private int num2;

	public int soma(){
		try {
			num1 = Integer.parseInt(JOptionPane.showInputDialog("Digite o primeiro valor:"));
			num2 = Integer.parseInt(JOptionPane.showInputDialog("Digite o segundo valor:"));

			int res = num1 + num2;

			JOptionPane.showMessageDialog(null, "O resultado é: " + res);
			return res;
		} catch(NumberFormatException e1){
			JOptionPane.showMessageDialog(null, "Você digitou um valor inadequado", "Error!", JOptionPane.ERROR_MESSAGE);
		}
		return -1;
	}

}