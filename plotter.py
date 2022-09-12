#!/usr/bin/env python
# coding: utf-8

import matplotlib.pyplot as plt
import pandas as pd
import argparse


parser = argparse.ArgumentParser()
parser.add_argument('--csv')
args = parser.parse_args("--csv out_p1-2.csv".split()) #empty if run from command line

data = pd.read_csv(args.csv, header=None, sep=args.sep, names=['x', 'ux'])
data.plot(x="x", y="ux", kind="line", figsize=(5, 5), legend="")
plt.xlabel("x"); plt.ylabel("u(x)")
#plt.xlim(0,1); plt.ylim(0 , .5)
#plt.title("plot title")
plt.savefig('p1-2.png')
plt.show()

