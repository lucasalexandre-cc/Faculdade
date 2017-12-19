package Exercicio_08;

import java.io.IOException;
import java.util.Scanner;

public class teste {
	public static void main(String[] args){
		Scanner input = new Scanner(System.in);
		try{
			AcessoRandomico lista1 = new AcessoRandomico("arquivo_lista_sequencial.bin");
			lista1.setElementos(10, 12.5, 11.0);
			lista1.setElementos(5, 10.5, 3.5);
			lista1.setElementos(1, 1.1, 1.2);
			lista1.changeElemento(2, 2, 2.1, 2.2);//Alterando os elementos da posição de índice 2
			lista1.setElementos(1, 5.5, 2.7);
			lista1.setElementos(11, 5.3, 2.1);
			lista1.setElementos(9, 0.5, 1.3);
			
			System.out.println("Resultado final, após os sets e changes: ");
			lista1.printTodosElementos();
			System.out.println("");
			
			System.out.println("Excluindo elemento da lista(por posição): ");
			lista1.excluirElemento(3); //No caso, estaria excluindo os elementos (5,10.5,3.5), que estão na posição 1
			lista1.printTodosElementos();
			System.out.println("");
			
			lista1.ordenarPeloIntCrescente();
			System.out.println("Elementos após a ordenação crescente: ");
			lista1.printTodosElementos();
			System.out.println("");
			
			System.out.println("Elementos após a ordenação decrescente: ");
			lista1.ordenarPeloIntDecrescente();
			lista1.printTodosElementos();
			System.out.println("");
			
			lista1.fecharArquivo();
			
		}catch(IOException e){
			System.err.println(e.getMessage());
		}
	}
}
