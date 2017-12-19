//Letra C
package Exercicio_04;
import java.util.ArrayList;
public class Edificio extends Imovel{
	//Atributos
	private int totalDePortas;
	private int totalDeAndares  = 1;
	private ArrayList<Porta> portas = new ArrayList<>();
	
	//Métodos
	
	public int quantasPortasEstaoAbertas(){
		int a = 0;
		for(int i = 0; i<portas.size();i++){
			a += portas.get(i).estaAberta()? 1:0;
		}
		return a;
	}
	
	public void adicionarPorta(Porta _porta){
		this.portas.add(_porta);
		this.totalDePortas += 1;
	}
	
	public int totalDePortas(){
		return this.totalDePortas;
	}
	
	public void adicionarAndar(){
		this.totalDeAndares += 1;
	}
	
	public int totalDeAndares(){
		return this.totalDeAndares;
	}
	
}
