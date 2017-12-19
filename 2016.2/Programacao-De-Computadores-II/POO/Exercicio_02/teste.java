package Exercicio_02;
public class teste {
	public static void main(String[] args){
		Pais Brasil = new Pais("Brasil","Rio de Janeiro",7500);
		Pais Brasil2 = new Pais("Brasil","Rio de Janeiro",8500);
		Pais Canada = new Pais("Canada","Otawwa",10000);
		Pais EUA = new Pais("EUA","Washington",100);
		Pais Mexico = new Pais("Mexico","HFHUds",50000);
		
		//Testando a igualdade
		System.out.println("Brasil é o mesmo pais que Brasil2? "+Brasil.equals(Brasil2));
		
		//Colocando o Canada como fronteira do Brasil
		Brasil.setFronteira(Canada);
		EUA.setFronteira(Canada);
		Brasil.setFronteira(Mexico);
		EUA.setFronteira(Mexico);
		System.out.println("Vizinhos do México: "+Mexico.getFronteira());
		System.out.println("Vizinhos em comum entre Brasil e EUA: "+ Brasil.vizinhosComuns(EUA));
	}
}
