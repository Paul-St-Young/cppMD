#!/usr/bin/env python

import numpy as np

def equal(v1,v2):
    for i in range(len(v1)):
        if v1[i]!=v2[i]:
            return False
        # end if
    # end for
    return True
# end def equal
            

import argparse
if __name__=="__main__":

    parser = argparse.ArgumentParser(description='Estimate the number of steps it takes to go from one site to another')
    parser.add_argument('traj',type=str,help='file containing vacancy trajectory')
    args = parser.parse_args()
    
    data = np.loadtxt(args.traj)
    oldPos = data[0]
    avgstep = 0
    mystep = 0
    nmove = 0
    for i in range(len(data)):
        if equal( data[i], oldPos):
            mystep += 1
        else:
            nmove +=1
            avgstep += mystep
        # end if
    # end for i
    avgstep /= float(nmove)
    print avgstep
    
# end __main__
