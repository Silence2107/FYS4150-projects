#!/usr/bin/env python
# coding: utf-8

import matplotlib.pyplot as plt
import pandas as pd
import argparse


parser = argparse.ArgumentParser()
parser.add_argument(
    '--csv', '--csv')

data = pd.read_csv(parser.parse_args().csv, header=None,
                   sep=",", names=['x', 'y'])

data1 = pd.read_csv(parser.parse_args().csv, header=None,
                   sep=",", names=['x1', 'y1'])

#alter the font size
plt.rcParams.update({'font.size': 20})

data.plot(x="x", y="y", kind="line", figsize=(9, 6), legend="N = 40")
data1.plot(x="x1", y="y1", kind="line", figsize=(9, 6), legend="N = 60")

plt.xlabel("T")
plt.ylabel("Quantity")
#plt.xlim(0,1); plt.ylim(0 , .5)
#plt.title("plot title")
plt.savefig('40.pdf')

#data = pd.read_csv("particle2.csv", header=None, sep=",", names=['x', 'y'])
#data.plot(x="x", y="y", kind="line", figsize=(5, 5), legend="")
#plt.xlabel("x"); plt.ylabel("u(x)")
##plt.xlim(0,1); plt.ylim(0 , .5)
##plt.title("plot title")
# plt.savefig('part2.pdf')

plt.show()
