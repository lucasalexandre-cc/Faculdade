package Exercicio_01;

public class teste {
	public static void main(String[] args){
		// ---- TESTANDO A CONTA CORRENTE ----
		
		//Criando um banco
		Banco banco1 = new Banco();
		
		//Criando 2 clientes diferentes
		Cliente cliente1 = new Cliente("150.150","Lucas Alexandre",19);
		Cliente cliente2 = new Cliente("500.500","Jo�o Pedro",20);
		
		//Criando 2 contas correntes
		Corrente contacorrente1 = new Corrente(cliente1,"12345678",500, banco1);
		Corrente contacorrente2 = new Corrente(cliente2,"87654321",500,banco1);
		
		//Depositando nas duas contas
		contacorrente1.Deposito(550.25, banco1);
		contacorrente2.Deposito(500, banco1);
		
		//Vendo o saldo das duas contas
		System.out.println(contacorrente1.verSaldo(banco1));
		System.out.println(contacorrente2.verSaldo(banco1));
		
		//Sacando dinheiro apeans da conta 1
		contacorrente1.Saque(550, banco1);
		
		//Tentando sacar mais que o permitido na corrente 1(contando com o limite)
		contacorrente1.Saque(2000, banco1);
		
		//Transformando uma conta em especial
		contacorrente2.Deposito(5000, banco1);
		contacorrente2.virarEspecial();
		System.out.println("A conta corrente 2 � especial? "+contacorrente2.isEspecial());
		
		//Trasferencia da conta2 para a conta1 
		contacorrente2.Tranferencia(contacorrente1, 2000, banco1);
		
		//Ver extrato das duas contas (retorna um ArrayList com todas as movimenta��es)
		System.out.println("---------------");
		System.out.println("Extrato da conta1: ");
		System.out.println(contacorrente1.getExtrato());
		System.out.println("---------------");
		System.out.println("Extrato da conta2");
		System.out.println(contacorrente2.getExtrato());
		System.out.println("");
		
		//Ver os dados finais das duas contas
		contacorrente1.getDadosTotais();
		System.out.println("--------------");
		contacorrente2.getDadosTotais();
		System.out.println("");
		
		//Excluir alguma conta
		banco1.excluirContaCorrente(contacorrente1);
		
		//Tentar fazer alguma opera��o com a conta corrente exclu�da
		contacorrente1.verSaldo(banco1);
		contacorrente1.Saque(500, banco1);
		
		// ---- TESTANDO A CONTA DE CR�TIDO ----
		
		//Criando duas contas de cr�dito
		Credito contacredito1 = new Credito(cliente1,"12345",5530.25,banco1);
		Credito contacredito2 = new Credito(cliente1,"54321",1000,banco1);
		
		//Fazendo compras nos 2 cart�es
		contacredito1.Comprar(1000, banco1);
		contacredito2.Comprar(1000, banco1);
		
		//Ultrapassar o valor do limite (dever� emitir um erro):
		contacredito2.Pagar(100, banco1);
		
		//Pegar os dados das duas contas
		System.out.println("---------------");
		contacredito1.statusCartao();
		System.out.println("");
		contacredito2.statusCartao();
		System.out.println("--------------");
		
		//Excluindo uma conta
		banco1.excluirContaCredito(contacredito2);
		
		//Tentar fazer alguma opera��o com a conta exclu�da
		contacredito2.Comprar(100, banco1);
		
	}
}
