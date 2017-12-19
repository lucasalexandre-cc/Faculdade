package URI;

import java.util.Scanner;
public class URI_1192 {
	public static void main(String[] args){
		Scanner input = new Scanner(System.in);
		int x = input.nextInt();
		for(int i = 0;i<x;i++){
			String comb = input.next();
			System.out.println(calculo(comb));
		}
	}
	
	public static int calculo(String x){
		if(x.charAt(0) == x.charAt(2)){
			return ((int)(x.charAt(0)) - 48)*((int)(x.charAt(0)) - 48);
		}else if(x.charAt(1) >= 'A' && x.charAt(1) <= 'Z'){
			return (int)(x.charAt(2) - (int)(x.charAt(0)));
		}else{
			return (int)(x.charAt(0)) + (int)(x.charAt(2)) - 96;
		}	
	}
}
