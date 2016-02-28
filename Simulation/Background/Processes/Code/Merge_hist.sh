#!/bin/bash
# Useless 


#===============================Manage Directories=======================


ls -Al | awk '{print $9}' | grep - > Direct.txt

MAXLINED=$(wc -l Direct.txt | awk '{print $1}')

for m in `seq 1 ${MAXLINED}` ; do
    
    DIRE=$(sed -n "${m}{p;q;}" Direct.txt)
    cd ${DIRE}

    hadd Bj_Bj-4p-${DIRE}_33TEV_Bj.root *

    mv Bj_Bj-4p-${DIRE}_33TEV_Bj.root ../
    cd ../
done
