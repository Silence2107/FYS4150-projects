#!/usr/bin/env python
# coding: utf-8

import matplotlib.pyplot as plt
import pandas as pd

data_z1 = pd.read_csv("particle1z.csv", header=None,
                   sep=",", names=['t', 'z'])
data_z1.plot(x="t", y="z", kind="line", figsize=(5, 5), legend="")
plt.xlabel("t")
plt.ylabel("z")
#plt.xlim(0,1); plt.ylim(0 , .5)
plt.title("Particle 1 movement along Z over time.")
plt.savefig('part1z.pdf')
#plt.show()

data_xy1 = pd.read_csv("particle1xy.csv", header=None,
                   sep=",", names=['x', 'y'])
data_xy1.plot(x="x", y="y", kind="line", figsize=(5, 5), legend="")
plt.xlabel("x")
plt.ylabel("y")
#plt.xlim(0,1); plt.ylim(0 , .5)
plt.title("Particle 1 movement in X-Y-plane")
plt.savefig('part1xy.pdf')
#plt.show()

data_xy2 = pd.read_csv("particle2xy.csv", header=None,
                   sep=",", names=['x', 'y'])
data_xy2.plot(x="x", y="y", kind="line", figsize=(5, 5), legend="")
plt.xlabel("x")
plt.ylabel("y")
#plt.xlim(0,1); plt.ylim(0 , .5)
plt.title("Particle 2 movement in X-Y-plane")
plt.savefig('part2xy.pdf')
#plt.show()

#3D plot for particle 1
fig3d = plt.figure().add_subplot(projection='3d')
data_xyz1 = pd.read_csv("particle1xyz.csv", header=None,
                   sep=",", names=['x', 'y', 'z'])
x1_column = data_xyz1.iloc[: , 0]
y1_column = data_xyz1.iloc[: , 1]
z1_column = data_xyz1.iloc[: , 2]
fig3d.plot(x1_column, y1_column, z1_column, label='parametric curve')
fig3d.set_xlabel("x")
fig3d.set_ylabel("y")
fig3d.set_zlabel("z")
#plt.xlim(0,1); plt.ylim(0 , .5)
plt.title("Particle 1 movement in X-Y-Z-space.")
plt.savefig('part1xyz.pdf')
#plt.show()

#Plot xy for particle 1 and 2 together
#data_xy1.plot(x="x", y="y", kind="line", figsize=(5, 5), legend="", label="particle 1")
#data_xy2.plot(x="x", y="y", kind="line", figsize=(5, 5), legend="", label="particle 2")
data_xy1.plot(x="x", y="y", kind="line", figsize=(5, 5), legend="", label="particle 1")
data_xy2.plot(x="x", y="y", kind="line", figsize=(5, 5), legend="", label="particle 2")

plt.xlabel("x")
plt.ylabel("y")
#plt.xlim(0,1); plt.ylim(0 , .5)
plt.title("Particle 1 and 2 movement in X-Y-plane, no interaction.")
plt.savefig('part12xy.pdf')
plt.show()
