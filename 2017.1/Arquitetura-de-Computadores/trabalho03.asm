	processor 6502
        
	include "vcs.h"

YMissel = $80;
LinhaVisivelMissel = $81;

;Variáveis usadas na troca de cores quando pressionar o 'gatilho'
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

	STA Delay		;Atribui 0 a variável 'Delay'

	LDA #00
	STA COLUBK 		          
	LDA #65
	STA CorMissel	;Atribui a cor inicial do Míssel a variável 'CorMissel'
	STA COLUP0 
	LDA #95
	STA YMissel

	sta RESM0	
	 	
	LDA #$20
	STA NUSIZ0 		
	

	;Configurando cor e controle do Playfield
	LDA #25
	STA CorBorda	;Atribui a cor inicial do playfield a variável 'CorBorda'
	STA COLUPF             
	LDA #%00000001
	STA CTRLPF		;Reflexão


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


;COMEÇO: verificação do movimento do míssel em X e Y (já explicados no trabalho anterior).
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
;FIM: fim da verificação do movimento do míssel em X e Y.
	

;	Aqui será verificado se o botão (gatilho) foi pressionado ou não. Para isso, carregamos um valor atribuído ao estado do botão
;no Registrador A. Depois usamos o 'BMI' para verificar se o botão foi pressionado. Se ele não tiver sido pressionado, ele fará
;um Branch para a label 'NaoBotao'. Caso tenha sido pressionado, ele inverterá a cor do playfield com a cor do míssel.
;	Como fiz a inversão de cores? Primeiro, carreguei o valor de CorMissel no registrador A e CorBorda no registrados X. Depois, 
;setei o valor de X na variável CorMissel e no registrador COLUP0. Também setei o valor de A na variável CorBorda e no registrador
;COLUPF. Com isso, inverti as cores e atualizei o valor das variáveis.
;	Obs: Ao implementar essa troca de cores foi verificado um bug. Quando o botão que representa o 'gatilho' é pressionado,
;ele não lê apenas um click, ou seja, o código trocava de cor várias vezes em um intervalo inferior a 1 segundo, muitas vezes voltando
;a cor original dificultando ao usuário que conseguisse trocar as cores. Para resolver esse problema, usei a variável Delay. No começo
;do programa, atribui seu valor em 0. Se o gatilho for pressionado uma vez, ele fará as trocas de cores e atribuirá o valor 10 na ;variável Delay. Enquanto essa variável não for igual a 0, ele não verificará se o botão foi pressionado, e pulará direto para a label
;que decrementa o valor da variável 'Delay'. Essa resolução foi uma espécie de gambiarra, contudo foi eficiente.

	LDY Delay
	CPY #0
	BNE DecrementaDelay	;Se Delay não for igual a 0, pula para label 'DecrementaDelay'.
	LDA INPT4		;Lê o input do botao
	BMI NaoBotao	;Pula para 'NaoBotao' caso o botão não tenha sido pressionado.
	LDA #10
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

	;Aqui, setamos a configuração inicial do playfield. No início, ele irá aparecer do começo ao fim da tela (margem superior).
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

	
;	Aqui, trocaremos a configuração do Playfield de acordo com o valor do registrador Y. Inicialmente, o reg Y tem o valor de 191
;e será decrementado em 1 até ser 0 (desenhando as linhas na tela). Usamos a instrução 'CPY' para comparar o valor do reg Y. Se ele
;for igual a 184, significa que as 8 linhas iniciais já foram desenhadas, ou seja, pularei para a label 'MargemMeio', que muda as 
;configurações do playfield (P0,P1 e P2) para que as próximas linhas representem uma margem lateral na direita e esquerda.
;	Quando o reg Y for igual a 9, ele pulará agora para label 'MargemFim', que fará com que as configurações dos registradores de 
;Playfield fiquem igual aos das primeiras 8 linhas (ocupando toda a linha horizontal).

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



;	Aqui são as labels que fazem as alterações nos registradores P0, P1 e P2, para que a margem seja desenhada corretamente.
;Após fazer as alterações necessárias, ele fará um JUMP para label 'DecrementandoRegY', voltando ao loop.

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