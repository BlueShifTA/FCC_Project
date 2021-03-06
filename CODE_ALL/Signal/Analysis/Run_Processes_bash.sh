#!/bin/bash

sed s/INPUT1/${1}/g FCC_temp_bash.job > temp
mv temp FCC_${1}_${2}_${3}_${4}_${5}_${6}_bash.job

sed s/INPUT2/${2}/g FCC_${1}_${2}_${3}_${4}_${5}_${6}_bash.job > temp
mv temp FCC_${1}_${2}_${3}_${4}_${5}_${6}_bash.job

sed s/INPUT3/${3}/g FCC_${1}_${2}_${3}_${4}_${5}_${6}_bash.job > temp
mv temp FCC_${1}_${2}_${3}_${4}_${5}_${6}_bash.job

sed s/INPUT4/${4}/g FCC_${1}_${2}_${3}_${4}_${5}_${6}_bash.job > temp
mv temp FCC_${1}_${2}_${3}_${4}_${5}_${6}_bash.job

sed s/INPUT5/${5}/g FCC_${1}_${2}_${3}_${4}_${5}_${6}_bash.job > temp
mv temp FCC_${1}_${2}_${3}_${4}_${5}_${6}_bash.job

sed s/INPUT6/${6}/g FCC_${1}_${2}_${3}_${4}_${5}_${6}_bash.job > temp
mv temp FCC_${1}_${2}_${3}_${4}_${5}_${6}_bash.job


chmod a+x FCC_${1}_${2}_${3}_${4}_${5}_${6}_bash.job

## Send job
./FCC_${1}_${2}_${3}_${4}_${5}_${6}_bash.job > Log_FCC_${1}_${2}_${3}_${4}_${5}_${6}_bash.log

#bsub -R "rusage[mem=1000]" -q 1nd -o Log_${1}_${2}_${3}_${4}_${5}_${6}_ FCC_${1}_${2}_${3}_${4}_${5}_${6}__bash.job
