#!/usr/bin/python

import random
import numpy as np


nList = [32,64,128,256,512,1024,2048,4096]
mList = [2,4,8,16]


# se generan matrices cuadradas
for n in nList:
  
  # matrices de elementos aleatorios de 0 a 9 
  vec = np.arange(n*n)
  for i in range(n*n):
    vec[i] = random.randint(0,9)
  random.shuffle(vec)
  mat = vec.reshape(n,n)
  fileName = str(n)+"x"+str(n)
  file = open(fileName, 'w')
  file.write(str(n)+"\n")
  file.write(str(n)+"\n")
  
  for i in range(n):
    for j in range(n):
      file.write(str(mat[i][j])+" ")
    file.write("\n")
  file.close()


# se generan matrices rectangulares n x m
for n in nList:

  for m in mList:

    # matrices de elementos aleatorios de 0 a 9 
    vec = np.arange(n*m)
    for i in range(n*m):
      vec[i] = random.randint(0,9)
    random.shuffle(vec)
    mat = vec.reshape(n,m)
    fileName = str(n)+"x"+str(m)
    file = open(fileName, 'w')
    file.write(str(n)+"\n")
    file.write(str(m)+"\n")
    
    for i in range(n):
      for j in range(m):
        file.write(str(mat[i][j])+" ")
      file.write("\n")
    file.close()


# se generan matrices rectangulares m x n
for n in nList:

  for m in mList:

    # matrices de elementos aleatorios de 0 a 9 
    vec = np.arange(n*m)
    for i in range(n*m):
      vec[i] = random.randint(0,9)
    random.shuffle(vec)
    mat = vec.reshape(m,n)
    fileName = str(m)+"x"+str(n)
    file = open(fileName, 'w')
    file.write(str(m)+"\n")
    file.write(str(n)+"\n")
    
    for i in range(m):
      for j in range(n):
        file.write(str(mat[i][j])+" ")
      file.write("\n")
    file.close()


  







