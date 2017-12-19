package Exercicio_05;
public class teste {
	public static void main(String[] args){
		Circulo circulo1 = new Circulo();
		circulo1.setRaio(2);
		
		Retangulo retangulo1 = new Retangulo();
		retangulo1.setLados(3, 5.2);
		
		Triangulo triangulo1 = new Triangulo();
		triangulo1.setBaseAltura(1, 4.1);
		
		Complexo todos = new Complexo();
		todos.addPoligono(circulo1);
		todos.addPoligono(retangulo1);
		todos.addPoligono(triangulo1);
		
		System.out.println("Circulo: "+circulo1.calcularArea());
		System.out.println("Retangulo: "+retangulo1.calcularArea());
		System.out.println("Triangulo: "+triangulo1.calcularArea());
		System.out.println("Complexo: "+todos.calcularArea());
	}
}
