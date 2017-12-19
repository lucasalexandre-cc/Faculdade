package Exercicio_01;

import java.util.ArrayList;

public class Corrente extends Conta{
	//Atributos
	private double saldo = 0;
	private double limite;
	private String numeroConta;
	private boolean especial;
	
	//M�todos
	public Corrente(Cliente _usuario, String _numConta, double _limite, Banco _banco){
		if ( _banco.inContaCorrente(this)){
			System.out.println("O n�mero da conta, ou a pr�pria conta, ja existe.");
		}else{
			_banco.addContaCorrente(this);
			this.criarConta(_usuario);
			this.especial = false;
			this.limite = _limite;
			this.numeroConta = _numConta;
		}
	}
	
	public void Deposito(double _valor, Banco _banco){
		if(_banco.inContaCorrente(this)){
		this.saldo += _valor;
		this.addExtrato(_valor);}else{
			System.out.println("Essa conta n�o existe!");
		}
	}
	
	public void Saque(double _valor, Banco _banco){
		if(_banco.inContaCorrente(this)){
		if(saldo+limite >= _valor){
		this.saldo -= _valor;
		this.addExtrato(- _valor);
		}else{
			System.out.println("Valor do saque extrapola seu saldo+limite");
		}
		}else{
			System.out.println("Essa conta n�o existe!");
		}
	}
	
	public void Tranferencia(Corrente _destino, double _valor, Banco _banco){
		if(_banco.inContaCorrente(this)){
		if(saldo+limite >= _valor){
		_destino.saldo += _valor;
		_destino.addExtrato(_valor);
		
		this.saldo -= _valor;
		this.addExtrato(- _valor);
		}else{
			System.out.println("Valor do saque extrapola seu saldp+limite");
		}
		}else{
			System.out.println("Essa conta n�o existe");
		}
	}
	
	public double verSaldo(Banco _banco){
		if(_banco.inContaCorrente(this)){
		return saldo;
		}else{
			System.out.println("Essa conta n�o existe");
			return 0;
		}
	}
	public void virarEspecial(){
		if(this.saldo >= 5000){
			this.especial = true;
			System.out.println("Parab�ns, a partir de agora sua conta � especial!");
		}else{
			System.out.println("Seu saldo � insuficiente para sua conta virar especial");
		}
	}
	public boolean isEspecial(){
		return this.especial;
	}
	
	public void getDadosTotais(){
		System.out.println("Usuario: "+this.getNome());
		System.out.println("SALDO: "+this.saldo);
		System.out.println("Limite: "+this.limite);
		System.out.println("Especial? "+this.especial);
		System.out.println("Extrato: "+this.getExtrato());
		System.out.println("Numero da conta: "+this.numeroConta);
	}
}
