#!/bin/bash

touch output-rand-T2-e.csv output-rand-T2-m.csv;

L=20;
temp_arr=(1.0 2.4);

for t in $(seq 1 ${#temp_arr[@]}); do

        temp=${temp_arr[t-1]}; 

        for i in $(seq 1 8); do

                #n number of MC cycles
                n=$(echo 10^$i| bc -l);

                echo -ne "\r\033[0K Executing programme: $L x $L lattice, T=$t J/kB, ${n} MC cycles" 

                #execute programme and send console output to file
                ./p4-5a_rand.exe $L $temp $n >> ${n}-output.csv

                #print energy and magnetization to respective output files
                energy=$(awk '/All states Average energy/{ print $NF }' ${n}-output.csv);
                magn=$(awk '/All states Average magnetization/{ print $NF }' ${n}-output.csv);

                echo $n","$energy >> output-rand-T${t}-e.csv
                echo $n","$magn >> output-rand-T${t}-m.csv

                rm ${n}-output.csv;
        done
done

