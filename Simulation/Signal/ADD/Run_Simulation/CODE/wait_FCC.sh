#!/bin/bash
# Script to wait until previous PIDs finish.

PID=$(ps | grep FCC | awk '{print $1}' | head -n 1)

#PID="1"

while [ ${PID} -gt 0 ] 
do
    echo 'Still Running'
    sleep 10
    PID=$(ps | grep FCC | awk '{print $1}' | head -n 1)
    echo ${PID}
done 

echo 'Out of Loop'
