package URI;

//N�O ESQUECER DE OTIMIZAR   <----------------

import java.util.Scanner;
public class URI_1366 {
	static int ret;
	static int cont;
	public static void main(String[] args){
		Scanner input = new Scanner(System.in);
		int x = input.nextInt();
		while(x != 0){
			int[][] vetor = new int[x][2];
			ret = 0;
			cont = 0;
			for(int i = 0;i<x;i++){
				vetor[i][0] = input.nextInt();
				vetor[i][1] = input.nextInt();
			}
			retangulos(vetor);
			System.out.println(ret);
			x = input.nextInt();
		}
	}
	
	public static void retangulos(int[][] vetor){
		while(cont >= 2){
			cont -= 2;
			ret ++;
		}
		boolean cond  = false;
		for(int i = 0; i<vetor.length;i++){
			if(vetor[i][1] >= 2){
				cond = true;
				cont++;
				vetor[i][1] -= 2;
			}
		}
		if(cond)retangulos(vetor);
	}
}
