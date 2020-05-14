#include <stdlib.h>
#include <stdio.h>
#include <time.h>


//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//
// El algoritmo de Strassen sigue el principio de Divide and Conquer para multiplicar las matrices X e Y.
// Divide las matrices X e Y en 8 submatrices, y luego calcula 7 ecuaciones de suma y multiplicacion de estas submatrices
//
// El problema de multiplicación X * Y = Z puede subdividirse en 8 multiplicaciones mas pequeñas:
//
//       X            Y             Z
//   | A B | x | E F | = | A*E+B*G   A*F+B*H |
//   | C D |   | G H |   | C*E+D*G   C*F+D*H |
//
//  1)  A*E
//  2)  B*G
//  3)  A*F
//  4)  B*H
//  5)  C*E
//  6)  D*G
//  7)  C*F
//  8)  D*H
//
//  Pero calcular esta multiplicación de matrices tiene el mismo tiempo de cálculo O(n^3) que el método tradicional de multiplicación.
//  Strassen demostró que calculando 7 ecuaciones basadas en las submatrices anteriores, puede obtenerse el mismo resultado.
//  Las ecuaciones son:
//
//  P1)  A*(F-H)
//  P2)  (A+B)*H
//  P3)  (C+D)*E
//  P4)  D*(G-E)
//  P5)  (A+D)*(E+H)
//  P6)  (B-D)*(G+H)
//  P7)  (A-C)*(E+F)
//
//  y el resultado se obtiene a partir de:
//
//                   Z
//   | P5+P4-P2+P6           P1+P2 |
//   | P3+P4           P1+P5-P3-P7 |
//
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


typedef struct {
    int **row;
    int n;
    int m;
}MAT;


void mat_mul_strassen(MAT *x, MAT *y, MAT *z);
void divide(MAT *x, MAT *y, MAT *z);
void mat_add(MAT *x, MAT *y, MAT *z);
void mat_sub(MAT *x, MAT *y, MAT *z);
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
  
  mat_mul_strassen(&x, &y, &z);
  
  // TERMINO DEL ALGORITMOs
  end = clock();
  
  // tiempo de ejecucion del algoritmo
  time = 1.0*(end - start)/CLOCKS_PER_SEC;
  
  // agregamos los tiempos en el archivo de estadisticas
  statsFile  = fopen(argv[4], "a");
  fprintf(statsFile, "mat_mul_strassen , con X de %dx%d e Y de %dx%d , tiempo = %lf \n", x.n, x.m, y.n, y.m, time);
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

void mat_mul_strassen(MAT *x, MAT *y, MAT *z) {
    
    if ((x->m != y->n))
        exit(printf("error: las matrices no tienen tamanos compatibles para multiplicacion"));

    // Con Strassen ambas matrices deben ser cuadradas en base 2 (investigar)
    if ((x->n%2==0) && (x->n == x->m) && (y->n == y->m)) {

        int ctr;

        // se define la matriz Z
        z->n = x->n;
        z->m = x->m;
        z->row = NULL;
        z->row = (int**)malloc(z->n * sizeof(int*));            // se pide memoria para las filas

        for (ctr=0; ctr<z->n; ctr++) {
            z->row[ctr] = NULL;
            z->row[ctr] = (int*)malloc(z->m * sizeof(int));     // se pide memoria para las columnas
        }

        // Se divide la multiplicacion de las matrices X e Y en sub multiplicaciones de submatrices
        // las matrices de la A..H y P1..P7 son creadas en tiempo de ejecución, por lo que es bastante lento
        // se puede buscar un método que haga referencia a las matrices x,y,z para evitar los mallocs extra
        divide(x, y, z);


        // Se divide la multiplicacion de las matrices X e Y en sub multiplicaciones de submatrices
        // definidas como trozos referenciados de las matrices X,Y,Z.
        //divide_ref(x, y, z);

    } else {
        // si alguna de las matrices no es cuadrada base 2, transformarla a cuadrada base 2,
        // volver a utilizar el algoritmo y recortar los excesos en el resultado final
    }
}


