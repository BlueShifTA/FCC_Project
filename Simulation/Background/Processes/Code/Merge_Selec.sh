#!/bin/bash
#Useless

#===============================Manage Directories=======================

mkdir 0-400
mkdir 400-1000
mkdir 1000-1800
mkdir 1800-3000
mkdir 3000-4600
mkdir 4600-6600
mkdir 6600-100000
mv *0-400*log 0-400/
mv *400-1000*log 400-1000/
mv *1000-1800*log 1000-1800/
mv *1800-3000*log 1800-3000/
mv *3000-4600*log 3000-4600/
mv *4600-6600*log 4600-6600/
mv *6600-100000*log 6600-100000/

ls -Al | awk '{print $9}' | grep - > Direct.txt

MAXLINED=$(wc -l Direct.txt | awk '{print $1}')

for m in `seq 1 ${MAXLINED}` ; do
    
    DIRE=$(sed -n "${m}{p;q;}" Direct.txt)
    cd ${DIRE}

    #=============================Declear Array========================================
    
    declare -a SelecCut
    
    for a in `seq 0 15` ; do
       SelecCut[$a]=0
    done
    
    #============================Summation Part========================================
    
    

    ls -Al | grep log | awk '{print $9}' > Data.txt
    
    MAXLINE=$(wc -l Data.txt | awk '{print $1}')
    
    for i in `seq 1 ${MAXLINE}` 
    do
      File=$(sed -n "${i}{p;q;}" Data.txt)
        for j in `seq 0 15`
        do 
           VAL=$(more $File | grep Cut" "${j} | awk '{print $5}')
           let SelecCut\[$j]+=$VAL
    #       echo ${SelecCut[$j]} 
        done
    done
    
    
    for a in `seq 0 15` ; do
       echo "Selection Cut ${a} :  ${SelecCut[$a]}" >> Result_${DIRE}.txt
    done
    mv Result_${DIRE}.txt ../
    cd ../
done

