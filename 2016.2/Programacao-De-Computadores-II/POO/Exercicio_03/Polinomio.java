package Exercicio_03;
public class Polinomio {
	private double c[];
	public Polinomio(double[] _coef){
		this.c = new double[_coef.length];
		
		for(int i = 0;i<_coef.length;i++){
			this.c[i] = _coef[i];
		}
	}
	
	public void multiplicar(Polinomio p2){
		double c_new[] = new double[c.length + p2.c.length - 1];
		for(int i = 0;i<p2.c.length;i++){
			for(int j = 0;j<this.c.length;j++){
				c_new[i+j] += p2.c[i]*this.c[j];
			}
		}
		c = c_new;
		
	}
	
	public void printarPolinomio(){
		for(int i = this.c.length-1; i>=0;i--){
			System.out.print(c[i]+"x^"+i);
			if(i != 0){
				System.out.print(" + ");
			}
		}
	}
	
	public void somar(Polinomio p2){
		if (p2.c.length > this.c.length){
			double c_new[] = p2.c;
			for(int i = 0; i<this.c.length;i++){
				c_new[i] += this.c[i];
			}
			this.c = c_new;
		}else{
			for(int i = 0; i<p2.c.length;i++){
				this.c[i] += p2.c[i];
			}
		}
	}
	
	public double avaliacao(double x){
		double y = 0;
		for(int i = 0; i<this.c.length;i++){
			y += this.c[i]*(Math.pow(x,i));
		}
		return y;
	}
}
