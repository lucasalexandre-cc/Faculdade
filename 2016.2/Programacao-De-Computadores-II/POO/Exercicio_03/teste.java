package Exercicio_03;
public class teste {
	public static void main(String[] args){
		//Testando a multiplicação
		double[] coef = {0,-1,8,5}; // -x + 8x^2 + 5x^3
		double[] coef2 = {0,0,3}; // +3x^2
		Polinomio p1 = new Polinomio(coef);
		Polinomio p2 = new Polinomio(coef2);
		p1.multiplicar(p2);
		p1.printarPolinomio();
		
		System.out.println("\n----------------");
		
		//Testando a soma
		double[] coef3 = {-2,5,-2};
		double[] coef4 = {-1,2,0,-3};
		Polinomio p3 = new Polinomio(coef3);
		Polinomio p4 = new Polinomio(coef4);
		p3.somar(p4);
		p3.printarPolinomio();
		
		System.out.println("\n----------------");
		
		//Avaliando o polinomio (atribuir um valor a x e retornar o y
		double[] coef5 = {1,-2,0,3};
		Polinomio p5 = new Polinomio(coef5);
		System.out.println("Para x = 2, y = "+p5.avaliacao(2));
	}
}
