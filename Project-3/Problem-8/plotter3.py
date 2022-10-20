#!/usr/bin/env python
# coding: utf-8

import matplotlib.pyplot as plt
import pandas as pd
import argparse


parser = argparse.ArgumentParser()
parser.add_argument('--csv')
args = parser.parse_args("--csv euler.csv".split()) #empty if run from command line

data = pd.read_csv("particle1.csv", header=None, sep=",", names=['x', 'y'])
data.plot(x="x", y="y", kind="line", figsize=(5, 5), legend="")
plt.xlabel("x"); plt.ylabel("y")
#plt.xlim(0,1); plt.ylim(0 , .5)
#plt.title("plot title")
plt.savefig('part1.pdf')

#data = pd.read_csv("particle2.csv", header=None, sep=",", names=['x', 'y'])
#data.plot(x="x", y="y", kind="line", figsize=(5, 5), legend="")
#plt.xlabel("x"); plt.ylabel("u(x)")
##plt.xlim(0,1); plt.ylim(0 , .5)
##plt.title("plot title")
#plt.savefig('part2.pdf')

plt.show()



