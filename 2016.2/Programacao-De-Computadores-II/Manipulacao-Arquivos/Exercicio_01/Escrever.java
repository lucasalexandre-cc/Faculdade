package Exercicio_01;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;
public class Escrever {
	public static void main(String[] args){
		Scanner input = new Scanner(System.in);
		try{
			PrintWriter pr = new PrintWriter(new FileOutputStream("arquivo.txt"));
			System.out.print("Informe sua matrícula: ");
			int mat = input.nextInt();
			do{
				System.out.print("Informe seu nome: ");
				input.nextLine(); //Porque tenho que fazer isso???
				String nome = input.nextLine();
				System.out.print("Informe seu C.R: ");
				double cr = input.nextDouble();
				escrever(pr,nome);
				escrever(pr,mat);
				escrever(pr,cr);
				System.out.print("Informe sua matrícula: ");
				mat = input.nextInt();
			}while(mat != 0);
			pr.close();
		}
		catch(IOException erro){
			System.err.println("ERRO ao escrever no arquivo");
		}
		
	}
	
	public static void escrever(PrintWriter pr,Object frase){
		pr.println(frase);
	}
}
