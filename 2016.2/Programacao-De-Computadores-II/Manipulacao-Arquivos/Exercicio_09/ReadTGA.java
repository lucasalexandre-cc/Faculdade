package Exercicio_09;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class ReadTGA {
    private byte[] red; 
    private byte[] green; 
    private byte[] blue;
	private byte ID;
    private short larg; 
    private short alt; 

    public ReadTGA(String arquivo) throws IOException{
        
        try{
        	FileInputStream file = new FileInputStream(arquivo);
            this.ID = (byte)file.read();
            
            if(file.read() != 0 || file.read() != 2){ 
                throw new java.io.IOException("Color map não compatível.");
            }
            
            file.skip(9);
            this.larg = (short)(file.read() | file.read() << 8);
            this.alt = (short)(file.read() | file.read() << 8);
           
            file.skip(1); 
            
            file.skip(this.ID); 

            int size = (int)larg * alt;

            this.red = new byte[size];
            this.green = new byte[size];
            this.blue = new byte[size];

            for(int i = 0; i< size; i++){
                this.red[i] = (byte)file.read();
                this.green[i] = (byte)file.read();
                this.blue[i] = (byte)file.read();
            }
        }
        catch(java.io.FileNotFoundException ex){
            System.err.println("Arquivo não encontrado!");
        }
        
        FileOutputStream outRed = new FileOutputStream(arquivo.replace(".tga", "R.raw")); 
        outRed.write(red);
        outRed.close();
        
        FileOutputStream outGreen = new FileOutputStream(arquivo.replace(".tga", "G.raw")); 
        outGreen.write(green);
        outGreen.close();
        
        FileOutputStream outBlue = new FileOutputStream(arquivo.replace(".tga", "B.raw")); 
        outBlue.write(blue);
        outBlue.close();
    }
}
