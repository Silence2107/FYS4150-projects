#!/usr/bin/env python
# coding: utf-8


import matplotlib.pyplot as plt
import pandas as pd
import argparse 


parser = argparse.ArgumentParser()
parser.add_argument('--csv')
parser.add_argument('--y')
parser.add_argument('--title')
parser.add_argument('--output')
args = parser.parse_args()

data = pd.read_csv(args.csv, header=None, sep='\t', names=['x', 'ux'])

data.plot(x="x", y="ux", kind="line", figsize=(5, 5), legend="")
#data.plot(x="x", y=args.y, kind="line", figsize=(5, 5), legend=args.legend)

#plt.xlabel("x"); plt.ylabel("u(x)")
plt.xlabel("x"); plt.ylabel(args.y)
plt.title(args.title)
#plt.xlim(0,1); plt.ylim(0 , .5)
#plt.title("plot title")
#plt.show()
plt.savefig(args.output)

# In[ ]:




