#define MAX_V 1000


bool* 
isSinkMatrix( Graph G );
   
bool* 
isSourceMatrix( Graph G );

bool* 
isSink( Graph G );

bool* 
isSource( Graph G );

// GRAPHlists.h
void
GRAPHremoveArc ( Graph G, vertex v, vertex w);

// GRAPHlists.h
Graph
GRAPHcopy ( Graph G);

// Otimizada para grafos esparsos e grandes
bool
GRAPHisUndirected( Graph G );

bool* 
isSinkMatrix( Graph G ){
   
   bool* isSink = malloc( G->V * sizeof( bool));

   for ( vertex v = 0; v < G->V; v++){
      for ( vertex w; v < G->V; w++)
         if ( G->adj[v][w] == 1 ){
            isSink[v] = 0;
            break;
         } 
      
      if ( w == G->V )
         isSink[v] = 1;
   }
   return isSink;   
}  

bool* 
isSourceMatrix( Graph G ){
   
   bool* isSource = malloc( G->V * sizeof( bool));

   for ( vertex v = 0; v < G->V; v++){
      for ( vertex w = 0; v < G->V; w++)
         if ( G->adj[w][v] == 1 ){
            isSource[v] = 0;
            break;
         } 
      
      if ( w == G->V )
         isSource[v] = 1;
   }
   return isSource;   
}  

bool* 
isSink( Graph G ){

   bool* isSink = malloc( G->V * sizeof( bool));

   for ( vertex v = 0; v < G->V; v++){
      if ( G->adj[v] != NULL )
         isSink[v] = 0;
      else
         isSink[v] = 1; 

   }   

   return isSink;   
}

bool* 
isSource( Graph G ){
   
   bool* isSource = malloc( G->V * sizeof( bool));
   int sources = G->V;

   for ( vertex v = 0; v < G->V; v++)
      isSource[v] = 1;

   for ( vertex v = 0; v < G->V; v++){
      for ( link a = G->adj[v]; a != NULL; a = a->next)
         if ( isSource[a->w] == 1 ){
            isSource[a->w] = 0;
            sources = sources - 1;
            if ( sources == 0 )
               return isSource;
         }      

   }

   return isSource;   
}      


void
GRAPHremoveArc( Graph G, vertex v, vertex w){
   
   link p = G->adj[v];
   link prev = G->adj[v];
   if ( p->w == w ){
      G->adj[v] = p->next;
      free(p);
      return;
   }
   p = p->next   
   while ( p != NULL ){
      if ( p->w == w ){
         prev->next = p->next;
         free(p)
         return;
      }
   }   
}   
// Incompleto!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Implementação O(1) para remover arcos, necessita do endereço do link
// anterior 
void
GRAPHremoveArcQuick( Graph G, link a){
   
   link p = G->adj[v];
   link prev = G->adj[v];
   if ( p->w == w ){
      G->adj[v] = p->next;
      free(p);
      return;
   }
   p = p->next   
   while ( p != NULL ){
      if ( p->w == w ){
         prev->next = p->next;
         free(p)
         return;
      }
   }   
}   

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// Targ = Target
// Copia a estutura de G, e elimina arco, se achar seu recíproco, 
// elimina-o também, senão, retorna false.
// IMPLEMENTAR UM GRAPHremoveArcQuick
bool
GRAPHisUndirected( Graph G ){

   bool isUndirected;
   Graph Gcopy;
   vertex = arcTarg;
   link targ;

   Gcopy = GRAPHcopy( G);
   for ( vertex v = 0; v < Gcopy->V; v++){
      for ( link w = Gcopy->adj[v]; w != NULL; w = w->next){
         arcTarg = w->w;
         GRAPHremoveArc( Gcopy, v, w);
         for ( targ = Gcopy->adj[w]; targ != NULL; targ = targ->next ){ 
            if ( targ->w == v ){
                GRAPHremoveArc( Gcopy, w, v );
                break;    
            }   
         }
         if ( targ == NULL )
            return false;
      }
   }
   return true;   
}   


Graph
GRAPHcopy ( Graph G){
   
   Graph Gcopy;
   Gcopy = GRAPHinit( G->V);
   
   for ( vertex v = 0; v < G->V; v++)
      for ( link w = G->adj[v]; w != NULL; w = w->next)
         GRAPHinsertArc( Gcopy, v, w);
   
   return Gcopy;

}   

