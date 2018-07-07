#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int sss1(int* v, int n, int s){
    int i, sum = 0;
    for(i = 0; i < n; i++){
        if((sum < s && v[i] > 0) || (sum > s && v[i] < 0)) {
        	sum += v[i];
        }
        if(sum == s) return 1;
    }
    return 0;
}

int real_index(int v, int n) {
	if(v >= 0) return v;
	return n+v;
}
int sss2(int* v, int t, int s){
    int i, j, constant, n = 0, p = 0;
    
    for(i = 0; i < t; i++){
        if(v[i] < 0) n += v[i];
        else p += v[i];
    }
    if(s < n || s > p) return 0;

    constant = p-n+1;
    bool **dp = (bool **) malloc(sizeof(bool*)*t);
    for(i=0; i<t; i++) dp[i] = (bool *) malloc(sizeof(bool)*constant);

    for(i = 0; i < t; i++){
        for(j = 0; j < constant; j++){
        	if(!i && j != real_index(v[0], constant)) dp[i][j] = false;
        	else if(!i && j == real_index(v[0], constant)) dp[i][j] = true;
        	else if((dp[i-1][real_index(j, constant)]) || (dp[i-1][real_index(j-v[i], constant)]) || (j == v[i])) dp[i][j] = true;
        	else dp[i][j] = false;
        }
    }
    return dp[t-1][real_index(s, constant)];
}

int main(){
    int i, n, s;
    int* v = (int*)malloc(sizeof(int)*n);
    scanf("%d", &n);
    scanf("%d", &s);
    for(i = 0; i < n; i++){
        scanf("%d", &v[i]);
    }

    printf("Algoritmo 1: %d\n", sss1(v, n, s));
    printf("Algoritmo 2: %d\n", sss2(v, n, s));

    return 0;
}
