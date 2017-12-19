//Letra A
package Exercicio_04;
public class Porta {
	//Atributos
	private boolean aberta;
	private String cor;
	private double dimensaoX;
	private double dimensaoY;
	private double dimensaoZ;
	
	//Métodos
	public void abre(){
		this.aberta = true;
	}
	
	public void fecha(){
		this.aberta = false;
	}
	
	public void pinta(String _cor){
		this.cor = _cor;
	}
	
	public boolean estaAberta(){
		return this.aberta;
	}
	
	public void setDimensoes(double x,double y, double z){
		this.dimensaoX = x;
		this.dimensaoY = y;
		this.dimensaoZ = z;
	}
	
	public String getCor(){
		return this.cor;
	}
	
	public double getDimensaoX(){
		return this.dimensaoX;
	}
	
	public double getDimensaoY(){
		return this.dimensaoY;
	}
	
	public double getDimensaoZ(){
		return this.dimensaoZ;
	}
}
