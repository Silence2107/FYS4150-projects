
import pandas as pd
import matplotlib.pyplot as plt
import argparse

# Create the parser
parser = argparse.ArgumentParser(description='Plots the probability of y')
parser.add_argument('--file', type=str, help='The file to read the data from')

args = parser.parse_args()

# Read the data from a file
df = pd.read_csv(args.file, sep=',', header=None, names=['y', 'prob'])

# Plot the data
df.plot(x='y', y='prob', kind='line', legend=False)
plt.xlabel('y, rel.u.')
plt.ylabel('Prob. density integrated over x')

# Save the plot
plt.savefig('prob_of_y.pdf')