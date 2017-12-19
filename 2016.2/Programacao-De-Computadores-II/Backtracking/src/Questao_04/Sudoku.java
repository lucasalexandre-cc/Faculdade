package Questao_04;
public class Sudoku {
	static int a = 0;
	public static void main(String[] args){
		int[][] vetor = 
            {{0,0,0,4,7,8,0,5,0},
            {0,0,0,0,0,2,9,0,0},
            {0,0,0,6,0,0,8,0,0},
            {0,3,8,1,0,0,6,7,0},
            {0,6,0,9,0,4,0,1,0},
            {0,9,1,0,0,6,5,8,0},
            {0,0,5,0,0,9,0,0,0},
            {0,0,9,2,0,0,0,0,0},
            {0,4,0,8,6,7,0,0,0}};//jogo no nível mais alto possivel (de acordo com o site do jogo na internet)
		Recursao(0,0,0,vetor);
	}
	
	public static boolean Recursao(int y, int x,int num, int[][] vet){
		if (a!=0){
			vet[y][x] = num;
		}
		a++;
		if(!ganhou(vet)){
			for(int i = 0;i<9;i++){
				for(int j = 0;j<9;j++){
					if(vet[i][j] == 0){
						for(int z = 1;z<10;z++){
							if(verificarNum(i,j,z,vet)){
								Recursao(i,j,z,vet);
							}
						}
						vet[y][x] = 0;
						return false;
					}
				}
			}
		}else{
			return true;
		}
		return false;
	}
	
	public static boolean verificarNum(int y, int x, int numero, int[][] vet){
		//Horizontal
		for(int i = 0;i<9;i++){
			if(vet[y][i] == numero) return false;
		}
		//Vertical
		for(int i = 0; i<9;i++){
			if(vet[i][x] == numero) return false;
		}
		int contx = -1;
		while(x>contx){
			contx += 3;
		}
		contx -= 2;
		
		int conty = -1;
		while(y> conty){
			conty+=3;
		}
		conty -= 2;
		
		x = contx;
		y = conty;
		if(vet[y][x] == numero || vet[y][x+1] == numero || vet[y][x+2] == numero) return false;
		if(vet[y+1][x] == numero || vet[y+1][x+1] == numero || vet[y+1][x+2] == numero) return false;
		if(vet[y+2][x] == numero || vet[y+2][x+1] == numero || vet[y+2][x+2] == numero) return false;
		
		return true;
	}
	public static boolean ganhou(int[][] vet){
		for(int i = 0;i<9;i++){
			for(int j = 0;j<9;j++){
				if(vet[i][j] == 0) return false;
			}
		}
		printarVetor(vet);
		return true;
	}
	
	public static void printarVetor(int[][] vetor){
		for(int i = 0;i<9;i++){
			for(int j = 0;j<9;j++){
				System.out.print(vetor[i][j] + " ");
			}
			System.out.println("");
		}
		System.out.println("-----------------");
	}
}
