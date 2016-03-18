#!/bin/bash

sed s/INPUT1/${1}/g FCC_temp_bash.job > temp
mv temp FCC_${1}_${2}_bash.job

sed s/INPUT2/${2}/g FCC_${1}_${2}_bash.job > temp
mv temp FCC_${1}_${2}_bash.job

chmod a+x FCC_${1}_${2}_bash.job

## Send job
#./FCC_${1}_${2}_bash.job > Log_FCC_${1}_${2}_bash.log

qsub -o /mypath/output.txt -e /mypath/error.txt FCC_${1}_${2}_bash.job
