#include <stdio.h>
#include <stdlib.h>
#include<time.h>

int carregaTamanhoMatriz();
int** alocaMemoriaMatriz(int);
int erros(int);
void carregaMatriz(int**, int);
void imprimeMatriz(int**, int);
void delimitaBordas(int**, int);

int main(){
  int **fonte,tam,**resultado, **filtro; 
  tam = carregaTamanhoMatriz();
  fonte=alocaMemoriaMatriz(tam);
  resultado=alocaMemoriaMatriz(tam);
  filtro=alocaMemoriaMatriz(3);
  if(fonte==NULL){
    return erros(0);
  }
  carregaMatriz(fonte, tam);
  printf("Matriz fonte:\n");
  imprimeMatriz(fonte, tam);
  return 0;
}

int carregaTamanhoMatriz(){
  int tam;
  printf("Digite o tamanho da matriz: ");
  scanf("%i", &tam);
  return tam;
}

int** alocaMemoriaMatriz(int tam){
  int **m;
  int i;
  m = (int*) malloc(sizeof(int) * tam);
  if(m==NULL) {
     return (NULL);
  }
  for(i=0; i<tam;i++){
    m[i]=(int*) malloc(sizeof(int) * tam);
    if(m==NULL) {
     return (NULL);
    }
  }
  return(m);
}

int erros(int erro){
    printf("Erro ao alocar memória para o vetor! (Erro %i)\n", erro);
    return erro;
}

void carregaMatriz(int** mat, int tam){
  srand(time(NULL));
  int i,j;
  for(i=0;i<tam;i++){
    for(j=0;j<tam;j++){
      mat[i][j]=rand() % 10;
    }
  }
}
void imprimeMatriz(int** mat, int tam){
  int i,j;
  for(i=0;i<tam;i++){
    for(j=0;j<tam;j++){
      printf("%d ",mat[i][j]);
    }
    printf("\n");
  }
}

void delimitaBordas(int** mat, int tam){
    int i,j;
    for(i=0;i<tam;i++){
        for(j=0;j<tam;j++){
            if((i==0)||(j==0)||(i==tam-1)||(j==tam-1)){
                mat[i][j]=0;
            }
        }
  }
}
