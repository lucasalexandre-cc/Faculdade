package Exercicio_02;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.InputMismatchException;

public class Questao2 {
	public static void main(String[] args) throws NumberFormatException, IOException {
		BufferedReader teclado = new BufferedReader(
				new InputStreamReader(System.in));
		
		boolean ok;
		
		do{
			try{
				System.out.println("Eu sei somar!");
				System.out.print("Informe o primeiro valor: ");
				double x = Double.parseDouble(teclado.readLine());
				System.out.print("Informe o segundo valor: ");
				double y = Double.parseDouble(teclado.readLine());
				System.out.println("O resultado da soma � " + (x + y));
				ok = true;
			}catch(InputMismatchException erro){
				System.err.println("Voc� informou um termo imposs�vel de ser convertido em um n�mero real!");
				ok = false;
			}
		}while(!ok);
		}
}
