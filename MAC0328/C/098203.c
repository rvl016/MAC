// MAC0328 (2019) Algoritmos em Grafos
// // Aluno:      RAVI DO VALLE LUZ
// // Número USP: 9820317
// // Aluno:      GABRIEL MORETE DE AZEVEDO
// // Número USP: 10350500
// // Tarefa:     C
// // Data:       2019-08-24
// //
// // DECLARAMOS QUE NÓS, OS ALUNOS LISTADOS ACIMA, SOMOS OS ÚNICOS 
// // AUTORES E RESPONSÁVEIS POR ESTE PROGRAMA. TODAS
// // AS PARTES DO PROGRAMA, EXCETO AS QUE FORAM FORNECIDAS PELO
// // PROFESSOR
// // OU COPIADAS DO LIVRO OU DAS BIBLIOTECAS DE SEDGEWICK OU ROBERTS,
// // FORAM DESENVOLVIDAS POR NÓS. DECLARAMOS TAMBÉM QUE SOMOS
// // RESPONSÁVEIS POR
// // TODAS AS EVENTUAIS CÓPIAS DESTE PROGRAMA E QUE NÃO DISTRIBUIMOS
// // NEM FACILITAMOS A DISTRIBUIÇÃO DE CÓPIAS. 
// //
// /////////////////////////////////////////////////////////////////////
// PROBLEMA 1: numeração pré ou pós ordem não são necessariamente n
// numerações topo/antitopológicas em um DAG!!! MENTIRA: pós-ordem, é.
// PROBLEMA 2: em Cout3 imprimir uma permutação é fácil, mas um ciclo é
// difícil; inverter o sentido dos arcos e aplicar novamente o top
// parece o mais eficiente e resultaria num subgrafo apenas com ciclos,
// mas tem que refazer o grafo e aplicar de novo o algoritmo
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "GRAPHlists.h"
#include "QUEUE.h"

