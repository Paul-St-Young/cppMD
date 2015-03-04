#!/bin/bash

export OMP_NUM_THREADS=8

for t in {0.1,0.5,1.0,2.0,3.0,4.0};do
	./cppMD $t > out$t
	mv sk.dat sk$t.dat
	mv cv.dat cv$t.dat	
	mv gr.dat gr$t.dat
	mv myTrajectory.xyz myTrajectory$t.xyz
done
