#!/usr/bin/python

import random


nList = [10,50,100,200,500,1000,2500,5000,10000,25000,50000,75000,100000,150000,300000,500000,1000000]


for n in nList:
  
  # se generan los vectores ordenados
  array = range(n)
  fileName = str(n)+"ord"
  file = open(fileName, 'w')
  file.write(str(n)+" ")
  for x in array:
    file.write(str(x)+" ")
  file.close()
    
  # se generan copias invertidas
  array.sort(reverse=True)
  fileName = str(n)+"rev"
  file = open(fileName, 'w')
  file.write(str(n)+" ")
  for x in array:
    file.write(str(x)+" ")
  file.close()
  
  
  # se generan copias desordenadas
  random.shuffle(array)
  fileName = str(n)+"rand"
  file = open(fileName, 'w')
  file.write(str(n)+" ")
  for x in array:
    file.write(str(x)+" ")
  file.close()
  


