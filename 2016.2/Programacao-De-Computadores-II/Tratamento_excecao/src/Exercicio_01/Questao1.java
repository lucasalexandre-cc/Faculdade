package Exercicio_01;

import java.util.InputMismatchException;

public class Questao1 {
	public static void main(String[] args){
		try{
			int n = Integer.parseInt(args[0]);
			for(int i = 0;i<n;i++){
				System.out.println(i);
			}
		}catch(InputMismatchException erro){
			System.err.println("Voc� informou um termo imposs�vel de ser convertido para inteiro.");
		}catch(ArrayIndexOutOfBoundsException erro){
			System.err.println("Posi��o do Array n�o encontrada");
		}
	}
}
