package Questao_08;
public class Labirinto {
	//No exercicio nao pede para achar o melhor caminho possivel, mas sim para achar um caminho
	//O programa foi implementado para fazer isso.
	
	static int cont = 0;
	public static void main(String[] args){
		int[][] labirinto ={{1,1,1,1,1,1,1},
							{1,0,1,1,1,1,1},
							{1,0,1,0,1,1,1},
							{1,0,1,0,1,1,0},
							{1,0,1,0,1,1,1},
							{1,0,0,0,0,0,1},
							{1,1,0,1,1,1,1},
							{1,1,0,1,1,1,1}};
		if(andando(labirinto,1,1)){
			printarLab(labirinto);
		}else{
			System.out.println("Não conseguimos concluir o labirinto!");
		}
	}
	
	public static boolean andando(int[][] vetor, int i, int j){
		vetor[i][j] = 2;
		if(!ganhou(vetor)){
			//Para cima
			if(i-1>= 0){
				if(vetor[i-1][j] == 0) andando(vetor,i-1,j);
				if(ganhou(vetor)) return true;
			}
			//Para baixo
			if(i+1<vetor.length){
				if(vetor[i+1][j] == 0) andando(vetor,i+1,j);
				if(ganhou(vetor)) return true;
			}
			//Para esquerda
			if(j-1>=0){
				if(vetor[i][j-1] == 0) andando(vetor,i,j-1);
				if(ganhou(vetor)) return true;
			}
			//Para direita
			if(j+1<vetor[0].length){
				if(vetor[i][j+1] == 0) andando(vetor,i,j+1);
				if(ganhou(vetor)) return true;
			}
		}else{
			return true;
		}
		return false;
	}
	public static boolean ganhou(int[][] vetor){
		for(int i = 0;i<vetor.length;i++){
			if(vetor[i][0] == 2){
				return true;
			}
		}
		for(int j = 0;j<vetor[0].length;j++){
			if(vetor[0][j] == 2){
				return true;
			}
		}
			
		for(int i = 0;i<vetor.length;i++){
			if(vetor[i][vetor[0].length-1] == 2){
				return true;
			}
		}
		for(int j = 0;j<vetor[0].length;j++){
			if(vetor[vetor.length-1][j] == 2){
				return true;
			}
		}
		return false;
	}
	
	public static void printarLab(int[][] vetor){
		for(int i = 0;i<vetor.length;i++){
			for(int j = 0;j<vetor[0].length;j++){
				System.out.print(vetor[i][j]);
			}
			System.out.println("");
		}
		System.out.println("---------------");
	}
}
