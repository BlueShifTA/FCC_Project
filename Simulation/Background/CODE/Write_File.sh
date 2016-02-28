#!/bin/bash
#==========================================================
# Index for running through HTbin
pt[1]=50
pt[2]=100
pt[3]=200
pt[4]=400
pt[5]=600
pt[6]=800
pt[7]=1000
pt[8]=1500
pt[9]=2000
pt[10]=2500
pt[11]=3000
pt[12]=4000
pt[13]=5000
pt[14]=10000
pt[15]=15000
pt[16]=20000
pt[17]=25000


#==========================================================

for i in `seq 1 16`
do
       echo "./Run_Processes_bash.sh wzjet ${pt[${i}]} ${pt[${i}+1]}" >> Run_many_wzjet.sh
done

chmod a+x Run_many_wzjet.sh
