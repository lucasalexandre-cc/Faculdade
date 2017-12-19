package URI;

import java.util.Scanner;
public class URI_1374 {
	static int[] _31 = {1,3,5,7,8,10,12};
	static int[] _30 = {4,6,9,11};
	public static void main(String[] args){
		Scanner input = new Scanner(System.in);
		int n = input.nextInt(); 
		while(n != 0){
			int dia = input.nextInt(); int mes = input.nextInt(); int ano = input.nextInt();
			int consumo = input.nextInt();
			
			int consumoTotal = 0;
			int cont = 0;
			for(int i = 0;i<n-1;i++){
				int dia2 = input.nextInt();
				int mes2 = input.nextInt();
				int ano2 = input.nextInt();
				int consumo2 = input.nextInt();
				if(DiaSeguinte(dia,mes,ano,dia2,mes2,ano2)) {
					cont++;
					consumoTotal += consumo2-consumo;
				}
				
				dia = dia2; mes = mes2; ano = ano2; consumo = consumo2;
			}
			System.out.println(cont+" "+consumoTotal);
			n = input.nextInt(); 
		}
	}
	
	public static boolean DiaSeguinte(int dia1, int mes1, int ano1, int dia2, int mes2, int ano2){
		if(ano1%400 == 0 ||(ano1%4==0 && ano1%100 != 0)){
			if(contido(_31,mes1)){
				if(dia1 == 31 && mes1==12 && ano2-ano1 == 1 && dia2 == 1 && mes2 == 1) return true;
				else if(dia1 == 31 && mes2-mes1 == 1 && dia2 == 1 && ano1==ano2) return true;
				else if(dia2-dia1 == 1 && mes1==mes2 && ano1==ano2) return true;
			}
			else if(contido(_30,mes1)){
				if(dia1 == 30 && mes2-mes1 == 1 && dia2==1 && ano1==ano2) return true;
				else if(dia2-dia1 == 1 && mes1 == mes2 && ano1 == ano2) return true;
			}
			else{
				if(dia1 == 29 && mes2-mes1 == 1 && dia2 == 1 && ano1==ano2) return true;
				else if(dia2-dia1 == 1 && mes2==mes1 && ano2 == ano1) return true;
			}
		}
		else{
			if(contido(_31,mes1)){
				if(dia1 == 31 && mes1==12 && ano2-ano1 == 1 && dia2 == 1 && mes2 == 1) return true;
				else if(dia1 == 31 && mes2-mes1 == 1 && dia2 == 1 && ano1==ano2) return true;
				else if(dia2-dia1 == 1 && mes1==mes2 && ano1==ano2) return true;
			}
			else if(contido(_30,mes1)){
				if(dia1 == 30 && mes2-mes1 == 1 && dia2==1 && ano1==ano2) return true;
				else if(dia2-dia1 == 1 && mes1 == mes2 && ano1 == ano2) return true;
			}
			else{
				if(dia1 == 28 &&mes2-mes1 == 1 && dia2 == 1 && ano1==ano2) return true;
				else if(dia2-dia1 == 1 && mes2==mes1 && ano2 == ano1) return true;
			}
		}
		return false;
	}
	public static boolean contido(int[] vetor, int num){
		for(int i = 0;i<vetor.length;i++){
			if(vetor[i] == num) return true;
		}
		return false;
	}
}
