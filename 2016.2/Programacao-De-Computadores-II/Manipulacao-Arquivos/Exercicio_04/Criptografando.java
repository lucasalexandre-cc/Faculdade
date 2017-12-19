package Exercicio_04;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.Scanner;

public class Criptografando {
	public static void main(String[] args){
		try{
			Scanner input = new Scanner(System.in);
			int k = input.nextInt();
			
			BufferedReader in = new BufferedReader(new InputStreamReader(new FileInputStream("entrada.txt")));
			PrintWriter pr = new PrintWriter(new FileOutputStream("saida.txt"));
			
			String linha = in.readLine();
			char[] linhaChar = linha.toCharArray();

			
			while(linha != null){
				for(int i = 0;i<linha.length();i++){
					linhaChar[i] = (char)(linhaChar[i]+k);
					if((int)(linhaChar[i]) > 127){
						while(linhaChar[i] > 127){
							linhaChar[i] = (char)(linhaChar[i]-96);
						}
					}
				}
				String x = String.valueOf(linhaChar);
				pr.println(x);
				linha = in.readLine();
				if(linha != null) linhaChar = linha.toCharArray();
			}
			pr.close();
			in.close();
			System.out.println("Arquivo criptografado!");
			
		}catch(IOException erro){
			System.err.println("Erro ao abrir o arquivo");
		}

	}
}
