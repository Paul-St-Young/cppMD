#!/usr/bin/env python

import matplotlib.pyplot as plt
from numpy import *
from scipy import stats
import sys

import argparse

parser = argparse.ArgumentParser(description='Process MD output')
parser.add_argument("output", help="output to analyze.")
parser.add_argument("-c","--column", type=str, choices=['U','K','T','E'],
                   help='column label',default='E')
args = parser.parse_args()

column_map = {'U':1,'K':2,'T':3,'E':4} 
column_name = {'U':"Potential Energy", 'K':"Kinetic Energy", 'T':"Temperature", 'E':"Total Energy"}

# --------- Read input and store in arrays ---------
f=open(args.output)

x=[]
E=[]

for line in f:
    cols=line.split()
    cols[1] = cols[1].replace("(","")
    cols[-1] = cols[-1].replace(")","")
    x.append( int(cols[0]) )
    E.append( float(cols[ column_map[args.column] ]) )
# end for line

npx=array(x)
npE=array(E)
print "E=",npE.mean(),"+-",stats.sem(npE)

# --------- Plot trace ---------
line1 = plt.plot(x,E,"r--", label="total energy", linestyle='-', color="black")
plt.title(column_name[args.column])
plt.ylabel(args.column)
plt.xlabel("t")
plt.axhline(npE.mean(), linestyle='dashed')

#plt.text(200, npE.mean()+3*npE.std(), r"$\mu="+str(npE.mean())[:8]+",\ \sigma="+str(npE.std())[:5]+"$")
#plt.text(200, npE.mean()+2.5*npE.std(), r"$\mu_{max}="+str(npE.max())[:8]+",\ \mu_{min}="+str(npE.min())[:8]+"$")
#plt.legend( loc='upper right', numpoints = 1 )

plt.show()



