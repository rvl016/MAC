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
// // Este programa gera dois grafos aleatórios de V vértices ( primeiro
// // argumento do programa) em sequência. O primeiro parte de um 
// // sorteio de arcos que ainda não existam nem sejam laços, até com 
// // que o grafo tenha o número de arcos requisitados pelo segundo 
// // argumento do programa. O segundo sorteia a existência ou não de um
// // arco com probabilidade A/(V(V-1)) para todas as combinações
// // possíveis, excluindo laços.
//
// {{{ Include...
// #include "GRAPHlists.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Alib.h"
// }}}

// {{{ functions
//    {{{ execute 
// execute - Chama as funções para cada tipo de RAND
// *Considero uma parte de main
void
execute( int V, int A, bool mode){
   
   clock_t clk;
   double time;
   Graph G;

   printf("\n\n---Iniciando GRAPHrand%d:---\n", ( (int) mode + 1 ));
   clk = clock();

   if ( mode ) 
      G = GRAPHrand2( V, A);   
   else 
      G = GRAPHrand1( V, A);
   
   clk = clock() - clk;
   time = ( (double) clk) / CLOCKS_PER_SEC;
   
   GRAPHcount( G, V);
   if ( V < 30 ) 
      GRAPHshow( G);
   
   printf("\n-Tempo de execução de GRAPHrand%d: %f segundos-\n",
      ( (int) mode + 1 ), (float) time); 

   GRAPHdestroy( G);

}   
//    }}}
// }}}

// {{{ Main

int 
main( int argc, char **argv){
   
   if ( argc < 3 ){
      printf ("Número de parâmetros insuficiente!\n");
      return (EXIT_FAILURE);
   }
      
   int V = atoi(argv[1]), A = atoi(argv[2]);

   execute( V, A, false );
   execute( V, A, true );

   return (EXIT_SUCCESS);
}    

// }}}
