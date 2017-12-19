package Questao_01;
public class B {
	public static void main(String[] args){
		int[] vetor = {1,4,43,21,42,21,143,2};
		System.out.println(Max(vetor.length,vetor));
	}
	public static int Max (int x, int[] vetor) { 
		if (x == 1){
	      return vetor[0];
	   } else {
	      int y = Max (x-1, vetor);
	      if (y > vetor[x-1]){
	         return y;
	      }else{
	         return vetor[x-1]; 
	      }
	   }
	}
}
