

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

for num in `seq 0 7`; do
    for i in `seq 2 6`
    do 
        P=$(ls -Al ${i} | grep _${num}.root | wc) 
        echo ${i} ${P}
    done 
    echo "==============${num}================="
done
