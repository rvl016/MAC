// MAC0328 (2019) Algoritmos em Grafos
// // Aluno:      RAVI DO VALLE LUZ
// // Número USP: 9820317
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
#ifndef _GRAPHtools_h
#define _GRAPHtools_h

#include <stdlib.h> // strtol(), qsort(), etc.
#include <stdio.h>
#include <string.h> // strtok(), etc.
#include <limits.h> // INT_MAX, etc.
#include <stdbool.h>

// CONSTRUÇÃO E DESTRUIÇÃO DE GRAFOS -----------------------------------
// A função GRAPHinit constrói e devolve um grafo com vértices
// 0 1 ... V-1 e nenhum arco.
Graph 
GRAPHinit( int V );

// A função GRAPHinsertArc() insere um arco v-w no grafo G. A função
// supõe que v e w são distintos e menores que G->V. Se o grafo já tem
// um arco v-w, a função não faz nada.
void 
GRAPHinsertArc( Graph G, vertex v, vertex w );

// Mesmo que o anterior, porém para casos em que não há dúvida sobre a
// ocorrência de arcos duplicados
void 
GRAPHinsertArcQuick( Graph G, vertex v, vertex w );
// Para cada vértice v do grafo G, esta função imprime, em uma linha da
// saída padrão, todos os vértices adjacentes a v.

// Esta função desaloca toda a memória usada pela estrutura de dados que
// representa o grafo G.
void 
GRAPHdestroy( Graph G );
// A função GRAPHremoveArc() remove o arco v-w do grafo G. A função
// supõe que v e w são distintos e menores que G->V. Se não existe arco
// v-w, a função não faz nada.
void 
GRAPHremoveArc( Graph G, vertex v, vertex w );

// Esta função desaloca toda a memória usada pela estrutura de dados que
// representa o grafo G.
void 
GRAPHdestroy( Graph G );

// --- AUXILIARES ---
// Função privada (= static) auxiliar usada para construir listas de
// adjacência. A função recebe um vértice w e o endereço next de um nó e
// devolve o endereço a de um novo nó tal que a->w == w e
// a->next == next. 
static
link 
NEWnode( vertex w, link next );

// ------------------
// ---------------------------------------------------------------------
////////////////////////////////////////////////////////////////////////
// Variados ------------------------------------------------------------

void 
GRAPHshow( Graph G );
// Copia um grafo qualquer, em estrutura de listas de adjacências
Graph
GRAPHcopy( Graph G );

// ---------------------------------------------------------------------
// Busca em profundidade (= depth-first search = DFS)
////////////////////////////////////////////////////////////////////////

// A função GRAPHdfs() faz uma busca em profundidade no grafo G, numera
// os vértices em pré-ordem e pós-ordem e constrói a floresta DFS da
// busca. Os resultados são armazenados nos vetores pre[], post[] e pa[]
// respectivamente, todos indexados pelos vértices (e alocados pelo
// cliente da biblioteca). A numeração em pré- e pós-ordem e o vetor de
// pais são definidos assim:
//   - se x é o k-ésimo vértice descoberto então pre[x] = k,
//   - se x é o k-ésimo vértice a morrer então post[x] = k,
//   - se v é o pai de um vértice w na floresta então pa[w] = v
//   - se w é uma raiz da floresta então pa[w] = w.
void 
GRAPHdfs( Graph G, int *pre, int *post, vertex *pa);