////////////////////////////////////////////////////////////////////////
//////////////////////// Funções auxiliares ////////////////////////////
void
PERMprint( int V, vertex *perm) {
// {{{        
   printf( "O grafo é topológico! Segue uma permutação topológica:\n");
   for( int i = 0; i < V; ++i)
      printf( "%d ", perm[i]);
   printf( "\n");
   return;
// }}}        
}   
// Retorna ao usuário uma sequência de vértices que correspondem a um
// circuito no grafo. É necessário um vetor de pais retornado por um
// DFS e um par de vértices, v e w, tal que v-w seja arco de retorno.
void
CYCLEshowDfs( int V, vertex *pa, vertex pair[2]) {
// {{{        
   vertex *cycle = malloc( V * sizeof (vertex));  
   vertex v = pair[0], w = pair[1];
   int i = 0;
   while (v != w) {
      cycle[i] = v;
      v = pa[v];
      i = i + 1;
   }   
   cycle[i] = v;
   printf( "O grafo não é DAG! Segue um ciclo encontrado:\n");
   while (i >= 0) {
      printf( "%d-", cycle[i]);
      i = i - 1;
   }   
   printf( "%d\n", w);
   free( cycle);
   return;
// }}}        
}   
// Utilizando o vetor inDeg, acha e mostra, ao usuário, um ciclo em 
// G. O ciclo encontrado depende de como a lista de adjacências de G é
// arranjada. Espera que o vetor inDeg seja pré-processado por CouT3(), 
// de modo que que todas as fontes retiradas ao longo das iterações 
// tenham grau de entrada zero.
// Dependências: mallocc(), GRAPHinit(), GRAPHinsertArcQuick(),
// GRAPHdestroy().
void
findShowCycleTop( Graph G, int *inDeg) {
// {{{        
   vertex *son = mallocc( G->V * sizeof (vertex));
   vertex v, w;
   link a;
   Graph Ginv = GRAPHinit( G->V);
   for (v = 0; v < G->V; ++v) 
      if (inDeg[v] > 0)
         for (a = G->adj[v]; a != NULL; a = a->next)
            GRAPHinsertArcQuick( Ginv, a->w, v);
   for (v = 0; v < G->V; ++v) 
      son[v] = G->V; 
   for (v = 0; v < G->V; ++v) 
      if (Ginv->adj[v] != NULL) {
         v = a->w;   
         break;
      }   
   while (son[v] == G->V) {
      a = Ginv->adj[v];
      while (Ginv->adj[a->w] == NULL) 
         a = a->next;
      son[v] = a->w;
      v = a->w;
   }   
   printf( "O grafo não é DAG! Segue um ciclo encontrado:\n");
   for (v = 0; v >= 0; --v) 
      printf( "%d-", son[v]);
   printf( "%d\n", w);
   free( son);
   GRAPHdestroy( Ginv);
   return;
// }}}        
}   
// Reverte a ordem de um vetor de inteiros.
void
ARRAYreverse( int n, int *array) {
// {{{        
   int tmp;
   for (int i = 0; i <= n / 2; ++i) {
      tmp = array[n - i];
      array[n - i] = array[i];
      array[i] = tmp;
   }   
   return;
// }}}        
}   
// Função que chama mallocc e zera todos os valores do vetor alocado.
// Assume que o que se está alocando é um vetor numérico.
// Dependência: mallocc().
void *
callocc( size_t n) { 
// {{{        
   void *ptr = mallocc( n);
   for (int i = 0; i < n; i++)
      ptr[i] = 0;
   return ptr;
// }}}        
}   
// Retorna vetor de graus de entrada. Essa implementação difere da 
// descrita em GRAPHlists no fato de que retorna um vetor com todos os
// graus de entrada do grafo em O(A).
// Dependência: callocc().
int*
GRAPHinDeg( Graph G) {
// {{{        
   int *inDeg = callocc( G->V, sizeof (int));
   for (vertex v = 0; v < G->V; v++)
      for (link a = G->adj[v]; a != NULL; a = a->next)
         inDeg[a->w] = inDeg[a->w] + 1;

   return inDeg;
// }}}        
}   
// Esta função privada auxiliar é usada por CouT2(). Ela
// devolve true se encontra um ciclo ao percorrer G a partir do vértice
// v e devolve false em caso contrário. O código é inspirado no de
// GRAPHdfsR().
static bool
dfsRcycle( Graph G, vertex v, int *pre, int *post, vertex *pa,
         vertex *pair, int cnt, int cntt) { 
// {{{        
   pre[v] = cnt++;
   // percorra a lista de adjacência de v.
   for (link a = G->adj[v]; a != NULL; a = a->next) {
      vertex w = a->w;
      if (pre[w] == -1) {
         // Se w não foi visitado, visite e retorne o que os próximos
         // níveis de recusão voltarem apenas se for true.
         pa[w] = v; 
         if (dfsRcycle( G, w, pre, post, pa, pair, cnt, cntt)) 
            return true;
       //res = dfsRcycle( G, w, pre, post, pa);
       //if (res != G->V) return ;
      } else {
         // (*) Se w foi visitado e post[w] == -1, ou seja, post[w] > 
         // post[v], então v-w é arco de retorno. Temos um ciclo!
         if (post[w] == -1) {
            pair[0] = v, pair[1] = w;
            return true;
         }   
      }
   }
   post[v] = cntt++;
   // Se essa recursão chegou até aqui, então não houve ciclos a partir
   // desse branch da árvore.
   return false;
// }}}        
}
////////////////////////////////////////////////////////////////////////
//////////////////////// Funções principais ////////////////////////////
////////////////////////////////////////////////////////////////////////
// Faz uma busca DFS completa e depois procura um arco de retorno.
// Dependências: GRAPHdfs(), mallocc(), CYCLEshowDfs(), injnum2perm(),
// ARRAYreverse(), PERMprint().
bool 
CouT1( Graph G) {
// {{{        
   int *pre = mallocc( G->V * sizeof (int));
   int *post = mallocc( G->V * sizeof (int));
   int *pa = mallocc( G->V * sizeof (vertex));
   vertex *perm = mallocc( G->V * sizeof (vertex));
   vertex pair[2];
   GRAPHdfs( G, pre, post, pa);
   for (vertex v = 0; v < G->V; ++v) {
      for (link a = G->adj[v]; a != NULL; a = a->next) {
         vertex w = a->w;
         if (post[v] < post[w]) { // v-w é de retorno
            pair[0] = v, pair[1] = w;
            CYCLEshowDfs( G->V, pa, pair);
            free( perm), free( pa), free( post), free( pre);
            return false;
         }
      }
   } 
   // post[v] > post[w] para todo arco v-w
   // GERAR PERMUTAÇÂO TOPOLÓGICA
   injnum2perm( G->V, post, perm);
   ARRAYreverse( G->V, perm);
   PERMprint( G-> V, perm);
   free( perm), free( pa), free( post), free( pre);
   return false;
// }}}        
}
// O que precisamos:
// (1) Completar a marcação do vetor de pais.
// (2) Dar um jeito de marcar o arco de retorno:
//    (a) Uma forma seria retornar o vertex w caso um ciclo ou G->V,
//    caso contrário. Vai ter que procurar v depois?! Isso ainda
//    não implica em perda de eficiência "grossa"...no máximo mais A.
//    (b) Outra forma seria retornar o circuito dentro da função...
//    FEIO.
//    (c) Retornar v e usar o vetor de pais junto com o vetor de pós-
//    ordem e pré-ordem...solução limpa e que (a), porém custa mais
//    O(V^2).
//    (d) criar uma nova entrada
//    

