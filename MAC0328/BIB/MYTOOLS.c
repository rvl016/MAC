
// Trata array como uma f: int->int, gerando f^(-1)
int*
ARRAYinverter( int* f, int size){

   int *fInv = ( int*) malloc( size * sizeof( int));
   for ( int i = 0; i < size; i++ )
      fInv[f[i]] = i;
   return fInv;
}   
