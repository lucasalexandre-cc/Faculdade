package URI;

import java.util.Scanner;

public class URI_1428 {
	public static void main(String[] args){
		Scanner input = new Scanner(System.in);
		int x = input.nextInt();
		for(int i = 0;i<x;i++){
			int n = input.nextInt();
			int m = input.nextInt();
			System.out.println(calculando(n,m));
		}
		
	}
	public static int calculando(int n, int m){
		n -= 2;
		m -= 2;
		if(n%3 == 0) n = n/3;
		else n = (n/3)+1;
		m -= 3;
		if(m > 0 && m%3 == 0){ 
			m = (m/3)*n;
		}
		else if(m>0 && m%3 != 0){
			m = (m/3 + 1)*n;
		}
		return n+m;
		
	}
}
