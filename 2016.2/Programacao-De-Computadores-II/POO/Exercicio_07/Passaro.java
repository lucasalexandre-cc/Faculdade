package Exercicio_07;
public class Passaro extends Animal implements Comparavel{
	//Atributos
	private String corPena;
	
	//Métodos
	public void emitirSom(){
		System.out.println("FiuFiu");
	}
	
	public void setCorPena(String cor){
		this.corPena = cor;
	}
	public String getCorPena(){
		return this.corPena;
	}
	
	public int compararCom(Animal arg){
		if(this.getVelocidade() < arg.getVelocidade()){
			return -1;
			}else if(this.getVelocidade() == arg.getVelocidade()){
				return 0;
			}else{
				return 1;
			}
		}
}
