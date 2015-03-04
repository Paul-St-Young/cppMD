#!/usr/bin/env python

import matplotlib.pyplot as plt
import sys

f=open(sys.argv[1],'r')
kMagList={}
kList=[]

for line in f:
    kMag,skString = line.split()
    skString=skString.replace("(","")
    skString=skString.replace(")","")
    sk = complex( float(skString.split(",")[0]), float(skString.split(",")[1]) )
    
    if kMag not in kMagList.keys():
      kMagList[kMag]=[sk]
      kList.append(kMag)
    else:
      kMagList[kMag].append(sk)
    
skList=[]
for l in kMagList.keys():
  skList.append(sum(kMagList[l])/len(kMagList[l]).real)
plt.plot(kList,skList,'-o')
plt.show()

