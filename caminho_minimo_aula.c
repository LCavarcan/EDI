#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define tam_fila 100  //tamanho max. fila
#define N 5       //Tamanho da matriz de conex�es e vetor de dist�ncias

//ED para fila
//------------------------------------------------------
//Tipo fila
typedef struct
{
  int A[tam_fila];    //Simplificacao p/ aplicacao
  int inicio, fim;
} fila;
//------------------------------------------------------

//Opera��es da fila
//------------------------------------------------------
//Cria uma fila vazia
void Definir(fila *q) {
   q->fim = 0;
   q->inicio = 0;
   //Obs: ponteiro de in�cio atrasado: aponta para uma posi��o anterior ao in�cio
}

//Retorna true se fila n�o cont�m elementos, false caso contr�rio
bool Vazia(fila *q) {
	if (q->inicio == q->fim)
   		return true;
   	return false;
}

//Retorna true se fila cheia, false caso contr�rio
bool Cheia(fila *q) {
	if (q->inicio == ((q->fim + 1) % tam_fila))
		return true;
	return false;
   //Obs: os dois ponteiros diferem de uma posi��o
}

//Adiciona um elemento no fim da fila q (retorna true se sucesso, false c.c.) 
//Note que uma posi��o da fila nunca ser� preenchida
bool Inserir(fila *q, int elem) {	
   if (Cheia(q))
      return false;
   q->fim = (q->fim + 1) % tam_fila;
   q->A[q->fim] = elem;
   return true;
}

//Remove um elemento do in�cio da fila q (retorna true se sucesso, false c.c.)
bool Remover(fila *q, int *elem) {
   if (Vazia(q))
      return false;
   q->inicio = (q->inicio + 1) % tam_fila;
   *elem = q->A[q->inicio];
   return true;
}
//------------------------------------------------------

int minimo(int pos, int C[N], int A[N][N], int dist[N]) {
   int menor = 1000, novo;
   
   for(int j=0;j<N;j++) {
      if(A[pos][j]!=0) {
         if(C[j] > dist[j] + A[pos][j]) {
            C[j] = dist[j] + A[pos][j];
         }
      }
      
      if(C[j]<menor) {
         menor = C[j];
         novo = j;
      }
   }

   for (int i=0; i<N; i++)
	   printf("dist[%d]: %d\n", i, C[i]);	

   return novo;
}


//------------------------------------------------------
//Principal
//matriz A (de adj.): representa as conex�es entre as cidades 0,...,N-1, 
//vetor 'dist': dist[i] � a dist�ncia da cidade fixada 'c' at� cada cidade 'i'
int main() {
	//Inicializa��o da matriz com as cidades interconectadas
	int A[N][N] = { {0,10,5,0,0}, {0,0,3,1,0}, {0,2,0,9,2}, {0,0,0,0,6}, {7,0,0,4,0} };
	int dist[N];
   int C[N];
	int i, j, c = 0;
	fila F;
	
	for (j=0; j<N; j++)  
	    dist[j] = 1000;       //Seta dist[j] = inf, todo j
    
	dist[c] = 0;
    Definir(&F);           //Cria fila
    Inserir(&F,c);         //Insere na fila

    //Roda at� que todos os n�s tenham sido checados pelo crit�rio abaixo: 
	//tira da fila uma cidade i, e coloca na fila as cidades vizinhas j com distancias � computadas
   int menor=1000, B[N], completo;
   
   for(i=0;i<N;i++) {
      B[i] = 1;
      completo = 1;
   }

   for(j=0;j<N;j++) {
      i = minimo(i, C, A, dist);
   }
	
	//Imprime vetor de dist�ncias de 'c' para as demais cidades 'i'
	for (i=0; i<N; i++)
	   printf("dist[%d]: %d\n", i, C[i]);	
}
