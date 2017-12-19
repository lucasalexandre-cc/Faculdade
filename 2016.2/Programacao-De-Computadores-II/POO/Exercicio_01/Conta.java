package Exercicio_01;
import java.util.ArrayList;
public abstract class Conta {
	//Atributos
	private Cliente usuario;
	private ArrayList<Double> extrato = new ArrayList<>();
	
	//Métodos
	public void criarConta(Cliente _usuario){
		this.usuario = _usuario;
	}
	
	public void addExtrato(double _valor){
		extrato.add(_valor);
	}
	
	public ArrayList<Double> getExtrato(){
		return this.extrato;
	}
	
	public int getIdade(){
		return this.usuario.getIdade();
	}
	
	public String getNome(){
		return this.usuario.getNome();
	}
}
