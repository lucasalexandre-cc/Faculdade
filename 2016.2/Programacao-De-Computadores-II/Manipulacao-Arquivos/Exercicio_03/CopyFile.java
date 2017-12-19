package Exercicio_03;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

public class CopyFile {
	public static void main(String[] args){
		try{
		InputStream in = new FileInputStream("C:/Users/Lucas/Desktop/Meus Documentos/Sistemas Operacionais ISO/Ubunto/ubuntu-16.10-desktop-amd64.iso");	
		OutputStream out = new FileOutputStream("copia.iso");
		
		byte[] buffer = new byte[10];
		
		int i;
		while((i = in.read(buffer))>0){
			out.write(buffer, 0, i);
		}
		
		in.close();
		out.close();
		
		
		}catch(IOException erro){
			System.err.println("Erro!");
		}
	}
}

//A cada "out.write", 10 bytes são escritos no arquivo.
