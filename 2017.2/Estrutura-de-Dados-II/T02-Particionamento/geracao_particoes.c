#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "geracao_particoes.h"
#include "stdio.h"
#include "stdlib.h"
#include "cliente.h"
#include <limits.h>
#include <string.h>


void esvaziarReservatorio(FILE *res, Cliente *memoria, int M);
void esvaziarMemoria(FILE *out, Cliente *memoria, int M);
int achando_indice_menor_cod(Cliente *vetor, int M);
void zerarMemoria(Cliente *mem, int M);

void classificacao_interna(char *nome_arquivo_entrada, Nomes *nome_arquivos_saida, int M)
{
    //TODO: Inserir aqui o codigo do algoritmo de geracao de particoes
}

void selecao_com_substituicao(char *nome_arquivo_entrada, Nomes *nome_arquivos_saida, int M)
{
    //TODO: Inserir aqui o codigo do algoritmo de geracao de particoes
}

//M = registros na memoria
//n = registros do reservatorio
void selecao_natural(char *nome_arquivo_entrada, Nomes *nome_arquivos_saida, int M, int n)
{
    FILE *in, *reservatorio;
    int qnts_clientes_reservatorio = 0;

    //Abrindo arquivos e verificando possiveis erros
    if(((in = fopen(nome_arquivo_entrada,"rb"))==NULL) || (reservatorio = fopen("reservatorio.dat", "w+b"))==NULL){
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }

    //Criando a 'memoria e um indice que indica quantos 'Clientes' estao armazenados
    Cliente *memoria = (Cliente *) malloc(sizeof(Cliente)*M);
    int qnts_clientes_memoria = 0;

    //Criando a primeira particao
    FILE *part = fopen(nome_arquivos_saida->nome,"wb");

    zerarMemoria(memoria, M);
    int i = 0;  int flag = INT_MIN;
    while(fread(&memoria[i].cod_cliente, sizeof(int), 1, in) > 0){
        fread(memoria[i].nome,sizeof(char), sizeof(memoria[i].nome), in);
        i++; qnts_clientes_memoria++;
        if(qnts_clientes_memoria == M){
            i = achando_indice_menor_cod(memoria, M);
            if(i != -1 && memoria[i].cod_cliente >= flag){//Escrever na particao
                flag = memoria[i].cod_cliente;
                fwrite(&memoria[i].cod_cliente, sizeof(int), 1, part);
                fwrite(memoria[i].nome, sizeof(char), sizeof(memoria[i].nome), part);
                memoria[i].cod_cliente = -1;
                qnts_clientes_memoria--;
            }else if (i != -1 && memoria[i].cod_cliente < flag){//Escrever no reservatorio
                fwrite(&memoria[i].cod_cliente, sizeof(int), 1, reservatorio);
                fwrite(memoria[i].nome, sizeof(char), sizeof(memoria[i].nome), reservatorio);
                memoria[i].cod_cliente = -1;
                qnts_clientes_memoria--;
                qnts_clientes_reservatorio++;
                if(qnts_clientes_reservatorio == n){//Reservatorio encheu
                    esvaziarMemoria(part, memoria, M);
                    fclose(part);


                    nome_arquivos_saida = nome_arquivos_saida->prox;
                    part = fopen(nome_arquivos_saida->nome, "wb");
                    esvaziarReservatorio(reservatorio, memoria, M);
                    qnts_clientes_memoria = M;
                    qnts_clientes_reservatorio = 0;
                    fclose(reservatorio);
                    reservatorio = fopen("reservatorio.dat", "w+b");

                    i = achando_indice_menor_cod(memoria, M);
                    flag = memoria[i].cod_cliente;
                    fwrite(&memoria[i].cod_cliente, sizeof(int), 1, part);
                    fwrite(memoria[i].nome, sizeof(char), sizeof(memoria[i].nome), part);
                    memoria[i].cod_cliente = -1;
                    qnts_clientes_memoria--;
                }
            }
        }
    }
    if(qnts_clientes_memoria != 0){
        esvaziarMemoria(part, memoria, M);
        fclose(part);

        nome_arquivos_saida = nome_arquivos_saida->prox;
        if(nome_arquivos_saida && qnts_clientes_reservatorio != 0){
            part = fopen(nome_arquivos_saida->nome, "w+b");
            esvaziarReservatorio(reservatorio, memoria, n);
            esvaziarMemoria(part, memoria, M);
            fclose(part);
            qnts_clientes_reservatorio = 0;
        }
    }

    if(qnts_clientes_reservatorio != 0){
        nome_arquivos_saida = nome_arquivos_saida->prox;
        part = fopen(nome_arquivos_saida->nome, "w+b");

        esvaziarReservatorio(reservatorio, memoria, n);
        esvaziarMemoria(part, memoria, M);

        fclose(part);
    }


}

//Retorna -1 caso nao tenha mais cliente na lista
//Retorna o indice no vetor do menor cliente
int achando_indice_menor_cod(Cliente *vetor, int M){
    int i = 0; int flag, resp;
    //Pegando o primeiro elemento diferente de -1
    while(i<M && vetor[i].cod_cliente == -1) i++;
    if(i == M) return -1;   //Significa que a memoria so esta com 'lixo'
    flag = vetor[i].cod_cliente;
    resp = i;
    //Pegando o menor indice do cod_cliente
    for(i = 0; i<M; i++){
        if(vetor[i].cod_cliente != -1 && vetor[i].cod_cliente < flag){
            flag = vetor[i].cod_cliente;
            resp = i;
        }
    }
    return resp;
}

//Passa tudo que ainda tem na memoria principal para o reservatorio
void esvaziarMemoria(FILE *out, Cliente *memoria, int M){
    int i = achando_indice_menor_cod(memoria, M);
    int flag;
    while(i != -1){
        fwrite(&memoria[i].cod_cliente, sizeof(int), 1, out);
        fwrite(memoria[i].nome, sizeof(char), sizeof(memoria[i].nome), out);

        flag = memoria[i].cod_cliente;
        memoria[i].cod_cliente = -1;
        i = achando_indice_menor_cod(memoria, M);
    }

    int maxi = INT_MAX;
    if(flag != maxi){
        fwrite(&maxi, sizeof(int), 1, out);
        fwrite("", sizeof(char), sizeof(memoria[0].nome), out);
    }
}

void esvaziarReservatorio(FILE *res, Cliente *memoria, int M){
    rewind(res);
    int i = 0;
    while(i < M && fread(&memoria[i].cod_cliente, sizeof(int), 1, res) > 0){
        fread(memoria[i].nome,sizeof(char), sizeof(memoria[i].nome), res);
        i++;
    }
}

void zerarMemoria(Cliente *mem, int M){
    int i;
    for(i = 0; i<M; i++){
        mem[i].cod_cliente = -1;
    }
}