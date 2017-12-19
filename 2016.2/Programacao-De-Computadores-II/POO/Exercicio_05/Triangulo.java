package Exercicio_05;
public class Triangulo extends Poligono{
	//Atributos
	private double base;
	private double altura;
	
	//Métodos
	public void setBaseAltura(double _base, double _altura){
		this.base = _base;
		this.altura = _altura;
	}
	
	public double calcularArea(){
		return (this.base*this.altura)/2;
	}
}
