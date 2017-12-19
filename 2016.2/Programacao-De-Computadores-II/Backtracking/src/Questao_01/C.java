package Questao_01;
public class C {
	public static void main(String[] args){
		int[] vetor = {1,2,3,4,5,6,70};
		System.out.println("A posição do valor 6 no vetor é: "+achandoValor(6,vetor,vetor.length));
	}
	public static int achandoValor(int valor, int[] vetor, int n){
		if(n < 0) return -1; //Não achou o elemento

		if(vetor[n-1] == valor) return n-1;
		else return(achandoValor(valor,vetor,n-1));
	}
}
