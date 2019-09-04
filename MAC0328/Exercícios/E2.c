// Trata array como uma f: int->int, gerando f^(-1)
int*
ARRAYinverter( int* f, int size);

// Recebe um G e uma permutação de vértices e verifica se é topológico.
// Assume que vv tem comprimento igual ao número de vértices de G!
//
bool
GRAPHlabelPemutationIsTopo( Graph G, vertex* vv );

// Constrói grafo não direcionado em grade mxn, numeração dos vértices
// corre ao longo das colunas.
UGraph
UGRAPHbuildGrid( int m, int n);


int*
ARRAYinverter( int* f, int size){

   int *fInv = ( int* ) malloc( size * sizeof( int));
   for ( int i = 0; i < size; i++ )
      fInv[f[i]] = i;
   return fInv;
}   

// Solução O(A). 
// Parece que se fosse usado a permutação topológica diretamente para 
// verificação se o grafo permutado é topológico, para todo v-w seria 
// necessário procurar a posição de w no vetor vv, implicando em um 
// algoritmo O(V*A). 
// 
// 0: converter permutação topológica em numeração topológica com
// ARRAYinverter.
// 1: testar se para todo v-w, topo[w] > topo[v].
// Dependências: ARRAYinverter
bool
GRAPHlabelPemutationIsTopo( Graph G, vertex* vv ){

   int *topo;
   // 0:
   topo = ARRAYinverter( vv, G->V );
   // 1:
   for ( vertex v = 0; v < G->V; v++ )
      for ( link a = G->adj[v]; a != NULL; a = a->next )
         if ( topo[v] >= topo[a->w] ){
            free( topo);
            return false;
         }     

   free( topo);
   return true; 

}   

// Solução O(m*n)
// Dependências: UGraph (structure), UGraphinit, UGRAPHinsertEdge
UGraph
UGRAPHbuildGrid( int m, int n){

   vertex v = 0, w = 0;
   UGraph G;
   
   G = UGRAPHinit( m * n);
   for ( vertex vline = 0; vline < m; vline++ )      
      for ( vertex vcolo = 0; vcolo < m; vcolo++ ){
         if ( vcolo > 0 ){
            UGRAPHinsertEdge( G, v - 1, v );
         } 
         if ( vline > 0 ){
            UGRAPHinsertEdge( G, v - n, v );
         }   
         v = v + 1;
      }
   return G;
}   
