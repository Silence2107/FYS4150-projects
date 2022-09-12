#!/usr/bin/env python
# coding: utf-8


import matplotlib.pyplot as plt
import pandas as pd
import argparse 

#Reusing plot script from problem 2, but with some adaptions to customize labels and title.
parser = argparse.ArgumentParser()
parser.add_argument('--csv')
parser.add_argument('--y')
parser.add_argument('--title')
parser.add_argument('--output')
args = parser.parse_args()

data = pd.read_csv(args.csv, header=None, sep='\t', names=['x', 'ux'])

data.plot(x="x", y="ux", kind="line", figsize=(5, 5), legend="")

plt.xlabel("x"); plt.ylabel(args.y)
plt.title(args.title)

plt.savefig(args.output)




