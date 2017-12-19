package URI;

import java.util.Scanner;
public class URI_1029 {
	static int x = 0;
	
	public static int chamadasFib(int num){
		if(num == 0){
			return 0;
		}else if(num == 1){
			return 1;
		}else{
			x+=2;
			return chamadasFib(num-1)+chamadasFib(num-2);
		}
	}
	
	public static void main(String[] args){
		Scanner input = new Scanner(System.in);
		int cont = input.nextInt();
		for(int i = 0;i<cont;i++){
			int fib = input.nextInt();
			int z = chamadasFib(fib);
			System.out.println("fib("+fib+") = "+x+" calls = "+z);
			x = 0;
		}
	}
}
