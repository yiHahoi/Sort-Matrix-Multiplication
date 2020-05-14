#include <stdlib.h>
#include <stdio.h>
#include <time.h>



void swap(int *x, int *y);
void mergeSort(int *v, int n);
void merge(int *v, int n, int r);



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
  
  mergeSort(vec,n);
  
  // TERMINO DEL ALGORITMOs
  end = clock();
  
  // tiempo de ejecucion del algoritmo
  time = 1.0*(end - start)/CLOCKS_PER_SEC;
  
  // agregamos los tiempos en el archivo de estadisticas
  statsFile  = fopen(argv[3], "a");
  fprintf(statsFile, "mergeSort , con N = %d , tiempo = %f \n", n, time);
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


void mergeSort(int *v, int n) {
    int r = 0;
    if (n>1) {
        if (n%2!=0) r = 1;          // si n es impar
        mergeSort(v, n/2);          // mergeSort de mitad inferior
        mergeSort(&v[n/2], r+n/2);  // mergeSort de mitad superior
        merge(v, n, r);             // se juntan ambas mitades en orden
    }
}


void merge(int *v, int n, int r) {
    int i=0, j=n/2, ctr=0;
    int temp[n];                    // (hacer pruebas con temp en stack y heap)

    while (i<n/2 && j<n) {          // se comparan ambos subvectores y se copia el menor elemento a un vector temporal
        if (v[i]<=v[j])
            temp[ctr++] = v[i++];
        else
            temp[ctr++] = v[j++];
    }

    while (i<n/2)                   // se copia el resto del subvector 1 en caso de no haberse recorrido por completo
        temp[ctr++] = v[i++];

    while (j<n)                     // se copia el resto del subvector 2 en caso de no haberse recorrido por completo
        temp[ctr++] = v[j++];

    for (ctr=0; ctr<n; ctr++) {     // se guardan los valores ordenados en el vector principal
        v[ctr] = temp[ctr];
    }
}


void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}


