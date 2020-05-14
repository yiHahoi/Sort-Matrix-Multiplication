#include <stdlib.h>
#include <stdio.h>
#include <time.h>


void swap(int *x, int *y);
void quickSort(int *v, int n);
int pivot(int *v, int n);



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
  
  quickSort(vec,n);
  
  // TERMINO DEL ALGORITMOs
  end = clock();
  
  // tiempo de ejecucion del algoritmo
  time = 1.0*(end - start)/CLOCKS_PER_SEC;
  
  // agregamos los tiempos en el archivo de estadisticas
  statsFile  = fopen(argv[3], "a");
  fprintf(statsFile, "quickSort , con N = %d , tiempo = %f \n", n, time);
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


void quickSort(int *v, int n) {             // quicksort usando primer elemento como pivote
    if (n>1) {
        int piv = pivot(v,n);
        quickSort(v, piv);                  // quickSort bajo pivote
        quickSort(&v[piv+1], n-piv-1);      // quickSort sobre pivote
    }
}


int pivot(int *v, int n){
    int i, j=n-1;
    int temp, piv=0;
    for (i=1; i<j+1; i++) {
        if (v[i]<v[piv]){         // si el siguiente elemento es menor que pivot se hace un swap y actualiza pivot
            swap(&v[piv],&v[i]);
            piv = i;
        } else {                  // si el siguiente elemento es mayor que pivot se mueve al final y actualiza indice final
            swap(&v[i],&v[j]);
            j--;                  // indice donde comienzan los elementos mayores que el pivote
            i--;                  // se repite la comparacion en la posicion i con el nuevo valor despues del swap
        }
    }
    return piv;
}


void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}


