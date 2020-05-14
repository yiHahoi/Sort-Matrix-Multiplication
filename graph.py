#!/usr/bin/python

import numpy as np
import matplotlib.pyplot as plt
import os

#####################################################################
#####################################################################
##################         ARREGLOS          ########################
#####################################################################
#####################################################################

#-----------------------------------------------

# figura 1
fig1 = plt.figure()
plt.title("Merge Sort")
plt.xlabel("N")
plt.ylabel("tiempo [s]")

#-----------------------------------------------

dataFile = open("output/merge_ord_stats","r")

n    = []
time = []

for line in dataFile:
  pair = line.split(',')
  temp = pair[1].split('= ')
  n.append(int(temp[1]))
  temp = pair[2].split('= ')
  time.append(float(temp[1]))
dataFile.close()

plt.plot(n,time,'-r', label='Arreglo Ordenado')

#-----------------------------------------------

dataFile = open("output/merge_rand_stats","r")

n    = []
time = []

for line in dataFile:
  pair = line.split(',')
  temp = pair[1].split('= ')
  n.append(int(temp[1]))
  temp = pair[2].split('= ')
  time.append(float(temp[1]))
dataFile.close()

plt.plot(n,time,'-g', label='Arreglo Aleatorio')

#-----------------------------------------------

dataFile = open("output/merge_rev_stats","r")

n    = []
time = []

for line in dataFile:
  pair = line.split(',')
  temp = pair[1].split('= ')
  n.append(int(temp[1]))
  temp = pair[2].split('= ')
  time.append(float(temp[1]))
dataFile.close()

plt.plot(n,time,'-b', label='Arreglo Invertido')

#-----------------------------------------------

plt.legend()
plt.show()
#fig1.savefig()

#-----------------------------------------------

# figura 2
fig2 = plt.figure()
plt.title("Selection Sort")
plt.xlabel("N")
plt.ylabel("tiempo [s]")

#-----------------------------------------------

dataFile = open("output/selection_ord_stats","r")

n    = []
time = []

for line in dataFile:
  pair = line.split(',')
  temp = pair[1].split('= ')
  n.append(int(temp[1]))
  temp = pair[2].split('= ')
  time.append(float(temp[1]))
dataFile.close()

plt.plot(n,time,'-r', label='Arreglo Ordenado')

#-----------------------------------------------

dataFile = open("output/selection_rand_stats","r")

n    = []
time = []

for line in dataFile:
  pair = line.split(',')
  temp = pair[1].split('= ')
  n.append(int(temp[1]))
  temp = pair[2].split('= ')
  time.append(float(temp[1]))
dataFile.close()

plt.plot(n,time,'-g', label='Arreglo Aleatorio')

#-----------------------------------------------

dataFile = open("output/selection_rev_stats","r")

n    = []
time = []

for line in dataFile:
  pair = line.split(',')
  temp = pair[1].split('= ')
  n.append(int(temp[1]))
  temp = pair[2].split('= ')
  time.append(float(temp[1]))
dataFile.close()

plt.plot(n,time,'-b', label='Arreglo Invertido')

#-----------------------------------------------

plt.legend()
plt.show()
#fig2.savefig()

#-----------------------------------------------

# figura 3
fig3 = plt.figure()
plt.title("Quick Sort")
plt.xlabel("N")
plt.ylabel("tiempo [s]")

#-----------------------------------------------

dataFile = open("output/quick_ord_stats","r")

n    = []
time = []

for line in dataFile:
  pair = line.split(',')
  temp = pair[1].split('= ')
  n.append(int(temp[1]))
  temp = pair[2].split('= ')
  time.append(float(temp[1]))
dataFile.close()

plt.plot(n,time,'-r', label='Arreglo Ordenado')

#-----------------------------------------------

dataFile = open("output/quick_rand_stats","r")

n    = []
time = []

for line in dataFile:
  pair = line.split(',')
  temp = pair[1].split('= ')
  n.append(int(temp[1]))
  temp = pair[2].split('= ')
  time.append(float(temp[1]))
dataFile.close()

plt.plot(n,time,'-g', label='Arreglo Aleatorio')

#-----------------------------------------------

dataFile = open("output/quick_rev_stats","r")

n    = []
time = []

for line in dataFile:
  pair = line.split(',')
  temp = pair[1].split('= ')
  n.append(int(temp[1]))
  temp = pair[2].split('= ')
  time.append(float(temp[1]))
dataFile.close()

plt.plot(n,time,'-b', label='Arreglo Invertido')

#-----------------------------------------------

plt.legend()
plt.show()
#fig3.savefig()

#-----------------------------------------------

# figura 4
fig2 = plt.figure()
plt.title("STD C Sort")
plt.xlabel("N")
plt.ylabel("tiempo [s]")

#-----------------------------------------------

dataFile = open("output/std_ord_stats","r")

n    = []
time = []

for line in dataFile:
  pair = line.split(',')
  temp = pair[1].split('= ')
  n.append(int(temp[1]))
  temp = pair[2].split('= ')
  time.append(float(temp[1]))
dataFile.close()

plt.plot(n,time,'-r', label='Arreglo Ordenado')

#-----------------------------------------------

dataFile = open("output/std_rand_stats","r")

n    = []
time = []

for line in dataFile:
  pair = line.split(',')
  temp = pair[1].split('= ')
  n.append(int(temp[1]))
  temp = pair[2].split('= ')
  time.append(float(temp[1]))
dataFile.close()

plt.plot(n,time,'-g', label='Arreglo Aleatorio')

#-----------------------------------------------

dataFile = open("output/std_rev_stats","r")

n    = []
time = []

for line in dataFile:
  pair = line.split(',')
  temp = pair[1].split('= ')
  n.append(int(temp[1]))
  temp = pair[2].split('= ')
  time.append(float(temp[1]))
dataFile.close()

plt.plot(n,time,'-b', label='Arreglo Inverso')

#-----------------------------------------------

plt.legend()
plt.show()
#fig2.savefig()



#####################################################################
#####################################################################
##################         MATRICES          ########################
#####################################################################
#####################################################################




#-----------------------------------------------

# figura 5
fig5 = plt.figure()
plt.title("Multiplicacion Matrices NxN")
plt.xlabel("N")
plt.ylabel("tiempo [s]")

#-----------------------------------------------

dataFile = open("output/iter_cuad_stats","r")

n    = []
time = []

for line in dataFile:
  pair = line.split(',')
  temp = pair[1].split('Y de ')
  temp2 = temp[1].split('x')
  n.append(int(temp2[0]))
  temp = pair[2].split('= ')
  time.append(float(temp[1]))
dataFile.close()

plt.plot(n,time,'-r', label='Iterativo clasico')

#-----------------------------------------------

dataFile = open("output/opt_cuad_stats","r")

n    = []
time = []

for line in dataFile:
  pair = line.split(',')
  temp = pair[1].split('Y de ')
  temp2 = temp[1].split('x')
  n.append(int(temp2[0]))
  temp = pair[2].split('= ')
  time.append(float(temp[1]))
dataFile.close()

plt.plot(n,time,'-g', label='Iterativo Optimizado')

#-----------------------------------------------

dataFile = open("output/strass_cuad_stats","r")

n    = []
time = []

for line in dataFile:
  pair = line.split(',')
  temp = pair[1].split('Y de ')
  temp2 = temp[1].split('x')
  n.append(int(temp2[0]))
  temp = pair[2].split('= ')
  time.append(float(temp[1]))
dataFile.close()

plt.plot(n,time,'-b', label='Strassen')

#-----------------------------------------------

plt.legend()
plt.show()
#fig2.savefig()





