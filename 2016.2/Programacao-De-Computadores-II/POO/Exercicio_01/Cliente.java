package Exercicio_01;
public class Cliente {
	//Atributos
	private String cpf;
	private String nome;
	private int idade;
	
	//Métodos
	public Cliente(String _cpf,String _nome,int _idade){
		this.cpf = _cpf;
		this.nome = _nome;
		this.idade = _idade;
	}
	
	public String getCpf(){
		return this.cpf;
	}
	
	public String getNome(){
		return this.nome;
	}
	
	public int getIdade(){
		return this.idade;
	}
	
}