void divide(MAT *x, MAT *y, MAT *z) {

    // se fragmentan las matrices X e Y en las submatrices A,B,C,D,E,F,G,H
    // condicion de termino: el algoritmo recursivo se detiene cuando ya no se puede seguir fragmentando la matriz
    if (x->n>2) {

        int i,j,ctr;
        MAT A,B,C,D,E,F,G,H;
        MAT P1,P2,P3,P4,P5,P6,P7;
        MAT TEMP,TEMP2;

        //-----------------------------------------------------------------------------------

        // se define la matriz A
        A.n = x->n/2;
        A.m = x->n/2;
        A.row = NULL;
        A.row = (int**)malloc(A.n * sizeof(int*));        // se pide memoria para las filas
        for (ctr=0; ctr<A.n; ctr++) {
            A.row[ctr] = NULL;
            A.row[ctr] = (int*)malloc(A.m * sizeof(int)); // se pide memoria para las columnas
        }
        //rellenamos A
        for (i=0; i<x->n/2; i++) {
            for (j=0; j<x->m/2; j++) {
                A.row[i][j] = x->row[i][j];
            }
        }

        //-----------------------------------------------------------------------------------

        // se define la matriz B
        B.n = x->n/2;
        B.m = x->n/2;
        B.row = NULL;
        B.row = (int**)malloc(B.n * sizeof(int*));        // se pide memoria para las filas
        for (ctr=0; ctr<B.n; ctr++) {
            B.row[ctr] = NULL;
            B.row[ctr] = (int*)malloc(B.m * sizeof(int)); // se pide memoria para las columnas
        }
        //rellenamos B
        for (i=0; i<x->n/2; i++) {
            for (j=0; j<x->m/2; j++) {
                B.row[i][j] = x->row[i][j+x->m/2];
            }
        }

        //-----------------------------------------------------------------------------------

        // se define la matriz C
        C.n = x->n/2;
        C.m = x->n/2;
        C.row = NULL;
        C.row = (int**)malloc(C.n * sizeof(int*));        // se pide memoria para las filas
        for (ctr=0; ctr<C.n; ctr++) {
            C.row[ctr] = NULL;
            C.row[ctr] = (int*)malloc(C.m * sizeof(int)); // se pide memoria para las columnas
        }
        //rellenamos C
        for (i=0; i<x->n/2; i++) {
            for (j=0; j<x->m/2; j++) {
                C.row[i][j] = x->row[i+x->n/2][j];
            }
        }

        //-----------------------------------------------------------------------------------

        // se define la matriz D
        D.n = x->n/2;
        D.m = x->n/2;
        D.row = NULL;
        D.row = (int**)malloc(D.n * sizeof(int*));        // se pide memoria para las filas
        for (ctr=0; ctr<D.n; ctr++) {
            D.row[ctr] = NULL;
            D.row[ctr] = (int*)malloc(D.m * sizeof(int)); // se pide memoria para las columnas
        }
        //rellenamos D
        for (i=0; i<x->n/2; i++) {
            for (j=0; j<x->m/2; j++) {
                D.row[i][j] = x->row[i+x->n/2][j+x->m/2];
            }
        }

        //-----------------------------------------------------------------------------------

        // se define la matriz E
        E.n = y->n/2;
        E.m = y->n/2;
        E.row = NULL;
        E.row = (int**)malloc(E.n * sizeof(int*));        // se pide memoria para las filas
        for (ctr=0; ctr<E.n; ctr++) {
            E.row[ctr] = NULL;
            E.row[ctr] = (int*)malloc(E.m * sizeof(int)); // se pide memoria para las columnas
        }
        //rellenamos E
        for (i=0; i<y->n/2; i++) {
            for (j=0; j<y->m/2; j++) {
                E.row[i][j] = y->row[i][j];
            }
        }

        //-----------------------------------------------------------------------------------

        // se define la matriz F
        F.n = y->n/2;
        F.m = y->n/2;
        F.row = NULL;
        F.row = (int**)malloc(F.n * sizeof(int*));        // se pide memoria para las filas
        for (ctr=0; ctr<F.n; ctr++) {
            F.row[ctr] = NULL;
            F.row[ctr] = (int*)malloc(F.m * sizeof(int)); // se pide memoria para las columnas
        }
        //rellenamos F
        for (i=0; i<y->n/2; i++) {
            for (j=0; j<y->m/2; j++) {
                F.row[i][j] = y->row[i][j+y->m/2];
            }
        }

        //-----------------------------------------------------------------------------------

        // se define la matriz G
        G.n = y->n/2;
        G.m = y->n/2;
        G.row = NULL;
        G.row = (int**)malloc(G.n * sizeof(int*));        // se pide memoria para las filas
        for (ctr=0; ctr<G.n; ctr++) {
            G.row[ctr] = NULL;
            G.row[ctr] = (int*)malloc(G.m * sizeof(int)); // se pide memoria para las columnas
        }
        //rellenamos G
        for (i=0; i<y->n/2; i++) {
            for (j=0; j<y->m/2; j++) {
                G.row[i][j] = y->row[i+y->n/2][j];
            }
        }

        //-----------------------------------------------------------------------------------

        // se define la matriz H
        H.n = y->n/2;
        H.m = y->n/2;
        H.row = NULL;
        H.row = (int**)malloc(H.n * sizeof(int*));        // se pide memoria para las filas
        for (ctr=0; ctr<H.n; ctr++) {
            H.row[ctr] = NULL;
            H.row[ctr] = (int*)malloc(H.m * sizeof(int)); // se pide memoria para las columnas
        }
        //rellenamos H
        for (i=0; i<y->n/2; i++) {
            for (j=0; j<y->m/2; j++) {
                H.row[i][j] = y->row[i+y->n/2][j+y->m/2];
            }
        }

        //-----------------------------------------------------------------------------------

        // se calculan P1,P2,P3,P4,P5,P6,P7

        // P1 = A*(F-H)
        mat_sub(&F, &H, &TEMP);                 //   (F-H)
        mat_mul_strassen(&A, &TEMP, &P1);       // A*(F-H)
        mat_free(&TEMP);

        // P2 = (A+B)*H
        mat_add(&A, &B, &TEMP);                 // (A+B)
        mat_mul_strassen(&TEMP, &H, &P2);       // (A+B)*H
        mat_free(&TEMP);

        // P3 = (C+D)*E
        mat_add(&C, &D, &TEMP);                 // (C+D)
        mat_mul_strassen(&TEMP, &E, &P3);       // (C+D)*E
        mat_free(&TEMP);

        // P4 = D*(G-E)
        mat_sub(&G, &E, &TEMP);                 //   (G-E)
        mat_mul_strassen(&D, &TEMP, &P4);       // D*(G-E)
        mat_free(&TEMP);

        // P5 = (A+D)*(E+H)
        mat_add(&A, &D, &TEMP);                 // (A+D)
        mat_add(&E, &H, &TEMP2);                //       (E+H)
        mat_mul_strassen(&TEMP, &TEMP2, &P5);   // (A+D)*(E+H)
        mat_free(&TEMP);
        mat_free(&TEMP2);

        // P6 = (B-D)*(G+H)
        mat_sub(&B, &D, &TEMP);                 // (B-D)
        mat_add(&G, &H, &TEMP2);                //       (G+H)
        mat_mul_strassen(&TEMP, &TEMP2, &P6);   // (B-D)*(G+H)
        mat_free(&TEMP);
        mat_free(&TEMP2);

        // P7 = (A-C)*(E+F)
        mat_sub(&A, &C, &TEMP);                 // (A-C)
        mat_add(&E, &F, &TEMP2);                //       (E+F)
        mat_mul_strassen(&TEMP, &TEMP2, &P7);   // (A-C)*(E+F)
        mat_free(&TEMP);
        mat_free(&TEMP2);

    //-----------------------------------------------------------------------------------

        //  Rellenamos la matriz de solucion Z de la forma:
        //
        //           | P5+P4-P2+P6           P1+P2 |
        //   Z   =   |                             |
        //           | P3+P4           P1+P5-P3-P7 |
        //

        // primer cuadrante
        mat_add(&P5, &P4, &TEMP);       //   P5+P4
        mat_sub(&TEMP, &P2, &TEMP2);    //  (P5+P4)-P2
        mat_free(&TEMP);
        mat_add(&TEMP2, &P6, &TEMP);    // ((P5+P4)-P2)+P6
        mat_free(&TEMP2);
        for (i=0; i<z->n/2; i++) {
            for (j=0; j<z->m/2; j++) {
                z->row[i][j] = TEMP.row[i][j];
            }
        }
        mat_free(&TEMP);

        // segundo cuadrante
        mat_add(&P1, &P2, &TEMP);       //   P1+P2
        for (i=0; i<z->n/2; i++) {
            for (j=0; j<z->m/2; j++) {
                z->row[i][j+z->m/2] = TEMP.row[i][j];
            }
        }
        mat_free(&TEMP);

        // tercer cuadrante
        mat_add(&P3, &P4, &TEMP);       //   P3+P4
        for (i=0; i<z->n/2; i++) {
            for (j=0; j<z->m/2; j++) {
                z->row[i+z->n/2][j] = TEMP.row[i][j];
            }
        }
        mat_free(&TEMP);

        // cuarto cuadrante
        mat_add(&P1, &P5, &TEMP);       //  P1+P5
        mat_sub(&TEMP, &P3, &TEMP2);    // (P1+P5)-P3
        mat_free(&TEMP);
        mat_sub(&TEMP2, &P7, &TEMP);    //((P1+P5)-P3)-P7
        mat_free(&TEMP2);
        for (i=0; i<z->n/2; i++) {
            for (j=0; j<z->m/2; j++) {
                z->row[i+z->n/2][j+z->m/2] = TEMP.row[i][j];
            }
        }
        mat_free(&TEMP);

        // liberamos la memoria de todas las matrices utilizadas para los calculos
        mat_free(&A);
        mat_free(&B);
        mat_free(&C);
        mat_free(&D);
        mat_free(&E);
        mat_free(&F);
        mat_free(&G);
        mat_free(&H);
        mat_free(&P1);
        mat_free(&P2);
        mat_free(&P3);
        mat_free(&P4);
        mat_free(&P5);
        mat_free(&P6);
        mat_free(&P7);

    //-----------------------------------------------------------------------------------

    // la condicion de termino del algoritmo de strassen ocurre cuando llegamos a una simple matriz de 2x2
    // en este caso podemos devolver la multiplicacion simple de matrices
    } else {
        z->row[0][0] = x->row[0][0]*y->row[0][0] + x->row[0][1]*y->row[1][0];
        z->row[0][1] = x->row[0][0]*y->row[0][1] + x->row[0][1]*y->row[1][1];
        z->row[1][0] = x->row[1][0]*y->row[0][0] + x->row[1][1]*y->row[1][0];
        z->row[1][1] = x->row[1][0]*y->row[0][1] + x->row[1][1]*y->row[1][1];
    }
}


