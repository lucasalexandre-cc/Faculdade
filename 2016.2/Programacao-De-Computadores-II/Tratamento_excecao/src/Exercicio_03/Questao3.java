package Exercicio_03;

import java.util.ArrayList;
import java.util.Scanner;

public class Questao3 {
	public static void main(String[] args){
		/*
		 * - Sim, pode ser feito. N�o dar� erro de compila��o
		 * - Sim, em alguns casos pode fazer sentido. Se voc� quiser que uma parte do seu c�digo rode, independente de qualquer
		 * erro que acontessa no caminho, isso pode ser usado.
		 * - Segue abaixo um exemplo:
		 */
		Scanner input = new Scanner(System.in);
		ArrayList<ArrayList<Double>> matriznumeros = new ArrayList<>();
		ArrayList<Double> linha1numeros = new ArrayList<>();
		
		try{
			for(int i = 0;i<10;i++){
				linha1numeros.add(input.nextDouble());
			}
		}finally{
			matriznumeros.add(linha1numeros);
			System.out.println("Linha 1 da matriz foi criada, independente do n�mero de elementos. ");
		}
	}
}
