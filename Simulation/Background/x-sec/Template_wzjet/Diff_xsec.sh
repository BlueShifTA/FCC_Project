# Code to load promc file to get x-sec 
# written 8/12/2015 
# Surapat EK-IN

NAME='tev100_pythia8_wzjet_pt'
END='_15.promc'
PROC=("Z0" "W+-" "232")
NOPROC=("W+-" "Z0" "222")

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

cd Log_File

> X-sec_wzjet_Diff.txt

for i in `seq 1 16`
do
    FILENAME=${NAME}${pt[${i}]}'_'${pt[${i}+1]}${END}
    for j in `seq 1 3`
    do
        xcross=($(more x_sec_${FILENAME} | awk 'NR>1000' | grep \| | grep ${PROC[${j}-1]} | grep -vE "(${NOPROC[${j}-1]})"| awk '{print $(NF-2)}'))
        echo ${FILENAME}" "${PROC[${j}-1]}" "${xcross[@]} 
    done 
done
rm X-sec_wzjet_Diff.txt 
#mv X-sec_wzjet_Diff.txt ../
#cd ../
