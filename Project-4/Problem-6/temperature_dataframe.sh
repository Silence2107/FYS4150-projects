#!/bin/bash

# This script runs the problem6.out binary $5 times and saves the output to a file called temperature$3_data.txt
# Usage: ./temperature_dataframe.sh <binarypath> <gridsize> <T * kB/J> <number of MC iterations> <number of runs>
binarypath=$1
outputpath="temperature$3_data.txt"
touch $outputpath
echo "energyPerSite magnetizationPerSite specificHeatPerSite magneticSusceptibilityPerSite" > $outputpath
for (( i=0; i<$5; i++ ))
do
    echo "At run $i with parameters $2 $3 $4"
    ./$binarypath $2 $3 $4>> $outputpath
done