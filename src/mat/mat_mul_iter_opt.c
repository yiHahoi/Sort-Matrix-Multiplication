#include <stdlib.h>
#include <stdio.h>
#include <time.h>


typedef struct {
    int **row;
    int n;
    int m;
}MAT;


void mat_mul_iter_opt(MAT *a, MAT *b, MAT *c);
void mat_transpose(MAT *b, MAT *bt);
void mat_free(MAT *x);
void mat_print(MAT *x);


// el programa recibe argumentos 
int main(int argc, char** argv) {
 
  FILE *inputMat1File;
  FILE *inputMat2File;
  FILE *outputMatFile;
  FILE *statsFile;
  clock_t start, end;
  double time;
  int ctr, ctr2;
  MAT x, y, z;

  // argumentos que definen input, output, stats
  if (argc != 5)
    exit(printf("no se entregaron suficientes argumentos"));

  // datos de matriz 1 en archivo de entrada 1
  inputMat1File  = fopen(argv[1], "r");
  fscanf(inputMat1File,"%d", &x.n);
  fscanf(inputMat1File,"%d", &x.m);
  // se pide memoria suficiente para matriz 1
  x.row = malloc(x.n * sizeof(int*));
  for (ctr=0; ctr<x.n; ctr++) {
    x.row[ctr] = malloc(x.m * sizeof(int));
  }
  // se rellena la matriz 1
  for (ctr=0; ctr<x.n; ctr++) {
    for (ctr2=0; ctr2<x.m; ctr2++) {
      fscanf(inputMat1File, "%d", &x.row[ctr][ctr2]);
    }
  }
  fclose(inputMat1File);
  
  // datos de matriz 2 en archivo de entrada 2
  inputMat2File  = fopen(argv[2], "r");
  fscanf(inputMat2File,"%d", &y.n);
  fscanf(inputMat2File,"%d", &y.m);
  // se pide memoria suficiente para matriz 2
  y.row = malloc(y.n * sizeof(int*));
  for (ctr=0; ctr<y.n; ctr++) {
    y.row[ctr] = malloc(y.m * sizeof(int));
  }
  // se rellena la matriz 2
  for (ctr=0; ctr<y.n; ctr++) {
    for (ctr2=0; ctr2<y.m; ctr2++) {
      fscanf(inputMat2File, "%d", &y.row[ctr][ctr2]);
    }
  }
  fclose(inputMat2File);
 

  start = clock();
  // SE EJECUTA EL ALGORITMO
  
  mat_mul_iter_opt(&x, &y, &z);
  
  // TERMINO DEL ALGORITMOs
  end = clock();
  
  // tiempo de ejecucion del algoritmo
  time = 1.0*(end - start)/CLOCKS_PER_SEC;
  
  // agregamos los tiempos en el archivo de estadisticas
  statsFile  = fopen(argv[4], "a");
  fprintf(statsFile, "mat_mul_iter_opt , con X de %dx%d e Y de %dx%d , tiempo = %f \n", x.n, x.m, y.n, y.m, time);
  fclose(statsFile);
  
  // guardamos la matriz solucion en el archivo de output
  outputMatFile = fopen(argv[3], "w");
  fprintf(outputMatFile, "%d\n", z.n);
  fprintf(outputMatFile, "%d\n", z.m);
  for (ctr=0; ctr<z.n; ctr++) {
    for (ctr2=0; ctr2<z.m; ctr2++) {
      fprintf(outputMatFile, "%d ", z.row[ctr][ctr2]);
    }
    fprintf(outputMatFile, "\n");
  }
  fclose(outputMatFile);

  // se libera la memoria de las matrices
  mat_free(&x);
  mat_free(&y);
  mat_free(&z);
  
  return(0);

}


// La funcion mat_mul_iter puede optimizarse transformando la matriz B a la matriz transpuesta
// y multiplicando filas de A por filas de B, de esta forma la cache aprovecha mejor la localidad espacial de B
void mat_mul_iter_opt(MAT *a, MAT *b, MAT *c) {

    // m de A debe ser igual a n de B
    if (a->m != b->n)
        exit(printf("error: las matrices no tienen tamanos compatibles para multiplicacion"));

    int ctr,i,j;

    // se define la matriz C
    c->n = a->n;
    c->m = b->m;
    c->row = NULL;
    c->row = (int**)malloc(c->n * sizeof(int*));    // se pide memoria para las filas

    for (ctr=0; ctr<c->n; ctr++) {
        c->row[ctr] = NULL;
        c->row[ctr] = (int*)malloc(c->m * sizeof(int));     // se pide memoria para las columnas
    }

    // se calcula C = A x* Bt
    // con B traspuesta y una cuasi multiplicacion de matrices de filas x filas
    MAT bt;
    mat_transpose(b,&bt);
    for (i=0; i<c->n; i++) {
        for (j=0; j<c->m; j++) {
            c->row[i][j] = 0;
            for (ctr=0; ctr<a->m; ctr++)
                c->row[i][j] += a->row[i][ctr] * bt.row[j][ctr];
        }
    }
    mat_free(&bt);  // una vez calculada la matriz c, se puede liberar la memoria de la matriz traspuesta temporal bt
}


void mat_transpose(MAT *b, MAT *bt){
    int i, j;
    // se define bt
    bt->n = b->m;
    bt->m = b->n;
    bt->row = NULL;
    bt->row = (int**)malloc(bt->n * sizeof(int*));  // se pide memoria para las filas
    for (i=0; i<bt->n; i++) {                       // se pide memoria para las columnas
        bt->row[i] = (int*)malloc(bt->m * sizeof(int));
    }
    // se copian los datos de b a bt de forma traspuesta
    for (i=0; i<b->n; i++) {
        for (j=0; j<b->m; j++) {
            bt->row[j][i] = b->row[i][j];
        }
    }
}


void mat_free(MAT *mat) {
    int ctr;
    for (ctr=0; ctr<mat->n; ctr++)
        free(mat->row[ctr]);
    free(mat->row);
    mat->n = 0;
    mat->m = 0;
}


void mat_print(MAT *x) {
    int i,j;
    for (i=0; i<x->n; i++) {
        for (j=0; j<x->m; j++)
            printf("%d ",x->row[i][j]);
        printf("\n\n");
    }
}


