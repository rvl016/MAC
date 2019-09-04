// Este arquivo: mst-prim.c
// Data: 2019-07-28
// Autor: Paulo Feofiloff
//
// Este programa testa várias implementações do algoritmo de Prim para o
// problema MST (= minimum spanning tree = árvore geradora de custo
// mínimo). Cada implementação recebe um grafo não-dirigido conexo G com
// custos nas arestas e devolve uma MST de G.
//
// O grafo G pode ser aleatório (com V vértices e E arestas) ou descrito
// num arquivo de texto (veja formato na documentação da função
// GRAPHinputLists_C() em GRAPHlists.h. Invocação:
//
// $ ./mst-prim -vV -eE -sS -fF -d -p
//
// Parâmetros:
//
//   -vV  V é o número de vértices de G
//   -eE  E é o número de arestas de G
//   -sS  S é a semente do gerador de números aleatórios
//   -fF  F é o nome do arquivo de dados que descreve o grafo G por meio
//          de listas de adjacência
//    -d  para que o programa execute uma verificação (debug) dos
//          resultados produzidos por cada implementação 
//    -p  para pausa depois da execução de cada implementação (aguarda
//          um <Enter> do usuário para prosseguir)
//
// Exemplos:
//
// $ ./mst-prim
// $ ./mst-prim -v1000 -e20000 -s222 -d -p 
// $ ./mst-prim -f./dados/meugrafo.txt -d 
//
// Os argumentos na linha de comando podem ser fornecidos em qualquer
// ordem. Quaisquer argumento podem ser omitidos.
////////////////////////////////////////////////////////////////////////


#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "GRAPHlists.h"

// número de implementações testadas:
#define IMPLEMS 4

// no caso de grafo aleatório, os custos das arcos são escolhidos no
// intervalo fechado CMIN..CMAX
#define CMIN -9
#define CMAX  99



// As IMPLEMS implementações que testaremos
////////////////////////////////////////////////////////////////////////

// Nomes das funções:
string algname[IMPLEMS] = 
   {"UGRAPHmstP0", "UGRAPHmstP1", "UGRAPHmstP2", "UGRAPHmstP3"};

// Endereços das funções: 
// func[i] é ponteiro para i-ésima função do tipo 
// int FFF( UGraph, vertex *):
int (*func[IMPLEMS])( UGraph G, vertex pa[]) = 
   {&UGRAPHmstP0, &UGRAPHmstP1, &UGRAPHmstP2, &UGRAPHmstP3};
// (acho que o "&" é opcional)

int mstcost[IMPLEMS];
double elapsedTime[IMPLEMS];
bool debug = false;
bool pausa = false;



// Função que executa uma implementação
////////////////////////////////////////////////////////////////////////

// Aplica a função algname[i], apontada por func[i], ao grafo G. 
// Armazena o custo da MST resultante em mstcost[i], e armazena o tempo
// gasto em elapsedTime[i].
void 
run( int i, UGraph G) {
   printf( "\nImplementação %s\n", algname[i]);
   vertex *pa = mallocc( G->V * sizeof (vertex));
   double start = (double) clock () / CLOCKS_PER_SEC;
   mstcost[i] = func[i]( G, pa); // calcula MST
   double stop = (double) clock () / CLOCKS_PER_SEC;
   printf( "custo da MST: %d\n", mstcost[i]);
   elapsedTime[i] = stop - start;
   printf( "tempo: %f\n", elapsedTime[i]);

   // verificação dos resultados:
   if (debug) { 
      if (G->V < 30) {
         printf( "vetor de pais:");
         for (vertex v = 0; v < G->V; ++v) 
            printf( "\n %d: %d", v, pa[v]);
         printf( "\n");
      }
      int checkcost = 0;
      for (vertex v = 0; v < G->V; ++v) {
         if (pa[v] == v) continue;
         link a = G->adj[v];
         while (a->w != pa[v]) a = a->next;
         checkcost += a->cst;
      }
      if (checkcost != mstcost[i]) { 
         // verificação um tanto supérflua...
         printf( "\n\n***Erro: custo declarado da MST!\n\n");
         exit( EXIT_FAILURE);
      }
   }

   free( pa);
}



