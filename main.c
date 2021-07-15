#include <stdio.h>
#include <stdlib.h>
#include<time.h>

int carregaTamanhoMatriz();
int** alocaMemoriaMatriz(int);
int erros(int);
void carregaMatriz(int**, int);
void imprimeMatriz(int**, int);
void delimitaBordas(int**, int);
void processarMatriz(int**, int**,int,int[3][3]);
void liberaMatriz(int **, int);

int main(){

  int **fonte,tam,**resultado; 

  int filtro[3][3]={
      {-1,0,1},
      {-2,0,2},
      {-1,0,1}
  };
  
  tam = carregaTamanhoMatriz();
  fonte=alocaMemoriaMatriz(tam);
  resultado=alocaMemoriaMatriz(tam);
  if(fonte==NULL||resultado==NULL){
    return erros(0);
  }
  carregaMatriz(fonte, tam);
  printf("--------------------\n");
  printf("Matriz Fonte(gerada aleatoriamente):\n");
  imprimeMatriz(fonte, tam);
  processarMatriz(fonte,resultado,tam,filtro);
  printf("--------------------\n");
  printf("Matriz Resultado:\n");
  imprimeMatriz(resultado,tam);
  liberaMatriz(fonte,tam);
  liberaMatriz(resultado,tam);
  return 0;
}

int carregaTamanhoMatriz(){ //Pede para o usuario o tamanho da matriz
  int tam;
  printf("Digite o tamanho da matriz: ");
  scanf("%i", &tam);
  return tam;
}

int** alocaMemoriaMatriz(int tam){//Aloca memoria para a matriz
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

void carregaMatriz(int** mat, int tam){//Carrega a matriz com numeros aleatorios
  srand(time(NULL));
  int i,j;
  for(i=0;i<tam;i++){
    for(j=0;j<tam;j++){
      mat[i][j]=rand() % 10;
    }
  }
}
void imprimeMatriz(int** mat, int tam){//Imprime a matriz
  int i,j;
  for(i=0;i<tam;i++){
    for(j=0;j<tam;j++){
      printf("%*d|",3,mat[i][j]);
    }
    printf("\n");
  }
}
void processarMatriz(int** fonte, int** resultado,int tam,int filtro[3][3]){
  int i,j,k,l,soma;
  //Coloca 0 nas bordas de resultado
  delimitaBordas(resultado,tam);
  for(i=0;i<tam-2;i++){
    for(j=0;j<tam-2;j++){
      soma = 0;
      for(k=0;k<3;k++){
        for(l=0;l<3;l++){
          soma = soma + (fonte[i+k][j+l] * filtro[k][l]);
        }
      }
      resultado[i+1][j+1]=soma;
    }
  }
}

void liberaMatriz(int**mat, int tam){//Libera a memória da matriz
  int i;
  for(i=0;i<tam;i++){
    free(mat[i]);
  }
  free(mat);
}
void delimitaBordas(int** mat, int tam){//Coloca 0 nas bordas da matriz
    int i,j;
    for(i=0;i<tam;i++){
        for(j=0;j<tam;j++){
            if((i==0)||(j==0)||(i==tam-1)||(j==tam-1)){
                mat[i][j]=0;
            }
        }
  }
}
