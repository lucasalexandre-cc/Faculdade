#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "cliente.h"
#include "encadeamento_interior.h"


void cria_hash(char *nome_arquivo_hash, int tam)
{
    FILE *hash = fopen(nome_arquivo_hash, "w+b");
    int i;
    Cliente *atual;
    for(i=0; i<tam;i++){
        atual = cliente(-1,"",i, LIBERADO);
        salva_cliente(atual, hash);
    }
    fclose(hash);
	//TODO: criar a tabela hash
}

int busca(int cod_cli, char *nome_arquivo_hash, int tam, int *encontrou)
{
    FILE *hash = fopen(nome_arquivo_hash, "r+b");
    
    int mod = cod_cli%tam, end=mod, primeiroLiberado = -1, encontradoRemovido=-1;
    Cliente *atual;
    fseek(hash, mod * tamanho_cliente(), SEEK_SET);
    
    while(atual=le_cliente(hash)){
        if(atual->cod_cliente % tam == mod){
            if(atual->cod_cliente == cod_cli){
                if(atual->flag==LIBERADO){
                    *encontrou = 0;
                    encontradoRemovido = end;
                    
                    if(atual->prox == end){
                        fseek(hash, 0, SEEK_END);
                    }else{
                        end = atual->prox;
                        fseek(hash, atual->prox * tamanho_cliente(), SEEK_SET);
                    }
                }else{
                    *encontrou = 1;
                    fclose(hash);
                    return end;
                }
            }
            else{
                if(atual->flag == LIBERADO && primeiroLiberado==-1)
                    primeiroLiberado = end;
                
                if(atual->prox == end){
                    fseek(hash, 0, SEEK_END);
                }else{
                    end = atual->prox;
                
                    fseek(hash, atual->prox * tamanho_cliente(), SEEK_SET);
                }
            }
        }else{
            end++;
            
        }
    }
    
    if(encontradoRemovido!=-1){
        fclose(hash);
        return encontradoRemovido;
    }

    *encontrou = 0;
    fclose(hash);
    return primeiroLiberado;
    
}

int insere(int cod_cli, char *nome_cli, char *nome_arquivo_hash, int tam)
{
	FILE *hash = fopen(nome_arquivo_hash, "r+b");

    int mod = cod_cli%tam;
    int pos_retorno = mod;  //A posição que será inserido
    int alterar = mod; Cliente *alterar_cli;//Usado para alterar valor de 'prox' em alguns casos

    Cliente *atual;
    fseek(hash, mod * tamanho_cliente(), SEEK_SET);
    while(atual = le_cliente(hash)){
        if(atual->cod_cliente%tam == mod || atual->flag == LIBERADO){
            if(atual->cod_cliente == cod_cli && atual->flag == OCUPADO){//Já existe e ta ocupado
                fclose(hash);
                return -1;
            }
            else if(atual->flag == LIBERADO){ //Espaco liberado
                fseek(hash, -tamanho_cliente(), SEEK_CUR);
                Cliente *aux = cliente(cod_cli, nome_cli, atual->prox, OCUPADO);
                salva_cliente(aux, hash);
                free(aux);
                if(pos_retorno != alterar){ //Se forem diferentes, é porque tenho que alterar um valor de proximo de um cliente antigo
                    alterar_cli->prox = pos_retorno;
                    fseek(hash, alterar*tamanho_cliente(), SEEK_SET);
                    salva_cliente(alterar_cli, hash);
                }
                fclose(hash);
                return pos_retorno;
            }
            else if(atual->prox != pos_retorno){ //Diferente, mas ainda tem proximo
                pos_retorno = atual->prox;
                alterar = atual->prox;
                fseek(hash, atual->prox * tamanho_cliente(), SEEK_SET);
                alterar_cli = le_cliente(hash);
                fseek(hash, -tamanho_cliente(), SEEK_CUR);
            }else{  //Diferente e nao tem mais proximo  (final)
                pos_retorno++;
            }
        }else pos_retorno++;
    }
    //Caso não tenha encontrado nenhum lugar para inserir ate agora
    //insiro no fim do arquivo
    Cliente *aux = cliente(cod_cli, nome_cli, pos_retorno, OCUPADO);
    salva_cliente(aux, hash);
    free(aux);
    return pos_retorno;
}

//Parte que o Luan vai implementar
int exclui(int cod_cli, char *nome_arquivo_hash, int tam)
{
	//TODO: Inserir aqui o codigo do algoritmo de remocao
    return INT_MAX;
}
