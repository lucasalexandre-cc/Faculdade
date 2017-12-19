package Questao_03;
import java.util.Scanner;
public class PreenchendoImagem {
	public static void main(String[] args){
		Scanner input = new Scanner(System.in);
		int c = input.nextInt();
		int[][] vetor ={{0,0,2,3,5},{0,0,1,0,7},{0,0,1,3,3},{0,1,1,1,1},{0,0,1,2,0},{0,0,1,0,0}};
		colorindoArea(3,3,c,vetor);
		printandoVetor(vetor);
	}
	
	public static void colorindoArea(int x, int y, int c, int[][] vet){
		int aux = vet[x][y];
		vet[x][y] = c;
		if(x-1 > -1 && vet[x-1][y] == aux) colorindoArea(x-1,y,vet[x][y],vet);
		if(x-1 > -1 && y-1 > -1 && vet[x-1][y-1] == aux) colorindoArea(x-1,y-1,vet[x][y],vet);
		if(x-1 > -1 && y+1 < vet[1].length && vet[x-1][y+1] == aux) colorindoArea(x-1,y+1,vet[x][y],vet);
		if(x+1 < vet.length && vet[x+1][y] == aux) colorindoArea(x+1,y,vet[x][y],vet);
		if(x+1 < vet.length && y-1>-1 && vet[x+1][y-1] == aux) colorindoArea(x+1,y-1,vet[x][y],vet);
		if(x+1 < vet.length && y+1 <vet[1].length &&vet[x+1][y+1] == aux) colorindoArea(x+1,y+1,vet[x][y],vet);
		if(y-1 > -1 && vet[x][y-1] == aux) colorindoArea(x,y-1,vet[x][y],vet);
		if(y+1<vet[1].length && vet[x][y+1] == aux) colorindoArea(x,y+1,vet[x][y],vet);
	}
	
	public static void printandoVetor(int[][] vetor){
		for(int i = 0;i<vetor.length;i++){
			for(int j = 0;j<vetor[0].length;j++){
				System.out.print(vetor[i][j]+" ");
			}
			System.out.println("");
		}
	}
}
