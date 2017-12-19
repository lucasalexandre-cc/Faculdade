package Questao_01;
public class E {
	public static void main(String[] args){
		String palavra = "arara";
		if(palindrome(0,palavra.length()-1,palavra)){
			System.out.println("É palindrome");
		}else{
			System.out.println("Não é palíncrome");
		}
	}
	
	public static boolean palindrome(int n1,int n2, String p){
		char a = p.charAt(n1);
		char b = p.charAt(n2);
		
		if(a != b) return false;
		
		if(n1<=n2){
			return palindrome(n1+1,n2-1,p);
		}
		return true;
	}
}
