#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Funções auxiliares
void troca(int* v, int a, int b){
	int aux = v[b];
	v[b] = v[a];
	v[a] = aux;
	return;
}

int estaOrdenado(int * v, int tam){
	int i;
	for(i = 0; i < tam-1 ; i++){
		if(v[i] > v[i+1]) return 0;
	}
	return 1;
}

int* copy_vector(int *vet, int tam){
	int* new = (int*)malloc(sizeof(int)*tam);
	int i;
	for(i=0; i<tam; i++){
		new[i] = vet[i];	
	} 
	return new;
}

//Merge Sort
void merge(int *v, int *c, int i, int m, int f) {
  int z, iv = i, ic = m + 1;

  for (z = i; z <= f; z++) c[z] = v[z];

  z = i;

  while (iv <= m && ic <= f) {
    if (c[iv] < c[ic]) v[z++] = c[iv++];
    else v[z++] = c[ic++];
  }

  while (iv <= m) v[z++] = c[iv++];

  while (ic <= f) v[z++] = c[ic++];
}

void sort(int* v, int* c, int i, int f){
	if(i >= f) return;
	sort(v, c, i, (i+f)/2);
	sort(v, c, (i+f)/2 + 1, f);
	if(v[(i+f)/2] <= v[(i+f)/2 + 1])return;
	merge(v, c, i, (i+f)/2, f);
}

void mergesort(int* v, int n){
	int* c = (int*)malloc(sizeof(int)*n);
	sort(v, c, 0, n-1);
	free(c);
}	

//Insertion Sort
void insertionsort(int* vetor, int tam){
	int fora, dentro;
	for(fora = 1; fora < tam; fora++){
		dentro = fora;
		while(vetor[dentro-1] > vetor[dentro] && dentro > 0){
			troca(vetor, dentro, dentro-1);
			dentro--;
		}
	}
	return;
}

//Selection Sort
int achaMin(int* v, int i, int n){ 
	int j, im = i, min = v[i];
	for(j = i; j < n; j++){
		if(v[j] < v[im]){
			im = j;
			min = v[im];
		}
	}
	return im;
}

void selectionsort(int* v, int n){ //testado
	int i, min;
	for(i = 0; i < n-1; i++){
		min = achaMin(v, i, n);
		troca(v, i, min);
	}
	return;
}

//Testes
int main(){
	//Input
	int n, i;
	clock_t inicio, fim, total;
	double resultado;
	scanf("%d", &n);
	int* input = (int*)malloc(sizeof(int)*n);
	for(i = 0; i < n; i++){
		scanf("%d", &input[i]);
	}
	printf("Tamanho do vetor: %d\n", n);
	printf("Está ordenado? %d\n", estaOrdenado(input, n));

	//Selection Sort
	int *selection = copy_vector(input, n);
	inicio = clock();
	selectionsort(selection, n);
	fim = clock();
	printf("Selection Sort ordenou? %d\n", estaOrdenado(selection, n));
	resultado = (double)(fim - inicio)/CLOCKS_PER_SEC;
	printf("%f\n", resultado);
	free(selection);

	//Insertion Sort
	int *insertion = copy_vector(input, n);
	inicio = clock();
	insertionsort(insertion, n);
	fim = clock();
	printf("Insertion Sort ordenou? %d\n", estaOrdenado(insertion, n));
	resultado = (double)(fim - inicio)/CLOCKS_PER_SEC;
	printf("%f\n", resultado);
	free(insertion);

	//Merge Sort
	int *merge = copy_vector(input, n);
	inicio = clock();
	mergesort(merge, n);
	fim = clock();
	printf("Merge Sort ordenou? %d\n", estaOrdenado(merge, n));
	resultado = (double)(fim - inicio)/CLOCKS_PER_SEC;
	printf("%f\n", 	resultado);
	free(merge);

	free(input);
	return 0;
}
