# builds energy histogram based on data in a provided file

import pandas as pd
import matplotlib.pyplot as plt

# read data from file
data = pd.read_csv('Project-4/Problem-6/temperature2.4_data.txt', sep=' ')

# build histogram
plt.hist(data['energyPerSite'], bins=50, range=(-1.32, -1.12))

# set labels
plt.xlabel('Energy')
plt.ylabel('Frequency')

# save figure
plt.savefig('Project-4/Problem-6/energy_histogram.png')