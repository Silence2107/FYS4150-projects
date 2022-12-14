import matplotlib.pyplot as plt
import numpy as np
import sys

#Initial state
# Read data from csv file into a np array
data = np.genfromtxt('prob0.csv', delimiter=',')

# Plot the data
plt.imshow(data, cmap='hot', interpolation='nearest')

# Save the plot
plt.savefig("prob0.pdf")

# Read data from csv file into a np array
data = np.genfromtxt('prob40.csv', delimiter=',')

# Plot the data
plt.imshow(data, cmap='hot', interpolation='nearest')

# Save the plot
plt.savefig("prob40.pdf")

# Read data from csv file into a np array
data = np.genfromtxt('prob80.csv', delimiter=',')

# Plot the data
plt.imshow(data, cmap='hot', interpolation='nearest')

# Save the plot
plt.savefig("prob80.pdf")
