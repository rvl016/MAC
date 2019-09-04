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
#ifndef _Alib_h
#define _Alib_h

#include <stdlib.h> // strtol(), qsort(), etc.
#include <stdio.h>
#include <string.h> // strtok(), etc.
#include <limits.h> // INT_MAX, etc.
#include <stdbool.h>

// GRAPHlists.h #######################################################/
// {{{

// Estruturas de dados básicas
////////////////////////////////////////////////////////////////////////

// Vértices de grafos são representados por objetos do tipo vertex. Os
// vértices são inteiros não-negativos (0,1,2,...). Em raras ocasiões,
// uma variável do tipo vertex pode ter valor -1 com o significado de
// "não definido".
#define vertex int

// A lista de adjacência de um vértice v é composta por nós do tipo
// node. Cada nó da lista corresponde a um arco e contém um vizinho w de
// v e o endereço do nó seguinte da lista. Cada nó tem um campo cst para
// o custo do arco; o campo é ignorado pelas funções que manipulam
// grafos sem custos. Um link é um ponteiro para um node.
typedef struct node *link;
struct node { 
   vertex w; 
// int cst;
   link next; 
};

// A estrutura graph representa um grafo. O campo adj é um ponteiro para
// o vetor de listas de adjacência, o campo V é o número de vértices e o
// campo A é o número de arcos. Suporemos sempre que V >= 1.
// Um objeto do tipo Graph contém o endereço de um graph.
typedef struct graph *Graph;
struct graph {
   int V; 
   int A; 
   link *adj; 
};

// Ferramentas para construção de grafos
////////////////////////////////////////////////////////////////////////

// Algumas funções têm duas versões, uma para grafos sem custos nos
// arcos e outra para grafos com custos; o nome da segunda versão tem um
// sufixo "_C". Em alguns casos --- como o da árvore geradora de custo
// mínimo -- o sufixo "_C" é omitido porque a função só faz sentido para
// grafos com custos.

// A função GRAPHinit constrói e devolve um grafo com vértices
// 0 1 ... V-1 e nenhum arco.
Graph 
GRAPHinit( int V);

// A função GRAPHinsertArc() insere um arco v-w no grafo G. A função
// supõe que v e w são distintos e menores que G->V. Se o grafo já tem
// um arco v-w, a função não faz nada.
void 
GRAPHinsertArc( Graph G, vertex v, vertex w);

// Mesmo que o anterior, porém para casos em que não há dúvida sobre a
// ocorrência de arcos duplicados
void 
GRAPHinsertArcQuick( Graph G, vertex v, vertex w);
// Para cada vértice v do grafo G, esta função imprime, em uma linha da
// saída padrão, todos os vértices adjacentes a v.
void 
GRAPHshow( Graph G);

// Função privada auxiliar usada por GRAPHdestroy(). Ela libera os nós
// da lista encadeada lst.
void 
freelist( link lst);


// Função privada (= static) auxiliar usada para construir listas de
// adjacência. A função recebe um vértice w e o endereço next de um nó e
// devolve o endereço a de um novo nó tal que a->w == w e
// a->next == next. 
link 
NEWnode( vertex w, link next);
// Esta função desaloca toda a memória usada pela estrutura de dados que
// representa o grafo G.
void 
GRAPHdestroy( Graph G);

// Grafos aleatórios
////////////////////////////////////////////////////////////////////////

vertex 
randV( Graph G);  
// Constrói grafo aleatório com vértices 0..V-1 e exatamente A arcos. A
// função supõe que A <= V*(V-1). Se A for próximo de V*(V-1), a função
// pode consumir muuuito tempo. Por isso, a função é mais usada para 
// gerar grafos esparsos.
Graph 
GRAPHrand1( int V, int A);


// Constrói um grafo aleatório com vértices 0..V-1. Cada um dos V*(V-1)
// possíveis arcos é construído com probabilidade p, sendo p calculado
// de modo que o número esperado de arcos seja A. A função supõe que 
// V >= 2 e A <= V*(V-1). A função é mais usada para gerar grafos
// densos.
Graph 
GRAPHrand2( int V, int A);

// }}}
// MYTOOLS.h ##########################################################/
// {{{
// Minha versão de malloc interrompe execução da função se malloc
// devolve NULL.
void *
mallocc( size_t n);

// }}}

//
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
GRAPHcount( Graph G, int V);

// GRAPHprintDgTbl - Recebe os dados de GRAPHcount para imprimir a 
// tabela.
//
void
GRAPHprintDgTbl ( vertex* inDgTbl, vertex* outDgTbl, int maxInDg,
   int maxOutDg);

#endif
