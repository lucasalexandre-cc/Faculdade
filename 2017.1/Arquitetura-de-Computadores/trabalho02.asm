⁠⁠⁠processor 6502

	include "vcs.h"

YMissel 	= $80;
LinhaVisivelMissel = $81;
	
	SEG
	ORG $F000 	
	
Reset 
	LDX #0 
	LDA #0 

Clear           
	STA 0,x 
	inx 
	BNE Clear

	LDA #$AC
	STA COLUBK 		            
	LDA #44
	STA COLUP0 		;Cor do missel
	LDA #95
	STA YMissel 	;Pos inicial do missel
	LDA #$20
	STA NUSIZ0 		

	sta RESM0

;VSYNC
Main
	lda #0
	sta VBLANK 
	lda #2 
	sta VSYNC 
	sta WSYNC
	sta WSYNC 
	lda #43
	STA TIM64T
	lda #0 
	sta VSYNC


;Verificando o mov do missel em Y
	LDA #%00010000 	;baixo
	BIT SWCHA 
	BNE NaoBaixo
	INC YMissel

NaoBaixo
	LDA #%00100000	;cima
	BIT SWCHA 
	BNE NaoCima
	DEC YMissel

NaoCima
;Verificando o movimento em X
	LDX #00
	LDA #%01000000	;Esquerda
	BIT SWCHA 
	BNE NaoEsquerda
	LDX #$10

NaoEsquerda
	LDA #%10000000	;Direita
	BIT SWCHA 
	BNE NaoDireita
	LDX #$F0	

NaoDireita

	STX HMM0 	;Registrando o movimento


EsperarPorVBlank
	LDA INTIM	
	BNE EsperarPorVBlank	
	LDY #191	
	STA WSYNC
	STA VBLANK  		
	STA HMOVE	;Movimentar

ScanLoop:
	STA WSYNC 

ChecandoMissel
	CPY YMissel
	BNE NaoChecarMissel
	LDA #8
	STA LinhaVisivelMissel 

NaoChecarMissel

	LDA #0		
	STA ENAM0

	LDA LinhaVisivelMissel 
	BEQ FimMissel

MisselEstaOn
	LDA #2		
	STA ENAM0
	DEC LinhaVisivelMissel 

FimMissel

	DEY	
	BNE ScanLoop

	LDA #2		
	STA WSYNC  	
	STA VBLANK 	
	LDX #30	    

EsperandoOnveScan 
	STA WSYNC
	DEX      
	bne EsperandoOnveScan
	jmp Main 

	ORG $FFFA
	
InterruptVectors
	.word Reset          
	.word Reset  
	.word Reset         

END