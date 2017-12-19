package Exercicio_07;
public class Main {
	public static void main(String[] args){
		Passaro p1 = new Passaro();
		Passaro p2 = new Passaro();
		Passaro p3 = new Passaro();
		Passaro p4 = new Passaro();
		
		p1.setVelocidade(350);
		p2.setVelocidade(500);
		p3.setVelocidade(55);
		p4.setVelocidade(1500);
		
		Animal[] vetorPassaro = {p4,p1,p2,p3};
		
		ordenar(vetorPassaro);
		for(int i = 0;i<vetorPassaro.length;i++){
			System.out.println(vetorPassaro[i].getVelocidade());
		}
	}
	
	private static void ordenar(Animal[] obj){
		for(int i = 0;i<obj.length;i++){
			Animal aux;
			for(int j = 0;j<obj.length;j++){
				if(obj[i].getVelocidade() < obj[j].getVelocidade()){
					aux = obj[i];
					obj[i] = obj[j];
					obj[j] = aux;
				}
			}
		}
	}
}
