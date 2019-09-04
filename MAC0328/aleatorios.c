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
// {{{ Include...
// #include "GRAPHlists.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Routine.h"
// }}}

// {{{ Define...
// MAX_V - Controle do tamanho de alocação de vetores para preparar a 
// impressão das tabelas. 
//#define MAX_V 10000
// RAND_1 - Decidir se usa GRAPHrand_1
// #define RAND_1 false 
// }}}

// {{{ functions
//    {{{ execute 
// execute - Chama as funções para cada tipo de RAND
// *Considero uma parte de main
void
execute( int V, int A, bool mode){
   

   printf("\n\n---Iniciando GRAPHrand%d:", ( (int) mode + 1 ));
   clock = clock();

   if ( mode ) 
      G = GRAPHrand2( V, A);   
   else 
      G = GRAPHrand1( V, A);
   
   clock = clock() - clock;
   time = ( (double) clock) / CLOCKS_PER_SEC;
   
   GRAPHcount( G, V);

   if ( V < 30 ) 
      GRAPHshow( G);
   
   printf("\n---Tempo de execução de GRAPHrand%d: %f",\
( (int) mode + 1 ), (float) time); 

   GRAPHdestroy( G);

}   
//    }}}
// }}}

// {{{ Main

int 
main( int argc, char **argv){

   int V = atoi(argv[1]), A = atoi(argv[2]);
   Graph G;
   clock_t clock;
   double time;
   
   if ( V > MAX_V ) {
      printf ("Número de vértices superior ao limite de alocação \
(%d)!\n Favor modificar a definição de MAX_V na linha 29 de \
aleatorios.c.", MAX_V);
      return EXIT_FAILURE;
   }   
   
   execute( V, A, false );
   execute( V, A, true );

   return EXIT_SUCCESS;
}    

// }}}
