#!/usr/bin/env python3

import os



# pruebas de matrices

nList = [32,64,128,256,512,1024,2048,4096]
mList = [2,4,8,16]

# multiplicacion matrices rectangulares
for n in nList:

  for m in mList:
    
    print("pruebas de multiplicacion Matrices Rectangulares N="+str(n) + "x" + str(m) + "\n")
    os.system("./bin/mat_mul_iter " + "./data/mat/" + str(n) + "x" + str(m) + " " + "./data/mat/" + str(m) + "x" + str(n) + " " + "./output/mat/iter" + str(n) + "x" + str(n) + "_rect" + " " + "./output/iter_rect_stats")
    os.system("./bin/mat_mul_iter_opt " + "./data/mat/" + str(n) + "x" + str(m) + " " + "./data/mat/" + str(m) + "x" + str(n) + " " + "./output/mat/opt" + str(n) + "x" + str(n) + "_rect" + " " + "./output/opt_rect_stats")
    #os.system("./bin/strassen " + "./data/mat/" + str(n) + "x" + str(m) + " " + "./data/mat/" + str(m) + "x" + str(n) + " " + "./output/mat/strass" + str(n) + "x" + str(n) + "_rect" + " " + "./output/strass_rect_stats")


# multiplicacion matrices cuadradas 
for n in nList:
  
  print("pruebas de multiplicacion Matrices Cuadradas N="+str(n) + "x" + str(n) + "\n")
  os.system("./bin/mat_mul_iter " + "./data/mat/" + str(n) + "x" + str(n) + " " + "./data/mat/" + str(n) + "x" + str(n) + " " + "./output/mat/iter" + str(n) + "x" + str(n) + "_cuad" + " " + "./output/iter_cuad_stats")
  os.system("./bin/mat_mul_iter_opt " + "./data/mat/" + str(n) + "x" + str(n) + " " + "./data/mat/" + str(n) + "x" + str(n) + " " + "./output/mat/opt" + str(n) + "x" + str(n) + "_cuad" + " " + "./output/opt_cuad_stats")
  os.system("./bin/strassen " + "./data/mat/" + str(n) + "x" + str(n) + " " + "./data/mat/" + str(n) + "x" + str(n) + " " + "./output/mat/strass" + str(n) + "x" + str(n) + "_cuad" + " " + "./output/strass_cuad_stats")




nList = [10,50,100,200,500,1000,2500,5000,10000,25000,50000,75000,100000,150000,300000,500000,1000000]

# pruebas de sort
for n in nList:

  # tests de STDsort
  print("pruebas de STDsort para N="+str(n)+"\n")
  os.system("./bin/STDsort " + "./data/sort/" + str(n) + "ord" + " " + "./output/sort/std_ord_" + str(n) + " " + "./output/std_ord_stats")
  os.system("./bin/STDsort " + "./data/sort/" + str(n) + "rev" + " " + "./output/sort/std_rev_" + str(n) + " " + "./output/std_rev_stats")
  os.system("./bin/STDsort " + "./data/sort/" + str(n) + "rand" + " " + "./output/sort/std_rand_" + str(n) + " " + "./output/std_rand_stats")

  # tests de mergesort
  print("pruebas de mergesort para N="+str(n)+"\n")
  os.system("./bin/mergesort " + "./data/sort/" + str(n) + "ord" + " " + "./output/sort/merge_ord_" + str(n) + " " + "./output/merge_ord_stats")
  os.system("./bin/mergesort " + "./data/sort/" + str(n) + "rev" + " " + "./output/sort/merge_rev_" + str(n) + " " + "./output/merge_rev_stats")
  os.system("./bin/mergesort " + "./data/sort/" + str(n) + "rand" + " " + "./output/sort/merge_rand_" + str(n) + " " + "./output/merge_rand_stats")

  # tests de quicksort
  print("pruebas de quicksort para N="+str(n)+"\n")
  os.system("./bin/quicksort " + "./data/sort/" + str(n) + "ord" + " " + "./output/sort/quick_ord_" + str(n) + " " + "./output/quick_ord_stats")
  os.system("./bin/quicksort " + "./data/sort/" + str(n) + "rev" + " " + "./output/sort/quick_rev_" + str(n) + " " + "./output/quick_rev_stats")
  os.system("./bin/quicksort " + "./data/sort/" + str(n) + "rand" + " " + "./output/sort/quick_rand_" + str(n) + " " + "./output/quick_rand_stats")

  # tests de selectionsort
  print("pruebas de selectionsort para N="+str(n)+"\n")
  os.system("./bin/selectionsort " + "./data/sort/" + str(n) + "ord" + " " + "./output/sort/selection_ord_" + str(n) + " " + "./output/selection_ord_stats")
  os.system("./bin/selectionsort " + "./data/sort/" + str(n) + "rev" + " " + "./output/sort/selection_rev_" + str(n) + " " + "./output/selection_rev_stats")
  os.system("./bin/selectionsort " + "./data/sort/" + str(n) + "rand" + " " + "./output/sort/selection_rand_" + str(n) + " " + "./output/selection_rand_stats")



print("FIN")