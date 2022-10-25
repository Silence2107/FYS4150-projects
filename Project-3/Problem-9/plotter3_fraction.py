#!/usr/bin/env python
# coding: utf-8

import matplotlib.pyplot as plt
import pandas as pd
import argparse


parser = argparse.ArgumentParser()
parser.add_argument(
    '--csv', help='Input csv file. Defaults to particle1.csv', default='particle1.csv')

data = pd.read_csv(parser.parse_args().csv, header=None,
                   sep=",", names=['x', 'y'])
data.plot(x="x", y="y", kind="line", figsize=(5, 5), legend="")
plt.xlabel("angular frequency")
plt.ylabel("fraction of particles")
#plt.xlim(0,1); plt.ylim(0 , .5)
#plt.title("plot title")
plt.savefig('random_ca_fraction.pdf')

#data = pd.read_csv("particle2.csv", header=None, sep=",", names=['x', 'y'])
#data.plot(x="x", y="y", kind="line", figsize=(5, 5), legend="")
#plt.xlabel("x"); plt.ylabel("u(x)")
##plt.xlim(0,1); plt.ylim(0 , .5)
##plt.title("plot title")
# plt.savefig('part2.pdf')

plt.show()
