import matplotlib.pyplot as plt
import numpy as np
import sys

#Initial state
# Read data from csv file into a np array
data = np.genfromtxt('init_prob.csv', delimiter=',')

# Plot the data
plt.imshow(data, cmap='hot', interpolation='nearest')

# Save the plot
plt.savefig("init.png")

#Final state
# Read data from csv file into a np array
data = np.genfromtxt('final_prob.csv', delimiter=',')

# Plot the data
plt.imshow(data, cmap='hot', interpolation='nearest')

# Save the plot
plt.savefig("final.png")


#Potential - can't be used right now as C++ does not export it.
# Read data from csv file into a np array
#data = np.genfromtxt('potential.csv', delimiter=',')

# Plot the data
#plt.imshow(data, cmap='hot', interpolation='nearest')

# Save the plot
#plt.savefig("potential.png")

