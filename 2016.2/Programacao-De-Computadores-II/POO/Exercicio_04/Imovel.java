//Letra D
package Exercicio_04;
public abstract class Imovel {
	//Atributos
	private String cor;
	
	//M�todos
	public void pinta(String _cor){
		this.cor = _cor;
	}
	
	public abstract int totalDePortas();
	public abstract int quantasPortasEstaoAbertas();
}
