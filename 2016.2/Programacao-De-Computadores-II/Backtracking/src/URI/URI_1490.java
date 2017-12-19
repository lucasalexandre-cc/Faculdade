package URI;

import java.util.Scanner;

public class URI_1490 {
	static int cont;
	static int maxCont;
	static int passo;
	public static void main(String[] args){
		while(true){
			try{
				Scanner input = new Scanner(System.in);
				int N = input.nextInt();
				int[][] vetor = new int[N][N];
				for(int i = 0; i<N;i++){
					String linha = input.next();
					for(int j = 0;j<N;j++){
						if(linha.charAt(j) == '.') vetor[i][j] = 0;
						else vetor[i][j] = -1;
					}
				}
				cont = 0; maxCont = 0; passo=0;
				Torres(vetor,0,0,N);
			}
			catch(Exception e){
				break;
			}
		}
		
	}
	public static void Torres(int[][] vetor,int x, int y, int N){
		if(passo != 0){
			cont++;
			atribuindoTorre(vetor,x,y,N);
			if(cont > maxCont) maxCont = cont;
			printarVetor(vetor);
		}
		passo++;
		for(int i = 0;i<N;i++){
			for(int j = 0;j<N;j++){
				if(vetor[i][j] == 0) Torres(vetor,i,j,N); 
			}
		}
		clean(vetor,x,y,N);
		cont--;
	}
	
	public static void atribuindoTorre(int[][] vetor,int x, int y, int N){
		vetor[x][y] = cont;
		//Linha
		for(int i = y-1;i>=0;i--){
			if(vetor[x][i] == -1) break;
			else if(vetor[x][i] == 0) vetor[x][i] = cont;
		}
		for(int i = y+1;i<N;i++){
			if(vetor[x][i] == -1) break;
			else if(vetor[x][i] == 0) vetor[x][i] = cont;
		}
		
		//Coluna
		for(int i = x-1;i>=0;i--){
			if(vetor[i][y] == -1) break;
			else if(vetor[i][y] == 0) vetor[i][y] = cont;
		}
		for(int i = x+1;i<N;i++){
			if(vetor[i][y] == -1) break;
			else if(vetor[i][y] == 0) vetor[i][y] = cont;
		}
	}
	
	public static void clean(int[][] vetor, int x, int y, int N){
		vetor[x][y] = 0;
		passo = 1;
		//Linha
		for(int i = y-1;i>=0;i--){
			if(vetor[x][i] == -1) break;
			else if(vetor[x][i] == cont) vetor[x][i] = 0;
		}
		for(int i = y+1;i<N;i++){
			if(vetor[x][i] == -1) break;
			else if(vetor[x][i] == cont) vetor[x][i] = 0;
		}
				
		//Coluna
		for(int i = x-1;i>=0;i--){
			if(vetor[i][y] == -1) break;
			else if(vetor[i][y] == cont) vetor[i][y] = 0;
		}
		for(int i = x+1;i<N;i++){
			if(vetor[i][y] == -1) break;
			else if(vetor[i][y] == cont) vetor[i][y] = 0;
		}
	}
	
	public static void printarVetor(int[][] vetor){
		for(int i = 0;i<vetor.length;i++){
			for(int j = 0;j<vetor.length;j++){
				System.out.print(vetor[i][j] + " ");
			}
			System.out.println("");
		}
		System.out.println("----------- " + passo + " --------------");
	}
}
