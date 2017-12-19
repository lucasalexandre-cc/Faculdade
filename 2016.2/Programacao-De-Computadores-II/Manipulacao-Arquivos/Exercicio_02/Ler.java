package Exercicio_02;

import java.io.DataInputStream;
import java.io.FileInputStream;
import java.io.IOException;

public class Ler {
	public static void main(String[] args){
		
		try{
		DataInputStream in = new DataInputStream(new FileInputStream("arquivo2.txt"));
		
		while(in.available()>0){
			System.out.println(in.readInt());
			System.out.println(in.readUTF());
			System.out.println(in.readDouble());
		}
		in.close();
		
		}catch(IOException erro){
			System.err.println("Erro ao ler o arquivo.");
		}
	}
}