// Protótipos de funções auxiliares
////////////////////////////////////////////////////////////////////////

void wait( void);
bool overflowdanger( Graph G);
bool samecosts( Graph G);



// Função main
////////////////////////////////////////////////////////////////////////

int 
main( int na, char* arg[]) { 
   int V = 10; // default value
   int E = 15; // default value
   int seed = 1; // default value
   string filename = NULL; // default value

   // leitura dos argumentos na linha de comando:
   while (--na) {
      if (sscanf( arg[na], "-v%d", &V) == 1);
      else if (sscanf( arg[na], "-e%d", &E) == 1);
      else if (sscanf( arg[na], "-s%d", &seed) == 1);
      else if (strncmp( arg[na], "-f", 2) == 0) filename = arg[na]+2;
      else if (strncmp( arg[na], "-d", 2) == 0) debug = true;
      else if (strncmp( arg[na], "-p", 2) == 0) pausa = true;
      else {
         printf( "\nUsage: %s [-vV] [-eE] [-sS] [-fF] [-d] [-p]\n\n",
                 arg[0]);
         exit( EXIT_FAILURE);
      }
   }

   // grafo a ser processado:
   UGraph G;
   if (filename != NULL) {
      printf( "\ndata file: %s\n", filename);
      FILE *infile = fopen( filename, "r");
      G = UGRAPHinputLists_C( infile);
      fclose( infile);
      V = G->V;
      E = G->A/2;
   } else {
      if (E < V-1) E = V-1;
      if (E > V*(V-1)/2) E = V*(V-1)/2;
      srand( seed);
      G = UGRAPHrand1connected_C( V, E, CMIN, CMAX);
      printf( "\nseed: %d\n", seed);
      printf( "CMIN..CMAX: %d..%d\n", CMIN, CMAX);
   }
   printf( "V: %d\n", V);
   printf( "E: %d\n", E);
   printf( "IMPLEMS: %d\n", IMPLEMS);
   if (debug) printf( "debug: true\n");
   if (debug && V < 30) {
      printf( "\nlistas de adjacência (com custos):\n");
      UGRAPHshow_C( G);
   }
   if (pausa) wait( );

   if (debug) {
      if (!UGRAPHisConnected( G)) {
         printf( "\n\n***Erro: grafo não é conexo!\n\n");
         exit( EXIT_FAILURE); 
      }
      if (overflowdanger( G)) {
         printf( "\n\n***Perigo de overflow aritmético!\n\n");
         exit( EXIT_FAILURE); 
      }
      if (!samecosts( G)) {
         printf( "\n\n***Erro: Custo de arco antiparalelo!\n\n");
         exit( EXIT_FAILURE); 
      }
      printf( "\nGrafo verificado!\n");
      if (pausa) wait( );
   }

   // processamento do grafo G:
   for (int i = 0; i < IMPLEMS; ++i) {
      run( i, G); // executa algname[i]
      if (pausa) wait( );
   }

   // compara resultado das IMPLEMS implementações:
   if (debug) {
      for (int i = 0; i < IMPLEMS-1; ++i) {
         if (mstcost[i] != mstcost[i+1]) {
            printf( "\n\n***Erro: custos diferentes!\n\n");
            exit( EXIT_FAILURE); 
         }
      }
      printf( "\nTodas as implementações produziram o mesmo custo "
              "total.\n");
   }

   // limpeza final:
   printf( "\n");
   UGRAPHdestroy( G);
   return EXIT_SUCCESS;
}



// Funções auxiliares
////////////////////////////////////////////////////////////////////////

// Pausa à espera de um <Enter> do usuário (veja opção -p do programa).
void 
wait( void) {
   printf( "<Enter> para continuar");
   (void) getc( stdin);
}

