
import matplotlib.pyplot as plt
import numpy as np
import sys

#PLOT VISUALS
plt.figure(figsize=(5, 5))
plt.rcParams.update({'font.size': 12})
plt.xlabel('x'); plt.ylabel('y');

# Read data from csv file into a np array
data = np.genfromtxt('data.csv', delimiter=',')

# Plot the data
plt.imshow(data, cmap='hot', interpolation='nearest')

# Save the plot
plt.savefig(sys.argv[1])
