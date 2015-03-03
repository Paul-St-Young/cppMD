#!/usr/bin/env python

import matplotlib.pyplot as plt
import sys

f=open(sys.argv[1],'r')
kMagList=[]
skList=[]

for line in f:
    kMag,skString = line.split()
    
    kMagList.append(float(kMag))
    
    skString=skString.replace("(","")
    skString=skString.replace(")","")
    sk = complex( float(skString.split(",")[0]), float(skString.split(",")[1]) )
    skList.append(sk)

plt.plot(kMagList,skList,'+')
plt.show()
