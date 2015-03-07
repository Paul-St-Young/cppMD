#!/usr/bin/env python

from pandas import DataFrame, Series,date_range
from numpy.random import randn
import matplotlib.pyplot as plt
import argparse

temp_list = ['']
prefix='sk'
sufix='.dat'
file_list=[]
for t in temp_list:
    file_list.append(prefix+t+sufix)
# end for t

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
    return [kList[1:],skList[1:]]
# end def get_sklist

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Plot a list of structure factors')
    parser.add_argument('-e','--equil',type=int,default=0,help="number of equilibration steps")
    args = parser.parse_args()

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
    collist=[]
    for t in temp_list:
        collist.append('T='+t)
    #end for t
    df = DataFrame(SKLIST, index=kList, columns=collist)

    plt.figure()
    df.plot(style=['-s','-o','-^','-v','-x'])
    plt.title("Structure factor")
    plt.xlabel(r"$\vert \vec{k} \vert$")
    plt.ylabel("S(k)")
    plt.show()

# end __main__
