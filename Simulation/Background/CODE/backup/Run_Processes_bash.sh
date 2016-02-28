#!/bin/bash

sed s/INPUT1/${1}/g FCC_temp_bash.job > temp
mv temp FCC_${1}_${2}_${3}_bash.job

sed s/INPUT2/${2}/g FCC_${1}_${2}_${3}_bash.job > temp
mv temp FCC_${1}_${2}_${3}_bash.job

sed s/INPUT3/${3}/g FCC_${1}_${2}_${3}_bash.job > temp
mv temp FCC_${1}_${2}_${3}_bash.job


chmod a+x FCC_${1}_${2}_${3}_bash.job

## Send job
./FCC_${1}_${2}_${3}_bash.job 

#bsub -R "rusage[mem=1000]" -q 1nd -o Log_${1}_${2}_${3}_ FCC_${1}_${2}_${3}__bash.job
