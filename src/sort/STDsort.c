#include <stdlib.h>
#include <stdio.h>
#include <time.h>


int cmp(const void *x, const void *y){
  if ( *(int*)x > *(int*)y)
    return 1;
  else if ( *(int*)x < *(int*)y)
    return -1;
  else
    return 0; 
}


// el programa recibe argumentos 
int main(int argc, char** argv) {
 
  FILE *inputFile;
  FILE *outputFile;
  FILE *statsFile;
  clock_t start, end;
  double time;
  int ctr, n, *vec;

  // argumentos que definen input, output, stats
  if (argc != 4)
    exit(printf("no se entregaron suficientes argumentos"));
  
  inputFile  = fopen(argv[1], "r");

  // datos de vector en archivo de entrada
  fscanf(inputFile,"%d", &n);
  vec = malloc(n * sizeof(int));
  for (ctr=0; ctr<n; ctr++) {
    fscanf(inputFile, "%d", &vec[ctr]);
  }
  fclose(inputFile);

  start = clock();
  // SE EJECUTA EL ALGORITMO
  
  qsort(vec, n, sizeof(int), cmp);
  
  // TERMINO DEL ALGORITMOs
  end = clock();
  
  // tiempo de ejecucion del algoritmo
  time = 1.0*(end - start)/CLOCKS_PER_SEC;
  
  // agregamos los tiempos en el archivo de estadisticas
  statsFile  = fopen(argv[3], "a");
  fprintf(statsFile, "C STD qsort , con N = %d , tiempo = %f \n", n, time);
  fclose(statsFile);
  
  // guardamos el vector solucion en el archivo de output
  outputFile = fopen(argv[2], "w");
  fprintf(outputFile, "%d ", n);
  for (ctr=0; ctr<n; ctr++) {
    fprintf(outputFile, "%d ", vec[ctr]);
  }
  fclose(outputFile);

  // se libera la memoria del vector dinamico  
  free(vec);
  
  return(0);

}





