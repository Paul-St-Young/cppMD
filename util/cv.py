#!/usr/bin/env python

import matplotlib.pyplot as plt
import argparse

parser = argparse.ArgumentParser(description='two column data')
parser.add_argument("output", help="output to analyze.")
args = parser.parse_args()

f = open(args.output,'r')

x=[]
y=[]
for line in f:
    x.append(int(line.split()[0]))
    y.append(float(line.split()[1]))
    
dt=0.01
for i in range(len(x)):
    x[i]*=dt
    
D=0.0 # diffusion constant
for i in range(len(x)):
    D += 1./3. * y[i] * dt
print D

plt.figure()
plt.plot(x,y)
plt.title("Velocity Correlation")
plt.xlabel("t")
plt.ylabel("$C_v(t)$")
plt.show()
