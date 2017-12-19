package URI;

import java.util.ArrayList;
import java.util.Scanner;

public class URI_1407 {
	public static void main(String[] args){
		Scanner input = new Scanner(System.in);
		int N = input.nextInt();
		int C = input.nextInt();
		int K = input.nextInt();
		while(N != 0 && C != 0 && K != 0){
			int[] vetor = new int[K];
			for(int i = 0;i<N;i++){
				for(int j = 0;j<C;j++){
					int x = input.nextInt();
					vetor[x-1]++;
				}
			}
			ArrayList<Integer> vet= menosSaiu(vetor);
			for(int i = 0;i<vet.size();i++){
				if(i!=vet.size()-1) System.out.print(vet.get(i)+" ");
				else System.out.println(vet.get(i));
			}
			N = input.nextInt();
			C = input.nextInt();
			K = input.nextInt();
		}
		
	}
	
	public static ArrayList<Integer> menosSaiu(int[] vetor){
		ArrayList<Integer> vet = new ArrayList<>();
		int min = vetor[0];
		vet.add(1);
		for(int i = 1;i<vetor.length;i++){
			if(vetor[i] < min){
				vet.clear();
				vet.add(i+1);
				min = vetor[i];
			}else if(vetor[i] == min){
				vet.add(i+1);
			}
		}
		return vet;
	}
}
