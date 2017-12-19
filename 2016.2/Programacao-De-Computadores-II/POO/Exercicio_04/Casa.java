//Letra B
package Exercicio_04;
public class Casa extends Imovel{
	//Atributos
	private Porta porta1;
	private Porta porta2;
	private Porta porta3;
	
	//Métodos
	public Casa(Porta _porta1, Porta _porta2, Porta _porta3){
		this.porta1 = _porta1;
		this.porta2 = _porta2;
		this.porta3 = _porta3;
	}
	
	public int quantasPortasEstaoAbertas(){
		return ((porta1.estaAberta()? 1 : 0) + (porta2.estaAberta()? 1:0) + (porta3.estaAberta()? 1:0));
	}
	
	public int totalDePortas(){
		return 3;
	}
	
}
