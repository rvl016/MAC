// MAC0328 (2019) Algoritmos em Grafos
// // Aluno:      RAVI DO VALLE LUZ
// // Número USP: 9820317
// // Tarefa:     A
// // Data:       2019-08-04
// //
// // DECLARO QUE SOU O ÚNICO AUTOR E RESPONSÁVEL POR ESTE
// // PROGRAMA. TODAS
// // AS PARTES DO PROGRAMA, EXCETO AS QUE FORAM FORNECIDAS PELO
// // PROFESSOR
// // OU COPIADAS DO LIVRO OU DAS BIBLIOTECAS DE SEDGEWICK OU ROBERTS,
// // FORAM DESENVOLVIDAS POR MIM. DECLARO TAMBÉM QUE SOU
// // RESPONSÁVEL POR
// // TODAS AS EVENTUAIS CÓPIAS DESTE PROGRAMA E QUE NÃO DISTRIBUI NEM
// // FACILITEI A DISTRIBUIÇÃO DE CÓPIAS. 
// //
// /////////////////////////////////////////////////////////////////////
#include "Alib.h"
// GRAPHlists.c #######################################################/
// {{{
// #define DEBUG false
#define DEBUG true

// Estruturas de dados básicas
////////////////////////////////////////////////////////////////////////

// A interface GRAPHlists.h define a estrutura graph e o tipo-de-dados
// Graph. Também contém inclui as interfaces QUEUE.h, PQ.h, UF.h e
// MYTOOLS.h. Também contém as interfaces padrão stdlib.h, stdio.h,
// string.h, limits.h e stdbool.h.

// Ferramentas para construção (e destruição) de grafos
////////////////////////////////////////////////////////////////////////

Graph 
GRAPHinit( int V) { 
   Graph G = mallocc( sizeof (Graph));
   G->V = V; 
   G->A = 0;
   G->adj = mallocc( V * sizeof (link));
   for (vertex v = 0; v < V; ++v) 
      G->adj[v] = NULL;
   return G;
}

void 
GRAPHdestroy( Graph G) {
   for (vertex v = 0; v < G->V; ++v)
      freelist( G->adj[v]);
   free( G->adj);
   free( G);   
}
// Função privada auxiliar usada por GRAPHdestroy(). Ela libera os nós
// da lista encadeada lst.
void 
freelist( link lst) {
   if (lst != NULL) {
      freelist( lst->next);
      free( lst);
   }
}

// Função privada (= static) auxiliar usada para construir listas de
// adjacência. A função recebe um vértice w e o endereço next de um nó e
// devolve o endereço a de um novo nó tal que a->w == w e
// a->next == next. 
link 
NEWnode( vertex w, link next) { 
   link a = mallocc( sizeof (struct node));
   a->w = w; 
   a->next = next;     
   return a;                         
}
// Esta função privada auxiliar devolve um vértice aleatório do grafo G.
// (Vamos supor que G->V <= RAND_MAX.) Ela é apenas um invólucro para a
// função rand() da biblioteca stdlib, que produz um número inteiro
// aleatório no intervalo fechado 0..RAND_MAX. 
vertex 
randV( Graph G) { 
   double r = rand() / (RAND_MAX + 1.0); // 0 <= r < 1
   return r * G->V;
}

Graph 
GRAPHrand1( int V, int A) { 
   Graph G = GRAPHinit( V);
   if (A > V*(V-1)) A = V*(V-1);
   while (G->A < A) {
      vertex v = randV( G);
      vertex w = randV( G);
      if (v != w){ 
         GRAPHinsertArc( G, v, w);
      }   
   }
   return G;
}

Graph 
GRAPHrand2( int V, int A) { 
   if (A > V*(V-1)) A = V*(V-1);
   double prob = (double) A / V / (V-1);
   Graph G = GRAPHinit( V);
   for (vertex v = 0; v < V; ++v)
      for (vertex w = 0; w < V; ++w) 
         if (v != w)
            if (rand( ) < prob*(RAND_MAX+1.0))
               GRAPHinsertArcQuick( G, v, w);
   return G;
}

