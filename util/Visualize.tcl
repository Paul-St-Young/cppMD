mol delete all
display resetview
mol load xyz "myTrajectory.xyz"
set molid [molinfo top]

mol active $molid
mol delrep 0 $molid
mol representation VDW 0.1 12.0
mol addrep $molid

animate read "storeMe.xyz" 0 3000 0 $molid

scale by 0.5
set sel [atomselect $molid all]
sel set radius 0.1
