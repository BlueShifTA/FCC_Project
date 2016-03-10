#!/bin/bash
#==========================================================
# Index for running through HTbin
#pt[1]=50
#pt[2]=100
#pt[3]=200
#pt[4]=400
#pt[5]=600
#pt[6]=800
#pt[7]=1000
#pt[8]=1500
#pt[9]=2000
#pt[10]=2500
#pt[11]=3000
#pt[12]=4000
#pt[13]=5000
#pt[14]=10000
#pt[15]=15000
#pt[16]=20000
#pt[17]=25000


#==========================================================
echo "SCRATCH_SRC=/home/orion/Project/ParticlePhysics/FCC/Simulation/Signal/ADD/Processes">> Run_many_ADD.sh
echo "DATA=/home/orion/Project/ParticlePhysics/FCC/Simulation/Data/FCC_Project/Signal/ADD">> Run_many_ADD.sh


for i in `seq 2 6`
do
    for k in `seq 1 10`
    do
        for j in `seq 10000 1000 20000`
        do
            echo "./Run_Processes_bash.sh ${i} ${j} 10000 ${k} " >> Run_many_ADD.sh
            if ((${j}%4000 == 0 ))
            then
                echo "echo "Waiting ...................................... "" >> Run_many_ADD.sh
                echo "sleep 2h" >> Run_many_ADD.sh
                echo "mv \${SCRATCH_SRC}/Sum_GEN/* \${DATA}/GEN/">> Run_many_ADD.sh
                echo "mv \${SCRATCH_SRC}/Sum_FAST/* \${DATA}/FAST/">> Run_many_ADD.sh
#                echo "echo "Press ENTER 3 times to continue"">> Run_many_ADD.sh
#                echo "read" >> Run_many_ADD.sh
#                echo "read" >> Run_many_ADD.sh
#                echo "read">> Run_many_ADD.sh
            fi
        done
    done
done

chmod a+x Run_many_ADD.sh
