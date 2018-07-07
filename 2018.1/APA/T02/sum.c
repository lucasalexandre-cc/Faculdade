#include <stdio.h>
#include <stdlib.h>

int main(){
    int n, i;
    scanf("%i", &n);
    
    int val;
    
    int min_local, min_global;
    min_local = min_global = 0;
    
    int i_local, i_global, f_global, f_local;
    i_local = i_global = f_global = f_local = -1;
    for(i=0; i<n; i++){
        scanf("%i", &val);
        
        f_local = i;
        if(i_local == -1){
            i_local = f_local;
        }
        
        min_local += val;
        if(min_local >= 0){
            i_local = f_local = -1;
            min_local = 0;
        }
        else if(min_local < min_global){
            min_global = min_local;
            if(i_global == -1) i_global = f_global = i;
            else{
                f_global = i;
                if(i_global != i_local) i_global = i_local;
            }
        }
    }   
    printf("Da posição %i até a posição %i, sendo o menor valor: %i\n", i_global, f_global, min_global);
}

