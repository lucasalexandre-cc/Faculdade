package Exercicio_05;
public class Retangulo extends Poligono{
	//Atributos
	private double lado1;
	private double lado2;
	
	//Métodos
	public void setLados(double _lado1, double _lado2){
		this.lado1 = _lado1;
		this.lado2 = _lado2;
	}
	
	public double calcularArea(){
		return this.lado1 * this.lado2;
	}
	
}
