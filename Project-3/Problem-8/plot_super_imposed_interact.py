#!/usr/bin/env python
# coding: utf-8

import matplotlib.pyplot as plt
import pandas as pd



data_xy1 = pd.read_csv("particle1xy.csv", header=None,
                   sep=",", names=['x', 'y'])


data_xy2 = pd.read_csv("particle2xy.csv", header=None,
                   sep=",", names=['x', 'y'])

#Plot xy for particle 1 and 2 together
plt.plot(data_xy1['x'], data_xy1['y'], label="Particle1")
plt.plot(data_xy2['x'], data_xy2['y'], label="Particle2")
plt.xlabel("x")
plt.ylabel("y")
#plt.xlim(0,1); plt.ylim(0 , .5)
plt.title("Particle 1 and 2 movement in X-Y-plane. With interaction.")
plt.savefig('part12xy_int.pdf')
plt.show()


