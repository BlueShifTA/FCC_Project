#!/bin/bash

FILENAME=Run_many_pythia.sh

i=1
j=1
for i in `seq 2 7`
do
     for j in `seq 2000 1000 15000`
     do
       MAXEVENT=1000
       echo "./Run_Processes_bash.sh $i $j ${MAXEVENT}" >> ${FILENAME}
     done
done

chmod a+x ${FILENAME}
