package Questao_01;
public class A {
	public static void main(String[] args){
		double[] vetor = {1,2,3,4,5,6,7};
		System.out.println(somandoVetor1(vetor,vetor.length));
	}
	
	public static double somandoVetor1(double[] vet, int n){
		if(n <= 0) return 0;
		double valor = vet[n-1];
		return valor + somandoVetor1(vet,n-1);
	}
}
