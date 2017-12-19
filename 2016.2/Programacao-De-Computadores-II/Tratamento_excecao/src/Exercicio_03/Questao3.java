package Exercicio_03;

import java.util.ArrayList;
import java.util.Scanner;

public class Questao3 {
	public static void main(String[] args){
		/*
		 * - Sim, pode ser feito. Não dará erro de compilação
		 * - Sim, em alguns casos pode fazer sentido. Se você quiser que uma parte do seu código rode, independente de qualquer
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
			System.out.println("Linha 1 da matriz foi criada, independente do número de elementos. ");
		}
	}
}
