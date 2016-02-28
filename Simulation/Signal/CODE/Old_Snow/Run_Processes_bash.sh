#!/bin/bash


sed s/INPUT1/${1}/g signal_temp_bash.job > temp
mv temp signal_${1}_${2}_${3}_bash.job

sed s/INPUT2/${2}/g signal_${1}_${2}_${3}_bash.job > temp
mv temp signal_${1}_${2}_${3}_bash.job

sed s/INPUT3/${3}/g signal_${1}_${2}_${3}_bash.job > temp
mv temp signal_${1}_${2}_${3}_bash.job

chmod a+x signal_${1}_${2}_${3}_bash.job

## Send job
./signal_${1}_${2}_${3}_bash.job #> signal_${1}_${2}_${3}.log

#bsub  -q 1nw -o Log_signal_${1}_${2}_${3} signal_${1}_${2}_${3}_bash.job
