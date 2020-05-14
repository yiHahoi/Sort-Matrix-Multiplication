#!/usr/bin/env python3

import os


# Se limpian las carpetas
print("removing files")
os.system("rm -r output/*")
os.system("rm -r data/*")
os.system("rm -r bin/*")
print("creating folders")
os.system("mkdir data/mat")
os.system("mkdir data/sort")
os.system("mkdir output/mat")
os.system("mkdir output/sort")

# Se compilan los programas
print("compiling programs")
os.system("gcc src/sort/selectionsort.c -o bin/selectionsort")
os.system("gcc src/sort/mergesort.c -o bin/mergesort")
os.system("gcc src/sort/quicksort.c -o bin/quicksort")
os.system("gcc src/sort/STDsort.c -o bin/STDsort")
os.system("gcc src/mat/mat_mul_iter.c -o bin/mat_mul_iter")
os.system("gcc src/mat/mat_mul_iter_opt.c -o bin/mat_mul_iter_opt")
os.system("gcc src/mat/strassen.c -o bin/strassen")

# Se generan los datos de prueba
os.system("cp src/dataGen/arrayGen.py data/sort/")
os.system("cp src/dataGen/matrixGen.py data/mat/")
#os.system("cd data/sort/")
#os.system("chmod +x data/sort/arrayGen.py")
#os.system("./data/sort/arrayGen.py")
#os.system("rm arrayGen.py")
#os.system("cd ..")
#os.system("cd data/mat/")
#os.system("chmod +x data/mat/matrixGen.py")
#os.system("./data/mat/matrixGen.py")
#os.system("rm matGen.py")
#os.system("cd ..")
#os.system("cd ..")

print("LISTO")