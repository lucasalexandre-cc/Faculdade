package Questao_02;

import java.util.Scanner;
public class TorresDeHanoi {
	public static void main(String[] args){
		Scanner input = new Scanner(System.in);
		System.out.print("Informe quantas argolas deseja: ");
		int n = input.nextInt();
		int[] original = new int[n];
		int[] destino = new int[n];
		int[] aux = new int[n];
		fazendoVetorOriginal(original,n);
		
		hanoi(n,original,destino,aux);
						
	}
	
	public static void hanoi(int n, int[] orig, int[] dest, int[] aux){
		if(n>0){
			hanoi(n-1,orig,aux,dest);
			mover(orig,dest);
			printarVetores(orig,dest,aux);
			hanoi(n-1,aux,dest,orig);
		}
	}
	
	
	public static void mover(int[] orig, int[] dest){
		int index1 = -1;
		for(int i = orig.length-1;i>=0;i--){
			if(orig[i] != 0){
				index1 = i;
				break;
			}
		}
		
		int index2 = -1;
		for(int i = 0;i<dest.length;i++){
			if(dest[i] == 0){
				index2 = i;
				break;
			}
		}
		
		dest[index2] = orig[index1];
		orig[index1] = 0;
	}
	
	public static void fazendoVetorOriginal(int[] vet, int n){
		for(int i = 0; i<vet.length;i++){
			vet[i] = n;
			n--;
		}
	}
	
	public static void printarVetores(int[] origem,int[] destino, int[] aux){
		System.out.print("Origem: ");
		for(int i = 0;i<origem.length;i++){
			System.out.print(origem[i]+ "| ");
		}	
		System.out.print("\nDestino: ");
		for(int i = 0;i<destino.length;i++){
			System.out.print(destino[i]+ "| ");
		}
		System.out.print("\nAuxiliar: ");
		for(int i = 0;i<aux.length;i++){
			System.out.print(aux[i]+ "| ");
		}
		System.out.println("");
		System.out.println("---------------");
	}
}
