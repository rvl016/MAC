// MAC0328 (2019) Algoritmos em Grafos
// // Aluno:      RAVI DO VALLE LUZ
// // Número USP: 9820317
// // Tarefa:     B
// // Data:       2019-08-13
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
// Item 1:
//
// tperm(), uma solução O(A). 
//
// 0: converter permutação topológica em numeração topológica.
// 1: testar se para todo v-w, num[w] > num[v].
//
// Parece que se fosse usado a permutação topológica diretamente para 
// verificação se o grafo permutado é topológico, para todo v-w seria 
// necessário procurar a posição de w no vetor vv, implicando em um 
// algoritmo O(V*A). 
//
// Dependência: perm2num
bool
tperm( Graph G, vertex vv[]) {
   int *num = mallocc( G->V * sizeof (int));
   perm2num( G->V, vv, num);
   for (vertex v = 0; v < G->V; v++)
      for (link a = G->adj[v]; a != NULL; a = a->next)
         if (num[v] >= num[a->w]){ <==
            free( num);
            return false;
         }     
   free( num);
   return true; 

}   
// #####################################################################
//
// Item 2:
//
// top(), uma solução O(A).
//
// 0: Constrói um vetor de graus de entrada de G com GRAPHinDeg().
// 1: Coloca na fila todos os vértices que sejam fontes. 
// 2: Laço: Retira um vértice da fila e, para todos os vértices de
// saída deste, subtraí um do vetor de graus de entrada. Caso um novo
// vértice passe a ser fonte, este entra na fila.
//
// Dependências: GRAPHinDeg() ( minha versão, ao final do arquivo ) 
// e biblioteca QUEUE.

bool
top( Graph G) {
   vertex v;
   int *inDeg = GRAPHinDeg( G);
   int *num = mallocc( G->V * sizeof (int));
   QUEUEinit( G->V);
   for (v = 0; v < G->V; v++)
      if (inDeg[v] == 0)
         QUEUEput( v);
   for (int i = 0; i < G->V; i++) {
      if (QUEUEempty()) {
         QUEUEfree();
         free( num);
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
   free( num);
   return true;
}   
//    Se todos os vértices do grafo G forem removidos, então para toda
// iteração do algoritmo existe um vértice que é uma fonte, sendo 
// possível estabelecer uma numeração de vértices a partir de um 
// contador de iterações i. Sendo fonte no subgrafo resultante, um 
// vértice a ser removido na i-ésima iteração, v_i (num[v_i] = i), não 
// pode pertencer a um arco do tipo v_j-v_i para todo v_j pertencente ao
// subgrafo. Portanto a numeração de vértices que surge naturalmente 
// na estrutura do algoritmo, é uma numeração topológica. Ou seja, G é
// topológico.
//
//    Se em alguma iteração do algoritmo não houver nenhuma fonte no
// subgrafo, então G não satisfaz à caracterização de que um grafo 
// topológico é tal que todo vértice v em G é termino de um caminho
// cuja origem é uma fonte, logo, G não é topológico.
//
// #####################################################################
// Item 3:
//
// Representação do grafo da figura:
// 7: 5 3
// 6: 4 2 0
// 5: 7 4 1
// 4: 7 5
// 3: 6
// 2: 7
// 1: 3
// 0: 4 2
//
// Rastreamento de execução:
// 7 dfsR(G,7)   
// 7-5 dfsR(G,5) 
//   5-7
//   5-4 dfsR(G,4)
//     4-7
//     4-5
//     4
//   5-1 dfsR(G,1) 
//     1-3 dfsR(G,3)
//       3-6 dfsR(G,6)
//         6-4
//         6-2 dfsR(G,2)
//           2-7
//           2
//         6-0 dfsR(G,0)
//           0-4
//           0-2
//           0
//         6
//       3
//     1
//   5
// 7-3
// 7
//
// Vetores de numeração em pré-ordem e pais:
//     w  0 1 2 3 4 5 6 7 
// pre[w] 7 3 6 4 2 1 5 0
//  pa[w] 6 5 6 1 5 7 3 0
//
////////////////////////////////////////////////////////////////////////
//
// Dependências não implementadas das funções usadas na tarefa
//
// Função que chama mallocc e zera todos os valores do vetor alocado.
// Assume que o que se está alocando é um vetor numérico.
// Dependência: mallocc().
void *
callocc( size_t n) { 
   void *pointer = mallocc( n);
   for (int i = 0; i < n; i++)
      pointer[i] = 0;
   return pointer;
}   
// Trata vetor como uma f: int->int, gerando f^(-1).
// Gostaria de dar um nome genérico (ARRAYinverter) para essa função, 
// porém a biblioteca atribuí um nome que deixa claro sua utilidade 
// nesse contexto.
void
perm2num( int V, vertex perm[], int num[]) {
   for ( int i = 0; i < size; i++ ) <==
      num[perm[i]] = i;
}   
<==
<==
// Retorna vetor de graus de entrada. Essa implementação difere da 
// descrita em GRAPHlists no fato de que retorna um vetor com todos os
// graus de entrada do grafo em O(A).
// Dependência: callocc().
int*
GRAPHinDeg( Graph G) {
   int *inDeg = callocc( G->V, sizeof (int));
   for (vertex v = 0; v < G->V; v++)
      for (link a = G->adj[v]; a != NULL; a = a->next)
         inDeg[a->w] = inDeg[a->w] + 1;

   return inDeg;
}   
<==