// Interrompe a busca DFS logo que encontra um arco de retorno.
// Essa função evita um dfs completo caso encontre um circuito no meio
// do caminho.
// Dependências: dfsRcycle(), CYCLEshowDfs(), injnum2perm(), 
// ARRAYreverse(), PERMprint().
bool 
CouT2( Graph G) { 
// {{{        
   int *pre = mallocc( G->V * sizeof (int));
   int *post = mallocc( G->V * sizeof (int));
   int cnt, cntt;
   vertex *pa = mallocc( G->V * sizeof (vertex));
   vertex *perm = mallocc( G->V * sizeof (vertex));
   vertex pair[2];
   cnt = cntt = 0;
   for (vertex v = 0; v < G->V; ++v)
      pre[v] = post[v] = -1;
   bool c = false;
   // Aqui o dfs parte efetivamente a partir de cada árvore da floresta
   // . MENTIRA: se houver um arco do "componente" i para j com i > j
   // na ordem de visita, porém, não há o oposto, i e j são, na verdade
   // , o mesmo componente!!!
   for (vertex v = 0; v < G->V; ++v)
      if (pre[v] == -1) {
         pa[v] = v;
         c = dfsRcycle( G, v, pre, post, pa, pair, cnt, cntt);
         if (c) break; // temos um ciclo
         // (não necessariamente passando por v)
      }
   if (c) CYCLEshowDfs( G->V, pa, pair);
   else {
      injnum2perm( G->V, post, perm);
      ARRAYreverse( G->V, perm);
      PERMprint( G->V, perm);
   }   
   free( perm), free( pa), free( post), free( pre);
   return c; 
// }}}        
}
// top(), uma solução O(A).
// NÃO DECREVER O COMO!!!!!
// 0: Constrói um vetor de graus de entrada de G com GRAPHinDeg().
// 1: Coloca na fila todos os vértices que sejam fontes. 
// 2: Laço: Retira um vértice da fila e, para todos os vértices de
// saída deste, subtraí um do vetor de graus de entrada. Caso um novo
// vértice passe a ser fonte, este entra na fila.
// Dependências: GRAPHinDeg(), findShowCycleTop(), injnum2perm(),
// PERMprint() e biblioteca QUEUE.
char *
CouT3( Graph G) {
// {{{        
   vertex v;
   int *inDeg = GRAPHinDeg( G);
   int *num = mallocc( G->V * sizeof (int));
   QUEUEinit( G->V);
   vertex *perm = mallocc( G->V * sizeof (vertex));
   for (v = 0; v < G->V; v++)
      if (inDeg[v] == 0)
         QUEUEput( v);
   for (int i = 0; i < G->V; i++) {
      if (QUEUEempty() == 1) {
         QUEUEfree();
         free( num);
         findShowCycleTop( G, inDeg);
         return false;
      }   
      v = QUEUEget();
      for (link a = G->adj[v]; a != NULL; a = a->next) {
         inDeg[a->w] = inDeg[a->w] - 1; 
         if (inDeg[a->w] == 0)
            QUEUEput( a->w);
      }
//   O vetor num constituí uma numeração topológica caso o laço termine.
      num[v] = i;
   }
   QUEUEfree();
   injnum2perm( G->V, num, perm);
   PERMprint( G->V, perm);
   free( num);
   return true;
// }}}        
}   
////////////////////////////////////////////////////////////////////////
//////////////////////////////// main //////////////////////////////////
int 
main( int argc, char **argv) {
   int V = atoi( argv[1]), A = atoi( argv[2]), s = atoi( argv[3]);
   int (*CouT[3]) ( Graph G) = { (*CouT1), (*CouT2), (*CouT3)};
   bool res[3];
   clock_t clk;
   double time[3];
   srand( s);
   Graph G = GRAPHrand1( V, A);
   for (int i = 0; i < 3; ++i) {
      printf( "Iniciando CouT%d!\n", i - 1);
      clk = clock();
      res[i] = (CouT[i]) ( G);
      clk = clock() - clk;
      time = ((double) clk) / CLOCKS_PER_SEC;
      if ( i > 0 && res[i] != res[i - 1] ) {
         printf( "Resultados das CouT diferem! Abortando!");
         GRAPHdestroy( G);
         return EXIT_FAILURE;
      }      
      printf( "CouT%d levou %lf segundos!", i - 1, time);
   }   
   GRAPHdestroy( G);
   return EXIT_SUCCESS;
}    
