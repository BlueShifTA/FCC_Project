# Code to Add hstogram and move
# written 8/12/2015 
# Surapat EK-IN
# 1 = Process
    
cd ${1}
DIRIN=$(ls -Al | grep orion | awk '{print $9}' | sort -n)


for dir in ${DIRIN[@]}
do 
    cd ${dir}
    for ind in `seq 0 7`
    do 
        #=============================Add Histograms=======================================
        hadd  tev100_${1}_${dir}_result_${ind}.root *${ind}.root 
        mv tev100_${1}_${dir}_result_${ind}.root ../../../Results/${1}/${ind} 
        
        #=============================Declear Array========================================
        declare -a SelecCut
        
        for a in `seq 0 16` ; do
           SelecCut[$a]=0
        done
        #============================Summation Part========================================
        ALLFILE=$(ls -Al | grep ${ind}.txt | awk '{print $9}')
        
        for i in ${ALLFILE[@]} 
        do
            for j in `seq 0 16`
            do 
               VAL=$(more ${i} | grep Cut" "${j} | awk '{print $5}')
               let SelecCut\[$j]+=$VAL
               #echo ${SelecCut[$j]} 
            done
        done
        
        for a in `seq 0 16` ; do
           echo "Selection Cut ${a} :  ${SelecCut[$a]}" >> Result_${1}_${dir}_${ind}.txt
        done
        mv Result_${1}_${dir}_${ind}.txt ../../../Results/${1}/${ind}
    done 
    cd ../
done 

