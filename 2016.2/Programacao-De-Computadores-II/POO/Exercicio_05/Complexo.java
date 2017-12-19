package Exercicio_05;
import java.util.ArrayList;
public class Complexo extends Poligono{
	//Atributos
	private ArrayList<Poligono> poligonos = new ArrayList<>();
	
	//Métodos
	public double calcularArea(){
		double total = 0;
		for(int i = 0;i<poligonos.size();i++){
			total += poligonos.get(i).calcularArea();
		}
		return total;
	}
	
	public void addPoligono(Poligono _p){
		poligonos.add(_p);
	}
}
