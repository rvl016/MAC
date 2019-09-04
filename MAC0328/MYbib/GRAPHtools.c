
// CONSTRUÇÃO E DESTRUIÇÃO DE GRAFOS -----------------------------------
// A função GRAPHinit constrói e devolve um grafo com vértices
// 0 1 ... V-1 e nenhum arco.
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
static link 
NEWnode( vertex w, link next) { 
   link a = mallocc( sizeof (struct node));
   a->w = w; 
   a->next = next;     
   return a;                         
}
// Copia um grafo qualquer, em estrutura de listas de adjacências
Graph
GRAPHcopy( Graph G ){
   
   Graph Gcopy = GRAPHinit( G, G->V );
   for ( vertex v = 0; v < G->V; v++)
      for ( link a = G->adj[v]; a != NULL; a = a->next )
         GRAPHinsertArcQuick( Gcopy, v, a->w );
      
   return Gcopy;

}   
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
////////////////////////////////////////////////////////////////////////

// Variáveis globais privadas usadas como contadores no cálculo de pre[]
// e post[] respectivamente.
static int cnt, cntt;

// A função privada auxiliar dfsR() é o motor de GRAPHdfs(). Ela recebe
// um grafo G, um vértice v, e vetores pre[], post[] e pa[]. A função
// tem acesso às variáveis globais cnt e cntt. O vetor pre[] tem valores
// no conjunto -1 0 1 ... cnt-1 e o vetor post[] tem valores no conjunto
// -1 0 1 ... cntt-1. Considere o conjunto X dos vértices que são
// acessíveis a partir de v por caminhos que só usam vértices x tais
// que pre[x] vale -1. Nesse contexto, a função dfsR() atribui um
// número pre[x] a cada x em X: se x é o k-ésimo vértice descoberto
// então pre[x] recebe o valor cnt + k.
static void 
dfsR( Graph G, vertex v, int *pre, int *post, vertex *pa) { 
   pre[v] = cnt++; 
   for (link a = G->adj[v]; a != NULL; a = a->next)
      if (pre[a->w] == -1) {
         pa[a->w] = v; 
         dfsR( G, a->w, pre, post, pa); 
      } 
   post[v] = cntt++;
}

// Código inspirado no programa 18.3 de Sedgewick.
void 
GRAPHdfs( Graph G, int *pre, int *post, vertex *pa) { 
   cnt = cntt = 0;
   for (vertex v = 0; v < G->V; ++v) 
      pre[v] = post[v] = -1; // A
   for (vertex v = 0; v < G->V; ++v)
      if (pre[v] == -1) {
         pa[v] = v;
         dfsR( G, v, pre, post, pa); // nova etapa
      }
}
// A: Inicializei post[] apenas porque a classificação on-the-fly dos
// arcos precisa disso.


