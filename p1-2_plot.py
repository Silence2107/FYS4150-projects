#!/usr/bin/env python
# coding: utf-8

# In[2]:


import matplotlib.pyplot as plt
import pandas as pd


# In[36]:


data = pd.read_csv("output.csv", header=None, sep='\t', names=['x', 'ux'])
data.plot(x="x", y="ux", kind="line", figsize=(5, 5), legend="", xicks)
plt.xlabel("x"); plt.ylabel("u(x)")
#plt.xlim(0,1); plt.ylim(0 , .5)
#plt.title("plot title")
plt.show()


# In[ ]:




