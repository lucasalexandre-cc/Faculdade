package Exercicio_01;

import java.util.ArrayList;
public class Banco {
	//Atributos
	private ArrayList<Corrente> ContasCorrente = new ArrayList<>();
	private ArrayList<Credito> ContasCredito = new ArrayList<>();
	
	//Métodos para Conta Corrente
	public void addContaCorrente(Corrente _conta){
		this.ContasCorrente.add(_conta);
	}
	public boolean inContaCorrente(Corrente _conta){
		return this.ContasCorrente.contains(_conta);
	}
	
	public void excluirContaCorrente(Corrente _conta){
		this.ContasCorrente.remove(_conta);
	}
	
	// Métodos para Conta Crédito
	public void addContaCredito(Credito _conta){
		this.ContasCredito.add(_conta);
	}
	public boolean inContaCredito(Credito _conta){
		return this.ContasCredito.contains(_conta);
	}
	
	public void excluirContaCredito(Credito _conta){
		this.ContasCredito.remove(_conta);
	}
}
