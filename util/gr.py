#!/usr/bin/env python

import matplotlib.pyplot as plt
import numpy
import argparse
from pandas import DataFrame

temp_list = ['0.1','0.5','1.5','2.5','3.5']
prefix='gr'
sufix='.dat'
file_list=[]
for t in temp_list:
    file_list.append(prefix+t+sufix)
# end for t

parser = argparse.ArgumentParser(description='plot g(r)')
#parser.add_argument("gr", help="output to analyze.")
parser.add_argument('-e','--equil',type=int, help="number of equilibration steps", default=0)
args = parser.parse_args()

def get_gr(name):
    f=open(name,'r')
    GR=[]
    for line in f:
        line = line.replace('(',' ')
        line = line.replace(')',' ')
        step,gr = int(line.split()[0]), line.split()[1:]
        for i in range(len(gr)):
            gr[i]=float(gr[i])
        if step>=args.equil:
            GR.append(gr)
      
    avg = [0.0]*len(gr)
    for i in range(len(GR)):
        for j in range(len(gr)):
            avg[j] += GR[i][j]/len(GR)
    return avg
# end def get_gr

r = numpy.arange(0,4.0,0.01)
GR=[]
for i in range(len(r)):
    GR.append([])
#end for i
for fn in file_list:
    gr = get_gr(fn)
    for i in range(len(r)):
        GR[i].append(gr[i])
# end for fn

collist=[]
for t in temp_list:
    collist.append('T='+t)
#end for t
df = DataFrame(GR, index=r, columns=file_list)

plt.figure()
df.plot()
plt.show()
