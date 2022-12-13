
import pandas as pd
import matplotlib.pyplot as plt
import argparse

# Create the parser
parser = argparse.ArgumentParser(description='Plots the probability of t')
parser.add_argument('--file', type=str, help='The file to read the data from')

args = parser.parse_args()

# Read the data from a file
df = pd.read_csv(args.file, sep=',', header=None, names=['t', 'prob'])

# Plot the data
df.plot(x='t', y='prob', kind='line', legend=False)
plt.xlabel('t, rel.u.')
plt.ylabel('Tot. probability')

# Save the plot
plt.savefig('prob_of_t.pdf')