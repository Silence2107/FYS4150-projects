import matplotlib.pyplot as plt
import numpy as np
import sys

#Initial state
# Read data from csv file into a np array
data = np.genfromtxt('prob50.csv', delimiter=',')

# Plot the data
plt.imshow(data, cmap='hot', interpolation='nearest')

# Save the plot
plt.savefig("prob50.pdf")

# Read data from csv file into a np array
data = np.genfromtxt('prob0.csv', delimiter=',')

# Plot the data
plt.imshow(data, cmap='hot', interpolation='nearest')

# Save the plot
plt.savefig("prob0.pdf")

# Read data from csv file into a np array
data = np.genfromtxt('prob100.csv', delimiter=',')

# Plot the data
plt.imshow(data, cmap='hot', interpolation='nearest')

# Save the plot
plt.savefig("prob100.pdf")

# Read data from csv file into a np array
data = np.genfromtxt('prob150.csv', delimiter=',')

# Plot the data
plt.imshow(data, cmap='hot', interpolation='nearest')

# Save the plot
plt.savefig("prob150.pdf")

# Read data from csv file into a np array
data = np.genfromtxt('prob200.csv', delimiter=',')

# Plot the data
plt.imshow(data, cmap='hot', interpolation='nearest')

# Save the plot
plt.savefig("prob200.pdf")

# Read data from csv file into a np array
data = np.genfromtxt('prob250.csv', delimiter=',')

# Plot the data
plt.imshow(data, cmap='hot', interpolation='nearest')

# Save the plot
plt.savefig("prob250.pdf")

# Read data from csv file into a np array
data = np.genfromtxt('prob300.csv', delimiter=',')

# Plot the data
plt.imshow(data, cmap='hot', interpolation='nearest')

# Save the plot
plt.savefig("prob300.pdf")
