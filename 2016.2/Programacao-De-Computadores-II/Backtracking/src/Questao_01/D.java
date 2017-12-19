package Questao_01;	
public class D {
	public static void main(String[] args){
		int[] vetor = {1,2,3,4,5};
		invertendo(0,vetor.length-1,vetor);
		for(int i = 0;i<vetor.length;i++){
			System.out.print(vetor[i]+" ");
		}
	}
	
	public static void invertendo(int n1,int n2, int[] vetor){
		int aux = vetor[n1];
		vetor[n1] = vetor[n2];
		vetor[n2] = aux;
		if(n1<=n2){
			invertendo(n1+1,n2-1,vetor);
		}
	}
}
