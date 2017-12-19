package Exercicio_05;

import java.io.BufferedOutputStream;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.Scanner;
import java.util.zip.ZipEntry;
import java.util.zip.ZipInputStream;
import java.util.zip.ZipOutputStream;

public class CompactarDescompactar {
	//Funcao para compactar
	public static void compactar(String origem, String destino){
		try{
			byte[] dados = new byte[1024];
			InputStream in = new FileInputStream(origem);
			ZipOutputStream out = new ZipOutputStream(new BufferedOutputStream(new FileOutputStream (destino)));
			out.putNextEntry(new ZipEntry(origem));
			int i;
			while((i = in.read(dados)) > 0){
				out.write(dados, 0, i);
			}
			in.close();
			out.close();
		}catch(IOException e){
			System.out.println(e.getMessage());
		}
	}
	
	//Funcao para descompactar 
	public static void descompactar(String origem, String destino){
		try{
			ZipInputStream in = new ZipInputStream(new FileInputStream(origem));
			ZipEntry entrada = in.getNextEntry();
			FileOutputStream out = new FileOutputStream(destino);
			byte[] dados = new byte[1024]; 
			int i;
			while((i = in.read(dados)) > 0){
				out.write(dados, 0, i);
			}
			in.closeEntry();
			in.close();
			out.close();
		}catch(IOException e){
			System.out.println(e.getMessage());
		}
	}
	
	//OBS: esse código só funciona para um zip que contenha apenas um arquivo dentro
	//Eu não fiz para que descompacte vários arquivos porque no enunciado, pelo que entendi,
	//Sempre será apenas um arquivo. Mas caso eu quisesse, era só fazer mais um while, que
	//Só pararia quando entrada.getNextEntry() fosse == null.
	
}
