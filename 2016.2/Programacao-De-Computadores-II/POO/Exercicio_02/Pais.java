package Exercicio_02;
import java.util.ArrayList;
public class Pais {
	//Atributos
	private String nome;
	private String nomeCapital;
	private double dimensao;
	private ArrayList<String> fronteira = new ArrayList<>();
	
	//Método Construtor
	public Pais(String _nome, String _nomeCapital, double _dimensao){
		this.nome = _nome;
		this.nomeCapital = _nomeCapital;
		this.dimensao = _dimensao;
	}
	
	//Gets and Sets
	public String getNome(){
		return this.nome;
	}
	public void setNome(String _nome){
		this.nome = _nome;
	}
	
	public String getNomeCapital(){
		return this.nomeCapital;
	}
	public void setNomeCapital(String _nomeCapital){
		this.nomeCapital = _nomeCapital;
	}
	
	public double getDimensao(){
		return this.dimensao;
	}
	public void setDimensao(double _dimensao){
		this.dimensao = _dimensao;
	}
	
	public ArrayList<String> getFronteira(){
		return this.fronteira;
	}
	public void setFronteira(Pais _vizinho){
		if(this.equals(_vizinho)){
			System.out.println("Erro! Os países são iguais.");
		}else{
		fronteira.add(_vizinho.getNome());
		_vizinho.fronteira.add(this.getNome());
		}
	}
	
	//Método para verificar se 2 paises são iguais
	public boolean equals(Pais _outro){
		return ((this.nome.equals(_outro.nome))&&(this.nomeCapital.equals(_outro.nomeCapital)));
	}
	
	//Letra D (já é o setFronteira)
	
	//Letra E (já é o getFronteira)
	
	//Vizinhos em comum
	public ArrayList<String>vizinhosComuns(Pais _outro){
		ArrayList<String> rascunho = new ArrayList<>();
		for(int i = 0; i<this.fronteira.size();i++){
			if(_outro.fronteira.contains(this.fronteira.get(i))){
				rascunho.add(this.fronteira.get(i));
			}
		}
		return rascunho;
	}
}
