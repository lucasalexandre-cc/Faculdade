package Exercicio_07;
public abstract class Animal {
	//Atributos
	private double peso;
	private double velocidade;
	
	//M�todos
	public void setPeso(double p){
		this.peso = p;
	}
	public double getPeso(){
		return this.peso;
	}
	public void setVelocidade(double vel){
		this.velocidade = vel;
	}
	public double getVelocidade(){
		return this.velocidade;
	}
	
	public abstract void emitirSom();
}
