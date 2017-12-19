package Exercicio_02;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class Escrever {
	public static void main(String[] args){
		Scanner input = new Scanner(System.in);
		try{
		DataOutputStream out = new DataOutputStream(new FileOutputStream("arquivo2.txt"));
		System.out.print("Informe sua matrícula: ");
		int mat = input.nextInt();
		do{
			out.writeInt(mat);
			System.out.print("Informe seu nome: ");
			input.nextLine(); //Porque tenho que fazer isso???
			String nome = input.nextLine();
			out.writeUTF(nome);
			System.out.print("Informe seu C.R: ");
			double cr = input.nextDouble();
			out.writeDouble(cr);
			System.out.print("Informe sua matrícula: ");
			mat = input.nextInt();
		}while(mat != 0);
		out.close();
		}catch(IOException erro){
			System.err.println("Erro ao escrever o arquivo");
		}
		
	}
}
