#!/bin/bash

while getopts n:f: flag
do
    case "${flag}" in
        n) num_of_slits=${OPTARG};;
        f) filepath=${OPTARG};;
    esac
done

if [ -z "$num_of_slits" ] || [ -z "$filepath" ]
then
    echo "Please provide the number of slits (n) and the path to the outfile (f)"
    exit 1
fi

# plot the specific potential in one go
g++ many_slit_potential_unit_test.cpp -o many_slit_potential_unit_test.exe -I../include ../src/* -larmadillo -std=c++17 -O3
./many_slit_potential_unit_test.exe $num_of_slits
python3 plot_file.py $filepath
rm data.csv; rm many_slit_potential_unit_test.exe