
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
GRAPHcopy( Graph G ) {
   
   Graph Gcopy = GRAPHinit( G, G->V );
   for (vertex v = 0; v < G->V; v++)
      for (link a = G->adj[v]; a != NULL; a = a->next)
         GRAPHinsertArcQuick( Gcopy, v, a->w);
   return Gcopy;
}   
// Novo - Implementação seguindo a definição do header GRAPHlist.
// A função GRAPHinsertArc() insere um arco v-w no grafo G. A função
// supõe que v e w são distintos e menores que G->V. Se o grafo já tem
// um arco v-w, a função não faz nada.
void
GRAPHinsertArc( Graph G, vertex v, vertex w) {
   
   link new;
   for (link p = G->adj[v]; p != NULL; p = p->next) {
       if (p->w == w){
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
GRAPHinsertArcQuick( Graph G, vertex v, vertex w) {
   
   link new;
   new = NEWnode( w, G->adj[v]);
   G->adj[v] = new;
   G->A = G->A + 1;
   return;
}
// Novo - Implementação seguindo a definição do header GRAPHshow.

void 
GRAPHshow( Graph G) {
   printf( "_______________________________________________________\n");
   printf( "Lista de adjacências:\n");
   for (vertex v = 0; v < G->V; v++) {
      printf( "%d -> ", v);
      for (link w = G->adj[v]; w != NULL; w = w->next)
         printf( "%d ", w->w); 
      printf( "\n");  
   }
   return;
}   

// 19/08/2019
//
// DFS iterativo
//
// Esta função é uma versão iterativa (não-recursiva) de GRAPHdfs().
// O que possibilita manter a complexidade O(A) é o fato do vetor de
// ponteiros tipo link, ptr[], guardar a posição do próximo 
// Isso tá bem mais foda que o imaginado.....
void 
GRAPHdfsIterative( Graph G, int *pre, int *post, vertex *pa){
   
   link *ptr = malloc( G->V * sizeof (link));
   vertex v, w, tmp;
   link a;
   int cnt = 0, cntt = 0;
   for (v = 0; v < G->V; v++) {
      pre[v] = post[v] = -1; 
      ptr[v] = G->adj[v];
   }   
   for (v = 0; v < G->V; v++) {
      if (pre[v] == -1) {
         pre[v] = cnt++;
         pa[v] = v;
         a = ptr[v]
         w = v;   
         while (a != NULL) {
            // Aqui a salsicha irá penetrar no grafo.
            while (pre[a->w] != -1 && a != NULL){
               ptw[w] = ptr[w]->next;
               a = ptr[w];
            }   
            if (a != NULL) {
               tmp = ptr[w]->w;
               ptr[w] = a->next;
               pa[tmp] = w;
               w = tmp;
               pre[w] = cnt++;
            }
            if (ptr[w] == NULL) {
               // A salsicha foi encurralada e irá fazer o movimento
               // reverso.
               while (ptr[w] == NULL) {
                  post[w] = cntt++;
                  if (w == pa[w]) 
                     break;
                  w = pa[w];
               }
               w = ptr[w];
            }   
         }
         post[v] = cntt++;
      }   
   }   
   return;
}   

