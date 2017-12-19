#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//dentro do processo filho, o pid tem valor 0
//dentro do processo pai, o pid tem o valor do processo filho
//fork() retorna um valor negativo, em caso de erro
int main(void){
    pid_t pid;

    pid = fork();
    if(pid < 0){    //Ocorreu um erro
        perror("fork");
        exit(1);
    }
    if(pid == 0){   //Esse código será executado no processo 'filho'
        printf("Pid do filho: %d\n", getpid());
    }
    else{   //Esse código será executado pelo processo 'pai'
        printf("Pid do pai: %d\n", getpid());
    }
    //Obs: getpid() retorna o 'real' pid do processo

    printf("Esta regiao sera executada por ambos os processos\n");

    return 0;
}