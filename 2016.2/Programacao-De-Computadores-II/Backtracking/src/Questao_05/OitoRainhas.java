package Questao_05;

import java.util.ArrayList;

public class OitoRainhas {
	//Nesse programa, ele printa o numero da solução toda vez que achar uma solucao diferente
	//Apos isso, ele printa todas as 92 solucoes achadas (demora um pouco para compilar)
	//Nao conseguir pensar em uma maneira de fazer, se o uso de variaveis globais
	
	static ArrayList<ArrayList<ArrayList<Integer>>> todas = new ArrayList<>();
	static int a = 0;
	static int cont2 = 0;
	public static void main(String args[]){
		int[][] tabuleiro = {{0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0},
							{0,0,0,0,0,0,0,0}};
		Recursao(tabuleiro,0,0);
		
		for(int i = 0;i<todas.size();i++){
			for(int j = 0;j<8;j++){
				for(int k = 0;k<8;k++){
					System.out.print(todas.get(i).get(j).get(k) + " ");
				}
				System.out.println("");
			}
			System.out.println("--------------------");
		}
	}
	
	public static void Recursao(int[][] vetor, int y,int x){
		if(a != 0) vetor[y][x] = 1;
		a++;
		if(tem8(vetor)) {
			addTabuleiro(vetor);
		}
		
		for(int i = 0; i<8;i++){
			for(int j = 0;j<8;j++){
				if(vetor[i][j] == 0){
					if(verificandoCasa(i,j,vetor)){
						Recursao(vetor,i,j);
					}
				}
			}
		}
		vetor[y][x] = 0;
	}
	
	public static boolean verificandoCasa(int y, int x, int[][] vetor){
		for(int i = 0;i<8;i++){
			if(vetor[y][i] != 0) return false;
		}
		for(int i = 0;i<8;i++){
			if(vetor[i][x] != 0) return false;
		}
		int y2 = y;
		int x2 = x;
		while(y2>0 && x2<7){
			y2--;
			x2++;
			if(vetor[y2][x2] != 0) return false;
		}
		y2 = y;
		x2 = x;
		while(y2>0 && x2>0){
			y2--;
			x2--;
			if(vetor[y2][x2] != 0) return false;
		}
		y2 = y;
		x2 = x;
		while(y2<7 && x2<7){
			y2++;
			x2++;
			if(vetor[y2][x2] != 0) return false;
		}
		y2 = y;
		x2 = x;
		while(y2<7 && x2>0){
			y2++;
			x2--;
			if(vetor[y2][x2] != 0) return false;
		}	
		return true;
	}
	
	public static void addTabuleiro(int[][] vetor){
		ArrayList<ArrayList<Integer>> lista = new ArrayList<>(); 
		for(int i = 0;i<8;i++){
			lista.add(new ArrayList<Integer>());
			for(int j = 0;j<8;j++){
				lista.get(i).add(vetor[i][j]);
			}
		}
		if(!todas.contains(lista)){
			cont2++;
			System.out.println(cont2);
			todas.add(lista);
		}
	}
	
	public static boolean tem8(int[][] vetor){
		int cont = 0;
		for(int i = 0;i<8;i++){
			for(int j = 0;j<8;j++){
				cont+= vetor[i][j];
			}
		}
		if(cont == 8) return true;
		else return false;
	}
}
