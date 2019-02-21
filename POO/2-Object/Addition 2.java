import java.util.*;
import javax.swing.JOptionPane;
 
public class Addition{
    public static void main(String[] args){
        int a, b, c;
        
        try{
            Scanner input = new Scanner(System.in);
            a = Integer.parseInt(JOptionPane.showInputDialog("Digite o valor de a:"));
            b = Integer.parseInt(JOptionPane.showInputDialog("Digite o valor de b:"));
            c = Integer.parseInt(JOptionPane.showInputDialog("Digite o valor de c:")); 
            
            float media = (float)(a+b+c)/3;
     
            if(a == b && a == c){
                JOptionPane.showMessageDialog(null, "A, B E C são iguais!");
            }else{
                if(a <= b && a <= c) JOptionPane.showMessageDialog(null, a + " é o menor");
                else if(b <= c && b <= a) JOptionPane.showMessageDialog(null,b +" é o menor");
                else if(c <= a && c <= b) JOptionPane.showMessageDialog(null, c + " é o menor");
             
                if(a >= b && a >= c) JOptionPane.showMessageDialog(null, a + " é o maior");
                else if(b >= c && b >= a) JOptionPane.showMessageDialog(null, b + " é o maior");
                else if(c >= a && c >= b) JOptionPane.showMessageDialog(null,c + " é o maior");
            }
     
            JOptionPane.showMessageDialog(null,"O produto é: " +  a*b*c);
            JOptionPane.showMessageDialog(null,"A soma é: " + (a+b+c));
            JOptionPane.showMessageDialog(null,"A média é: " +  media);
        }catch(NumberFormatException e1){
            JOptionPane.showMessageDialog(null, "Valor inadequado!", "Erro!", JOptionPane.ERROR_MESSAGE);
        }
    }
}