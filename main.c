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
int formula(int**,int[3][3]);
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
  int i,j;
  int **temp;
  //Coloca 0 nas bordas de resultado
  delimitaBordas(resultado,tam);
  for(i=1;i<tam-1;i++){
    for(j=1;j<tam-1;j++){
      //Aloca a memória para temp
      temp = alocaMemoriaMatriz(3);
      //Pega os valores vizinhos
      temp[0][0]=fonte[i-1][j-1];
      temp[0][1]=fonte[i-1][j];
      temp[0][2]=fonte[i-1][j+1];
      temp[1][0]=fonte[i][j-1];
      temp[1][1]=fonte[i][j];
      temp[1][2]=fonte[i][j+1];
      temp[2][0]=fonte[i+1][j-1];
      temp[2][1]=fonte[i+1][j];
      temp[2][2]=fonte[i+1][j+1];
      //Chama a função que realiza o calculo
      resultado[i][j]=formula(temp,filtro);
      //Libera a memória
      liberaMatriz(temp,3);
    }
  }
}
int formula(int**temp,int filtro[3][3]){//Calcula o valor
  int i,j,soma=0;
  for(i=0;i<3;i++){
    for(j=0;j<3;j++){
      soma+= temp[i][j]*filtro[i][j];
    }
  }
  return soma;

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
