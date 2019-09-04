// Blibioteca dos exercícios de sala
// E1.c ////////////////////////////////////////////////////////////////

bool
GRAPHisUndirected( Graph G );

bool* 
isSinkMatrix( Graph G );
   
bool* 
isSourceMatrix( Graph G );

bool* 
isSink( Graph G );

bool* 
isSource( Graph G );


// E2.c ////////////////////////////////////////////////////////////////
//
// Trata array como uma f: int->int, gerando f^(-1)
int*
ARRAYinverter( int* f, int size);

// Recebe um G e uma permutação de vértices e verifica se é topológico.
// Assume que vv tem comprimento igual ao número de vértices de G!
// *** Usa GRAPHcopy
bool
GRAPHlabelPemutationIsTopo( Graph G, vertex* vv );

// Constrói grafo não direcionado em grade mxn, numeração dos vértices
// corre ao longo das colunas.
UGraph
UGRAPHbuildGrid( int m, int n);
