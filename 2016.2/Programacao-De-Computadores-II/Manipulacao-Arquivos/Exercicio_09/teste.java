package Exercicio_09;
import java.io.IOException;
public class teste {
	public static void main(String[] agrs){
		try{
			
			ReadTGA pic = new ReadTGA("flag_b16.tga");
			
		}catch(IOException e){
			System.out.println(e.getMessage());
		}
	}
}
