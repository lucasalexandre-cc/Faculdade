	processor 6502
        
	include "vcs.h"

;Variáveis usadas para 'desenhar' o Míssel (trabalho02) e agora também para delimitar o movimento do Míssel no eixo 'Y'
YMissel = $80;
LinhaVisivelMissel = $81;

;Variável usada para delimitar o movimento do Míssel no eixo 'X'
XMissel = $85;

;Variáveis usadas na troca de cores quando pressionar o 'gatilho' (trabalho03)
CorMissel = $83;
CorBorda = $84;
Delay = $82
	
	SEG
	ORG $F000 
	
; Limpa RAM e todos os registradores TIA
Reset 
	LDX #0 
	LDA #0 

Clear           
	STA 0,x 
	inx 
	BNE Clear

	STA Delay		;Atribui 0 a variável 'Delay' (trabalho 03 - lógica para não trocar as cores várias vezes simultaneamente)

	LDA #00
	STA COLUBK 		          
	LDA #65
	STA CorMissel	
	STA COLUP0 
	LDA #95
	STA YMissel

	sta RESM0	
	 	
	LDA #$20
	STA NUSIZ0 		
	
	;	Setamos o valor '77' na variável 'XMissel'. A escolha desse valor foi um tanto quanto inusitada.
	;Para impedirmos que o Míssel ultrapasse a borda superior/inferior (eixo Y), a lógica é um tanto quanto
	;trivial (será explicada posteriormente). Contudo, para impedirmos que o Míssel ultrapasasse as bordas
	;lareais (eixo X), o problema se tornou um pouco mais complicado. 	
	;	O movimento no eixo X é realizado por meio
	;do HMM0 e HMOVE (registra e orienta o movimento no eixo x - trabalho 02). Com isso, ficou mais dificil sabermos
	;onde o míssel está localizado no eixo X. Para solucionar esse problema (provavelmente não é a melhor forma de se 
	;solucionar esse problema, contudo foi o que consguimos implementar e foi eficiente), decidimos criar uma variável
	;'XMissel'. Seu valor inicial foi definido com base em testes, que foram basicamente: definimos valores para
	;'XMissel', decrementamos seu valor caso o Míssel se movimente para esquerda e incrementando caso ele vá para direita.
	;Testamos valores diferentes até acharmos o valor 'x' onde, dado 'n' movimentos para esquerda, esse valor ('x') terá que ser
	;igual a 0 quando o Míssel estiver na borda lateral esquerda. Com isso, na base de testes, definimos o valor '77' para o
	;variáve 'XMissel' (é necessário 77 leituras de movimentos para esquerda para ele chegar a borda lateral esquerda).
	;Agora basta sabermos quanto movimentos para a direita (incrementa XMissel) é preciso para ele chegar a borda lateral direita(63),
	;e fazermos branchs com a lógica desses valores.
	LDA #69
	STA XMissel

	;Configurando cor e controle do Playfield
	LDA #25
	STA CorBorda
	STA COLUPF             
	LDA #%00000001
	STA CTRLPF		;Reflexão

	;Configurando os registradores de audio
	LDA #10
	STA AUDF0	;Registrador de divisão de frequência
	LDA #10
	STA AUDC0	;Registrador de controle de audio


;VSYNC
Main
	LDA #0
	STA AUDV0	;Boto o volume para 0
	STA VBLANK 
	LDA #2 
	STA VSYNC 
	STA WSYNC
	STA WSYNC 
	LDA #43
	STA TIM64T
	LDA #0 
	STA VSYNC


;COMEÇO: verificação do movimento do míssel em X e Y (já explicados no trabalho 02).
	
	LDY YMissel
	CPY #184	;Caso o valor de 'YMissel' seja igual a 184, significa que chegamos na margem superior.
	BEQ NaoCima	;Pulamos a verificação do movimento para cima, se 'YMissel' = 192 - 8(tamanho da borda superior) = 184
	LDA #%00010000 	;cima. 
	BIT SWCHA 
	BNE NaoCima
	INC YMissel	
	
