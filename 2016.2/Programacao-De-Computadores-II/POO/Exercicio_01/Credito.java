package Exercicio_01;
public class Credito extends Conta{
	//Atributos
	private double limite;
	private String numCartao;
	private double gastos;
	//Métodos
	public Credito(Cliente _usuario, String _numCartao, double _limite, Banco _banco){
		if ( _banco.inContaCredito(this)){
			System.out.println("O número da conta, ou a própria conta, ja existe.");
		}else{
			_banco.addContaCredito(this);
			this.criarConta(_usuario);
			this.numCartao = _numCartao;
			this.limite = _limite;
			this.gastos = 0;
		}
		
	}
	
	public void Comprar(double _valor, Banco _banco){
		if(_banco.inContaCredito(this)){
			if(gastos + _valor <= limite){
				this.gastos += _valor;
				this.addExtrato(- _valor);
			}else{
				System.out.println("Erro! Essa compra extrapolaria seu limite!");
			}
		}else{
			System.out.println("Essa conta não existe!");
		}
	}
	
	public void Pagar(double _valor, Banco _banco){
		if(_banco.inContaCredito(this)){
			if(_valor <= gastos){
				gastos -= _valor;
				this.addExtrato(_valor);
				System.out.println("Pagamento realizado com sucesso! Você ainda deve "+gastos+" reais");
			}else{
				System.out.println("O valor do pagamento é maior que o de seus gastos até o momento");
			}
		}
	}
	
	public void statusCartao(){
		System.out.println("Usuario: "+this.getNome());
		System.out.println("Limite: "+limite);
		System.out.println("Valor da dívida: R$"+gastos);
		System.out.println("Extrato: "+this.getExtrato());
	}
}
