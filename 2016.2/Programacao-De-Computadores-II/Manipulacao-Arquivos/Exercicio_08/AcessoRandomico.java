package Exercicio_08;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.RandomAccessFile;

public class AcessoRandomico {
	private RandomAccessFile arquivo;
	private final String nome;
	
	
	//Método construtor
	public AcessoRandomico(String _nome) throws IOException{
			this.arquivo = new RandomAccessFile(new File(_nome),"rw");
			this.nome = _nome;
	}
	
	//Método construtor padrão (caso não receva nenhum parametro)
	public AcessoRandomico() throws IOException{
		this.arquivo = new RandomAccessFile(new File("arquivoPadrao.bin"),"rw");
		this.nome = "arquivoPadrao.bin";
	}

	
	//Gets do int, double1 ou double2, dado a posição do vetor
	public int getInteiro(long posicao) throws IOException{
		this.arquivo.seek(posicao*(long)(20));
		return this.arquivo.readInt();
	}
	public double getReal1(long posicao) throws IOException{
		this.arquivo.seek(posicao*(long)(20) + 4);
		return this.arquivo.readDouble();
	}
	public double getReal2(long posicao) throws IOException{
		this.arquivo.seek(posicao*(long)(20) + 12);
		return this.arquivo.readDouble();
	}
	
	
	//Fechar o arquivo
	public void fecharArquivo() throws IOException{
		this.arquivo.close();
	}
	
	
	//Abrir o arquivo(caso tenha fechado e queira utilizar de novo)
	public void abrirArquivo() throws IOException{
		this.arquivo = new RandomAccessFile(new File(this.nome),"rw");
	}
	
	
	//Adicionar elementos ao final da lista
	public void setElementos(int inteiro, double real1, double real2) throws IOException{
		this.arquivo.seek(this.arquivo.length());
		this.arquivo.writeInt(inteiro);
		this.arquivo.writeDouble(real1);
		this.arquivo.writeDouble(real2);	
	}
	
	
	
	//Printar os elementos da lista, dado um índice
	public void printTodosElementos() throws IOException{
		try{
			this.arquivo.seek(0);
			for(int i = 0;i<this.arquivo.length()/20;i++){
				System.out.println("-> Índice "+i+":");
				System.out.println("Inteiro: "+this.arquivo.readInt());
				System.out.println("Real1: "+this.arquivo.readDouble());
				System.out.println("Real2: "+this.arquivo.readDouble());
			}
		}catch(java.io.EOFException e){
			System.err.println("Índice inválido.");
		}
	}
	
	
	//Mudar os elementos da lista, dado uma posição
	public void changeElemento(long posicao, int inteiro,double real1, double real2) throws IOException{
		try{
			this.arquivo.seek(posicao*Integer.toUnsignedLong(20));
			this.arquivo.writeInt(inteiro);
			this.arquivo.writeDouble(real1);
			this.arquivo.writeDouble(real2);
		}catch(java.io.EOFException e){
			System.err.println("Índice inválido.");
		}
	}
	
	
	//Ordenar o vetor de forma crescente
	public void ordenarPeloIntCrescente() throws IOException{
		int cont = 1;
		while(cont != 0){
			cont = 0;
			int inteiro;
			double real1;
			double real2;
			for(int i = 0;i<(this.arquivo.length()/Integer.toUnsignedLong(20))-1;i++){
				if(getInteiro(i) > getInteiro(i+1)){
					inteiro = getInteiro(i);
					real1 = getReal1(i);
					real2 = getReal2(i);
					changeElemento(i, getInteiro(i+1), getReal1(i+1),getReal2(i+1));
					changeElemento(i+1,inteiro,real1,real2);
					cont ++;
				}
			}
		}
	}
	
	
	//Ordenar o vetor de forma decrescente
	public void ordenarPeloIntDecrescente() throws IOException{
		int cont = 1;
		while(cont != 0){
			cont = 0;
			int inteiro;
			double real1;
			double real2;
			for(int i = 0;i<(this.arquivo.length()/Integer.toUnsignedLong(20))-1;i++){
				if(getInteiro(i) < getInteiro(i+1)){
					inteiro = getInteiro(i);
					real1 = getReal1(i);
					real2 = getReal2(i);
					changeElemento(i, getInteiro(i+1), getReal1(i+1),getReal2(i+1));
					changeElemento(i+1,inteiro,real1,real2);
					cont ++;
				}
			}
		}
	}
	
	
	//Excluir elemento do vetor
	public void excluirElemento(long posicao) throws IOException{
		if(posicao == 0 && this.arquivo.length() == (long)(20)){
			this.arquivo.setLength(0);
		}else if(posicao+1 == this.arquivo.length()/(long)(20)){
			this.arquivo.setLength(this.arquivo.length() - 20);
		}else{
			for(long i = posicao;i<(this.arquivo.length() - 20)/(long)(20);i++){	
				changeElemento(i,getInteiro(i+1),getReal1(i+1),getReal2(i+1));
			}
			this.arquivo.setLength(this.arquivo.length() - 20);
		}
	}
}
