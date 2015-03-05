#!/usr/bin/env python

from pandas import DataFrame, Series,date_range
from numpy.random import randn
import matplotlib.pyplot as plt
import sys

def get_sklist(filename):
    f=open(filename,'r')
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
    f.close()

    skList=[]
    for l in sorted( kMagList.keys() ):
      skList.append(sum(kMagList[l]).real/len(kMagList[l]))
    return [kList,skList]
# end def get_sklist
    
file_list = ["sk0.5.dat","sk1.0.dat","sk2.0.dat","sk3.0.dat"]

kList,skList = get_sklist(file_list[0])
SKLIST=[]
for i in range(len(kList)):
    SKLIST.append([])
#end for i
for fn in file_list:
    kList,skList = get_sklist(fn)
    for i in range(len(skList)):
        SKLIST[i].append(skList[i])
# end for fn

df = DataFrame(SKLIST, index=kList, columns=file_list)

plt.figure()
df.plot()
plt.show()


'''
ts = Series(randn(1000), index=date_range('1/1/2000', periods=1000))
df = DataFrame(randn(1000, 4), index=ts.index, columns=list('ABCD'))
df = df.cumsum()
plt.figure(); df.plot(); plt.legend(loc='best')
'''