// z = x + y
void mat_add(MAT *x, MAT *y, MAT *z) {
    int i,j;
    // se define z
    z->n = x->n;
    z->m = x->m;
    z->row = NULL;
    // se pide memoria para la matriz z
    z->row = (int**)malloc(z->n * sizeof(int*));
    for (i=0; i<z->n; i++) {
        z->row[i] = NULL;
        z->row[i] = (int*)malloc(z->m * sizeof(int));
    }
    // se calcula z = x + y para cada elemento de z
    for (i=0; i<x->n; i++) {
        for (j=0; j<x->m; j++) {
            z->row[i][j] = x->row[i][j] + y->row[i][j];
        }
    }
}


// z = x - y
void mat_sub(MAT *x, MAT *y, MAT *z) {
    int i,j;
    // se define z
    z->n = x->n;
    z->m = x->m;
    z->row = NULL;
    // se pide memoria para la matriz z
    z->row = (int**)malloc(z->n * sizeof(int*));
    for (i=0; i<z->n; i++) {
        z->row[i] = NULL;
        z->row[i] = (int*)malloc(z->m * sizeof(int));
    }
    // se calcula z = x - y para cada elemento de z
    for (i=0; i<x->n; i++) {
        for (j=0; j<x->m; j++) {
            z->row[i][j] = x->row[i][j] - y->row[i][j];
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