// Implementações próprias ###########################################//
// Novo - Implementação seguindo a definição do header GRAPHlist.
// A função GRAPHinsertArc() insere um arco v-w no grafo G. A função
// supõe que v e w são distintos e menores que G->V. Se o grafo já tem
// um arco v-w, a função não faz nada.
void
GRAPHinsertArc( Graph G, vertex v, vertex w){
   
   link new;
   for ( link p = G->adj[v]; p != NULL; p = p->next){
       if ( p->w == w ){
           return;
       }
   }    
    
   new = NEWnode( w, G->adj[v]);
   G->adj[v] = new;
   G->A = G->A + 1;
   return;

}
// Mesmo que o anterior, porém para casos em que não há dúvida sobre a
// ocorrência de arcos duplicados
void
GRAPHinsertArcQuick( Graph G, vertex v, vertex w){
   
   link new;
   new = NEWnode( w, G->adj[v]);
   G->adj[v] = new;
   G->A = G->A + 1;
   return;

}
// Novo - Implementação seguindo a definição do header GRAPHshow.

void 
GRAPHshow( Graph G ){
   printf( "_______________________________________________________\n");
   printf( "Lista de adjacências:\n");
   for ( vertex v = 0; v < G->V; v++){
      printf( "%d -> ", v);
      for ( link w = G->adj[v]; w != NULL; w = w->next)
         printf( "%d ", w->w); 
      printf( "\n");  
   }
   return;
}   
//
// }}}
// MYTOOLS.c ##########################################################/
// {{{
// contém a interface padrão stdlib.h

// Minha versão de malloc.
void *
mallocc( size_t n) {
   void *pointer = malloc( n);
   if (pointer == NULL) {
      fprintf( stderr, "\nmalloc devolveu NULL!\n"); 
      exit( EXIT_FAILURE);
   }
   return pointer;
}

// }}}
//
// {{{ GRAPHcount
// GRAPHcount - Função para obter as adjacências do Grafo gerado:
// Para cada v de G, conta-se o número de arcos (A), o número de
// vértices que partem de v (outDg[v]) e aproveita-se para já contar os
// vértices que chegam em v (inDg[v]). Além disso, monitora-se a qual é
// o máximo grau de saída e entrada em G ao longo das iterações.
// Como para cada iteração do do loop externo já se sabe o grau de saída
// de v, faz-se uma contagem em um vetor usado para imprimir a tabela
// de número de vértices por grau de saída (outDgTbl).
// Finalizado o loop externo, faz-se o mesmo para inDgTbl.
//
// ** Fiz abreviações que podem atrapalhar a leitura, mas que evitam 
// nomes muito extensos para as variáveis. Não sei o que seria melhor
// aqui.
// Dg = Degree
// Tbl = Table
// 
void
GRAPHcount( Graph G, int V){

   int *inDg, *outDg;
   vertex *inDgTbl, *outDgTbl;
   int maxInDg = 0, maxOutDg = 0;
   int A = 0;

   inDg = ( int* )calloc( V, sizeof( int ) );
   outDg = ( int* )calloc( V, sizeof( int ) );
   inDgTbl = ( vertex* )calloc( V - 1, sizeof( vertex ) );
   outDgTbl = ( vertex* )calloc( V - 1, sizeof( vertex ) );

   for ( vertex v = 0; v < V; v++ ){
      for ( link p = G->adj[v]; p != NULL; p = p->next){
         A = A + 1;
         outDg[v] = outDg[v] + 1;
         inDg[p->w] = inDg[p->w] + 1;  

         if ( maxInDg < inDg[p->w] ) 
            maxInDg = inDg[p->w];

      }   
      if ( maxOutDg < outDg[v] ) 
         maxOutDg = outDg[v];

      outDgTbl[outDg[v]] = outDgTbl[outDg[v]] + 1;      
   }

   G->A = A;

   for ( vertex v = 0; v < V ; v++ ){
      inDgTbl[inDg[v]] = inDgTbl[inDg[v]] + 1;
   }
   printf( "Grafo com %d vétices e %d arcos.\n", V, A);

   GRAPHprintDgTbl( inDgTbl, outDgTbl, maxInDg, maxOutDg );

   return;
}
// }}}
// {{{ GRAPHprintDgTbl  
// Recebe os dados de GRAPHcount para imprimir a tabela.
//
void
GRAPHprintDgTbl ( vertex* inDgTbl, vertex* outDgTbl, int maxInDg,
   int maxOutDg){

   printf( "_______________________________________________________\n");
   printf( "Tabela de graus de saída (grau - número de vértices):\n");
   for ( int i = 0; i <= maxOutDg; i++ ){
      printf( "%d | %d \n", i, outDgTbl[i]);
   }   
   printf( "_______________________________________________________\n");
   printf( "Tabela de graus de entrada (grau - número de vértices):\n");
   for ( int i = 0; i <= maxInDg; i++ ){
      printf( "%d | %d \n", i, inDgTbl[i]);
   }   
   return;
}     
// }}}
