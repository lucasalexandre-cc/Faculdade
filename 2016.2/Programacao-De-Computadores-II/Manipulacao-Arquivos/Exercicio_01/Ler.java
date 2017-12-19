package Exercicio_01;
import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
public class Ler {
	public static void main(String[] agrs){
		try{
			InputStreamReader in = new InputStreamReader(new FileInputStream("arquivo.txt"));
			BufferedReader br = new BufferedReader(in);
			String linha = br.readLine();
			int cont = 0;
			do{
				cont ++;
				System.out.println(linha);
				linha = br.readLine();
				if(cont%3 == 0){
					System.out.println("-----------------------------");
				}
			}while(linha != null);
			
			
		}
		catch(IOException erro){
			System.err.println("Erro ao ler arquivo!");
		}
	}
}
