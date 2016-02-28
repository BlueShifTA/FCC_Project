# Code to load promc file to get x-sec 
# written 8/12/2015 
# Surapat EK-IN

HREF_B='http://faxbox.usatlas.org/group/hepsim/events/pp/100tev/ttbar_pythia8_ptbins/'
NAME='tev100_pythia8_ttbar_pt'
END='_15.promc'

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

> X-sec_ttbar.txt

for i in `seq 1 17`
do 
    FILENAME=${NAME}${pt[${i}]}'_'${pt[${i}+1]}${END}
    HREF=${HREF_B}${FILENAME}
    #echo ${HREF}
    wget ${HREF}
    unzip -p ${FILENAME} logfile.txt > x_sec_${FILENAME}
    more x_sec_${FILENAME} | grep section | sed s:=:" ":g | awk '{print "'${pt[${i}]}'""_""'${pt[${i}+1]}'" " Cross Section : "$3" "$4" "$5" "$6}' >> X-sec_ttbar.txt 
    mv ${FILENAME} ProMC_File
    mv x_sec_${FILENAME} Log_File
done 

