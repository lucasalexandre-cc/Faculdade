package Exercicio_05;

public class Circulo extends Poligono{
	//Atributos
	private double raio;
	
	//Métodos
	public void setRaio(double _raio){
		this.raio = _raio;
	}
	
	public double calcularArea(){
		return Math.PI*this.raio*this.raio;
	}
}
