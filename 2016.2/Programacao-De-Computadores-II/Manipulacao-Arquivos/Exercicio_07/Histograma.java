package Exercicio_07;

import java.io.DataInputStream;
import java.io.FileInputStream;
import java.io.IOException;

public class Histograma {

	public static void main(String[] args) {
		try{
			DataInputStream in = new DataInputStream(new FileInputStream("lenna.raw"));
			
			int[] histograma = new int[256];
			
			//Criando o histograma
			while(in.available()>0){
				int x = in.read();
				histograma[x] += 1;
			}
			
			//Printando o histograma
			System.out.println("------ HISTOGRAMA ------");
			for(int i = 0;i<histograma.length;i++){
				if(histograma[i] != 0){
					System.out.println("O tom "+i+" apareceu na imagem "+histograma[i]+ " vezes.");
				}
			}
			
		}catch(IOException erro){
			System.err.println("Erro ao ler o arquivo.");
		}

	}

}
