#include <stdlib.h>
#include <stdio.h>
#include <time.h>



void swap(int *x, int *y);
void selectionSort(int *v, int n);


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
  
  selectionSort(vec,n);
  
  // TERMINO DEL ALGORITMOs
  end = clock();
  
  // tiempo de ejecucion del algoritmo
  time = 1.0*(end - start)/CLOCKS_PER_SEC;
  
  // agregamos los tiempos en el archivo de estadisticas
  statsFile  = fopen(argv[3], "a");
  fprintf(statsFile, "selectionSort , con N = %d , tiempo = %f \n", n, time);
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


void selectionSort(int *v, int n) {

    int i,j,min,temp;
    for (i=0; i<n-1; i++) {     // se compara el elemento en i con todos los siguientes
        min = i;
        for (j=i+1; j<n; j++) {
            if (v[j]<v[min])    // si se encuentra un elemento menor que i se guarda su índice
                min = j;
        }
        if (min != i) {         // se hace un swap entre ambos elementos
            swap(&v[min],&v[i]);
        }
    }
}


void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}


