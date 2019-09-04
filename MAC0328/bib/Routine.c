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
//
#include "Routine.h"
#include "Alib.h"
//
// GRAPHcount - Função para obter as adjacências do Grafo gerado:
// {{{ GRAPHcount
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

   int* inDg, outDg;
   vertex* inDgTbl, outDgTbl;
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