// Decide se o pocessamento de G corre o risco de produzir overflow.
// Mais precisamente, verifica se a soma de todos os custos positivos é
// menor que INT_MAX e a soma de todos os custos negativos é maior que
// INT_MIN.
bool
overflowdanger( Graph G) {
   int somap = 0, soman = 0;
   for (vertex v = 0; v < G->V; ++v) {
      for (link a = G->adj[v]; a != NULL; a = a->next) {
         if (a->cst > 0) {
            if (a->cst < INT_MAX - somap) somap += a->cst;
            else return true;
         } else {
            if (a->cst > INT_MIN - soman) soman += a->cst;
            else return true;
         }
      }
   }
   return false;
}

// Decide se cada arco de G tem um antiparalelo de mesmo custo igual
// ao do arco.
bool
samecosts( Graph G) {
   for (vertex v = 0; v < G->V; ++v) {
      for (link a = G->adj[v]; a != NULL; a = a->next) {
         vertex w = a->w;
         link b = G->adj[w];
         while (b != NULL && b->w != v) b = b->next; // que lento!
         if (b == NULL || a->cst != b->cst) 
            return false;
      }
   }
   return true;
}


// Exemplos:
// 
// pf:~/mac0328-2019/SANDBOX$ ./mst/mst-prim -v2000 -e100000 -d
// 
// seed: 1
// CMIN..CMAX: -9..99
// V: 2000
// E: 100000
// IMPLEMS: 4
// debug: true
// 
// Grafo verificado!
// 
// Implementação UGRAPHmstP0
// custo da MST: -16291
// tempo: 12.133216
// 
// Implementação UGRAPHmstP1
// custo da MST: -16291
// tempo: 0.033792
// 
// Implementação UGRAPHmstP2
// custo da MST: -16291
// tempo: 0.016827
// 
// Implementação UGRAPHmstP3
// custo da MST: -16291
// tempo: 0.012963
// 
// As implementações produziram o mesmo custo total.
// 
// pf:~/mac0328-2019/SANDBOX$
// pf:~/mac0328-2019/SANDBOX$ ./mst/mst-prim -d
// 
// seed: 1
// CMIN..CMAX: -9..99
// V: 10
// E: 15
// IMPLEMS: 4
// debug: true
// 
// listas de adjacência (com custos):
//  0:  1 (60)
//  1:  9 (14)  8 ( 5)  5 (-8)  7 ( 6)  0 (60)  4 (94)
//  2:  6 (48)  4 (30)
//  3:  8 (91)  5 ( 8)
//  4:  8 (21)  6 ( 5)  1 (94)  2 (30)  9 (22)
//  5:  7 (74)  8 (57)  3 ( 8)  1 (-8)
//  6:  2 (48)  4 ( 5)
//  7:  5 (74)  1 ( 6)
//  8:  3 (91)  4 (21)  5 (57)  1 ( 5)
//  9:  1 (14)  4 (22)
// 
// Grafo verificado!
// 
// Implementação UGRAPHmstP0
// custo da MST: 141
// tempo: 0.000009
// vetor de pais:
//  0: 0
//  1: 0
//  2: 4
//  3: 5
//  4: 8
//  5: 1
//  6: 4
//  7: 1
//  8: 1
//  9: 1
// 
// Implementação UGRAPHmstP1
// custo da MST: 141
// tempo: 0.000008
// vetor de pais:
//  0: 0
//  1: 0
//  2: 4
//  3: 5
//  4: 8
//  5: 1
//  6: 4
//  7: 1
//  8: 1
//  9: 1
// 
// Implementação UGRAPHmstP2
// custo da MST: 141
// tempo: 0.000010
// vetor de pais:
//  0: 0
//  1: 0
//  2: 4
//  3: 5
//  4: 8
//  5: 1
//  6: 4
//  7: 1
//  8: 1
//  9: 1
// 
// Implementação UGRAPHmstP3
// custo da MST: 141
// tempo: 0.000008
// vetor de pais:
//  0: 0
//  1: 0
//  2: 4
//  3: 5
//  4: 8
//  5: 1
//  6: 4
//  7: 1
//  8: 1
//  9: 1
// 
// As implementações produziram o mesmo custo total.
// 
// pf:~/mac0328-2019/SANDBOX$

