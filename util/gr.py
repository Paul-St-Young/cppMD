#!/usr/bin/env python

import matplotlib.pyplot as plt
import numpy
import argparse

parser = argparse.ArgumentParser(description='plot g(r)')
parser.add_argument("gr", help="output to analyze.")
parser.add_argument('-e','--equil',type=int, help="number of equilibration steps", default=0)
args = parser.parse_args()

f=open(args.gr,'r')
GR=[]
for line in f:
    line = line.replace('(',' ')
    line = line.replace(')',' ')
    step,gr = line.split()[0], line.split()[1:]
    for i in range(len(gr)):
        gr[i]=float(gr[i])
    if step>=args.equil:
        GR.append(gr)
  
avg = [0.0]*len(gr)
for i in range(len(GR)):
    for j in range(len(gr)):
        avg[j] += GR[i][j]/len(GR)
        
r = numpy.arange(0,4.0,0.01)
plt.figure()
plt.plot(r,avg,'bx-')
plt.title("g(r) for an LJ fluid")
plt.xlabel("r")
plt.ylabel("g(r)")
plt.show()
