package Exercicio_04;
public class teste {
	public static void main(String[] args){
		//Testando a letra A
		Porta porta1 = new Porta();
		porta1.abre();
		porta1.fecha();
		porta1.pinta("Amarelo");
		porta1.pinta("Verde");
		porta1.setDimensoes(50, 20, 100);
		
		System.out.println("A porta está aberta? "+porta1.estaAberta());
		System.out.println("Cor: "+porta1.getCor());
		System.out.println("Dimensao x: "+porta1.getDimensaoX());
		System.out.println("Dimensao y: "+porta1.getDimensaoY());
		System.out.println("Dimensao z: "+porta1.getDimensaoZ());
		System.out.println("---------------------");
		
		//Testando a letra B
		Porta porta2 = new Porta();
		porta2.abre();
		Porta porta3 = new Porta();
		porta3.abre();
		Casa casa1 = new Casa(porta1,porta2,porta3);
		casa1.pinta("Azul");
		System.out.println("Quantas portas estão abertas? "+casa1.quantasPortasEstaoAbertas());
		System.out.println("-------------------");
		
		//Testando a letra C
		Edificio edificio1 = new Edificio();
		edificio1.pinta("Vermelho");
		Porta porta4 = new Porta();
		porta4.abre();
		Porta porta5 = new Porta();
		porta5.fecha();
		Porta porta6 = new Porta();
		porta6.abre();
		
		edificio1.adicionarPorta(porta1);
		edificio1.adicionarPorta(porta2);
		edificio1.adicionarPorta(porta3);
		edificio1.adicionarPorta(porta4);
		edificio1.adicionarPorta(porta5);
		edificio1.adicionarPorta(porta6);
		System.out.println("Quantas portas então abertas? "+edificio1.quantasPortasEstaoAbertas());
		System.out.println("Total de portas: "+edificio1.totalDePortas());
		edificio1.adicionarAndar();
		edificio1.adicionarAndar();
		System.out.println("Total de andares: "+edificio1.totalDeAndares()); //Parti do principio que todo edificio já começa com pelo menos 1 andar
		
		
	}
}