NaoCima
	LDY YMissel	
	CPY #17			;Caso o valor de 'YMissel' seja igual a 7, significa que chegamos na margem inferior.
	BEQ NaoBaixo 	;Pulamos a verificação do movimento para baixo, se 'YMissel' = 8(margem) + 8(tamanho do missel) + 1 = 17
	LDA #%00100000	;baixo
	BIT SWCHA 
	BNE NaoBaixo
	DEC YMissel

NaoBaixo
	LDY XMissel	
	CPY #0			;Caso o valor de 'XMissel' seja igual a 0, significa que chegamos na margem lateal esquerda.
	BEQ NaoEsquerda	;Pulamos a verificação do movimento para esquerda, se 'XMissel' = 0 (explicado quando setamos o valor inicial dela)
	LDA #%01000000	;Esquerda
	BIT SWCHA 
	BNE NaoEsquerda
	LDX #$10
	DEC XMissel		;Decrementa o valor de 'XMissel'

NaoEsquerda
	LDY XMissel		
	CPY #140		;Caso o valor de 'XMissel' seja igual a 140, significa que chegamos na margem lateal direita.
	BEQ NaoDireita	;Pulamos a verificação do movimento para direita, se 'XMissel' = 140 (77+63)
	LDA #%10000000	;Direita
	BIT SWCHA 
	BNE NaoDireita
	INC XMissel		;Incrementa o valor de 'XMissel'
	LDX #$F0	

NaoDireita
	STX HMM0 	;Registrando o movimento
;FIM: fim da verificação do movimento do míssel em X e Y.
	

;Aqui será verificado se o botão (gatilho) foi pressionado ou não, e fará as operações necessárias (trabalho 03)
	LDY Delay
	CPY #0
	BNE DecrementaDelay	;Lógica para consertar troca simultânea de cores (trabalho 03)
	LDA INPT4		;Lê o input do botao
	BMI NaoBotao	;Pula para 'NaoBotao' caso o botão não tenha sido pressionado.
	LDA #10
	STA AUDV0	;Aumenta o volume (só é chamado quando o botão é pressionado)
	STA Delay
	LDA CorMissel
	LDX CorBorda
	STA CorBorda
	STA COLUPF
	STX CorMissel
	STX COLUP0
DecrementaDelay
	DEC Delay
NaoBotao


EsperarPorVBlank  
	LDA INTIM	
	BNE EsperarPorVBlank

	LDY #191
	STA WSYNC
	STA VBLANK  

	STA WSYNC		
	STA HMOVE	;Orienta a movimentação do míssel

	LDX #%11111111
  	STX PF0
  	STX PF1
  	STX PF2
  	
ScanLoop
	STA WSYNC 


;COMEÇO: checando se o míssel deve ser desenhado ou não (já explicados no trab anterior);
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
;FIM: terminamos de checar se o míssel deve ser desenhado ou não.

	
;Aqui, trocaremos a configuração do Playfield de acordo com o valor do registrador Y (Trabalho 3)
	CPY #184
	BEQ MargemMeio
	CPY #9
	BEQ MargemFim
DecrementandoRegY	;Essa label é usada como retorno para as chamadas 'MargemMeio' e 'MargemFim'
	DEY		
	BNE ScanLoop

	LDA #2		
	STA WSYNC  	
	STA VBLANK 	
	LDX #30	    

EsperandoOnveScan 
	STA WSYNC
	DEX      
	BNE EsperandoOnveScan
	JMP Main ;Recomeçar tudo (voltar ao main)



;Aqui são as labels que fazem as alterações nos registradores P0, P1 e P2 (Trabalho 03)

MargemFim
	LDX #%11111111
  	STX PF0
  	STX PF1
  	STX PF2
  	JMP DecrementandoRegY

MargemMeio
	LDX #%00110000        
  	STX PF0
  	LDX #0
  	STX PF1
  	STX PF2
  	JMP DecrementandoRegY


	ORG $FFFA
	
InterruptVectors
	.word Reset          
	.word Reset  
	.word Reset         

END