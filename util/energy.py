#!/usr/bin/env python

import matplotlib.pyplot as plt
from numpy import *
import sys

# --------- Read input and store in arrays ---------
f=open(sys.argv[1])

x=[]
E=[]

for line in f:
    cols=line.split()
    x.append( int(cols[0]) )
    E.append( float(cols[3][:-1] ) )
# end for line

npx=array(x)
npE=array(E)

# --------- Plot trace ---------
line1 = plt.plot(x,E,"r--", label="total energy", linestyle='-', color="grey")
plt.title("Energy")
plt.axhline(npE.mean(), linestyle='dashed')
plt.text(200, npE.mean()+3*npE.std(), r"$\mu="+str(npE.mean())[:8]+",\ \sigma="+str(npE.std())[:5]+"$")
plt.text(200, npE.mean()+2.5*npE.std(), r"$\mu_{max}="+str(npE.max())[:8]+",\ \mu_{min}="+str(npE.min())[:8]+"$")

plt.legend( loc='upper right', numpoints = 1 )

plt.show()



