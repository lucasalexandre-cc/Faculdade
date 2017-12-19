#include <stdio.h>
#include <stdlib.h>
#include "agencia.h"
#include "conta_corrente.h"

int main(void){
    while(1){
        int comando = 0;
        printf("--- Menu ---\n");
        printf("1- Cadastrar agência\n");
        printf("2 - Cadastrar conta corrente\n");
        printf("3 - Imprimir uma agência\n");
        printf("4 - Imprimir todas as agências\n");
        printf("5 - Imprimir uma conta corrente\n");
        printf("6 - Imprimir todas as contas correntes\n");
        printf("7 - Sair\n");
        printf("Informe o comando: ");
        scanf("%i", &comando);

        if(comando == 1){   //Cadastrar agencia
            //Abre o arquivo para escrita, preservando o conteudo caso exista
            FILE *out = fopen("agencia.dat", "ab");
            //Inputs
            int codigo; char nome[50]; char nome_gerente[50];
            printf("Informe o codigo da agencia: ");
            scanf("%i", &codigo);
            printf("Informe o nome da agencia: ");
            scanf("%s", nome);
            printf("Informe o nome do gerente: ");
            scanf("%s", nome_gerente);
            //Cria um ponteiro para 'Agencia'
            Agencia *aux = criaAgencia(codigo, nome, nome_gerente);
            //Salva no arquivo
            salva_agencia(aux, out);
            //Da free no ponteiro
            free(aux);
            //Fecha o arquivo
            fclose(out);
            printf("\n Agencia cadastrada com sucesso! \n\n");
        }
        if(comando == 2){   //Cadastrar conta corrente
            //Abre o arquivo para escrita, preservando o conteudo caso exista
            FILE *out = fopen("conta_corrente.dat", "ab");
            //Inputs
            int cod_conta; int cod_agencia; double saldo;
            printf("Informe o codigo da conta corrente: ");
            scanf("%i", &cod_conta);
            printf("Informe o codigo da agencia: ");
            scanf("%i", &cod_agencia);
            printf("Informe o saldo da conta: ");
            scanf("%lf", &saldo);
            //Cria um ponteiro para 'conta corrente'
            Conta_Corrente *aux = criaContaCorrente(cod_conta, cod_agencia, saldo);
            //Salva no arquivo
            salva_conta_corrente(aux, out);
            //Libera o ponteiro
            free(aux);
            //Fecha o arquivo
            fclose(out);
            printf("\n Conta Corrente cadastrada com sucesso! \n\n");
        }
        if(comando == 3){   //Imprimir UMA agencia
            //Abre o arquivo para leitura
            FILE *in = fopen("agencia.dat", "rb");
            //Se 'in' == NULL, significa que ele ainda nao existe, ou seja,
            //nenhuma agencia foi cadastrada ate agora
            if(!in) printf("\nNenhum cadastro existente ate o momento.\n\n");
            else{   //Caso o arquivo ja exista
                int cod_agencia;
                printf("Informe o codigo da agencia: ");
                scanf("%i", &cod_agencia);
                imprimindoUmaAgencia(in, cod_agencia);
                //Fecha o arquivo
                fclose(in);
            }
        }
        if(comando == 4){   //Imprimir todas as agencias
            FILE *in = fopen("agencia.dat", "rb");
            if(!in) printf("\nNenhum cadastro existente ate o momento.\n\n");
            else{
                imprimindoTodasAgencias(in);
                fclose(in);
            }

        }
        if(comando == 5){   //Imprimir UMA conta corrente
            FILE *in = fopen("conta_corrente.dat", "rb");
            if(!in) printf("\nNenhum cadastro existente ate o momento.\n\n");
            else{
                int cod_conta; int cod_agencia;
                printf("Informe o codigo da agencia: ");
                scanf("%i", &cod_agencia);
                printf("Informe o codigo da conta corrente: ");
                scanf("%i", &cod_conta);
                imprimindoUmaContaCorrente(in, cod_agencia, cod_conta);
                fclose(in);
            }

        }
        if(comando == 6){   //Imprimindo toas as conta correntes
            FILE *in = fopen("conta_corrente.dat", "rb");
            if(!in) printf("\nNenhum cadastro existente ate o momento.\n\n");
            else{
                imprimindoTodasContasCorrentes(in);
                fclose(in);
            }
        }
        if(comando == 7) break; //Sair
    }
    return 0;
}