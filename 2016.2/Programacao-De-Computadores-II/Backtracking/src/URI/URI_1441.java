package URI;

import java.util.Scanner;
public class URI_1441 {
	//varialve global
	static int max;
	
	//main
	public static void main(String[] args){
		Scanner input = new Scanner(System.in);
		int a = input.nextInt();
		while(a != 0){
			max = a;
			System.out.println(SeqGranizo(a));
			a = input.nextInt();
		}
	}
	
	//pegando a sequ�ncia de Granizo, e atribuindo seu maior valor a vari�vel global max.
	public static int SeqGranizo(int num){
		if(num == 1){
			return max;
		}else{ 
			
			if(num%2 == 0) num/=2;
			else num = (num*3) + 1;
			
			if(num > max) max = num;
			return SeqGranizo(num);
		}	
	}
}
