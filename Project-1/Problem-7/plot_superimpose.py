
import argparse
import matplotlib.pyplot as plt
import pandas as pd


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--files", nargs="+", help="Files to superimpose")
    parser.add_argument("--labels", nargs="+",
                        help="Labels for each file. Defaults to filenames", default=None)
    parser.add_argument("--output", help="Output plot")
    parser.add_argument("--sep", help="Separator for input files. Defaults to ','", default=",")

    args = parser.parse_args()

    if args.labels is None:
        args.labels = args.files

    for i, f in enumerate(args.files):
        data = pd.read_csv(f, header=None, sep=args.sep, names=['x', 'y'])
        plt.plot(data['x'], data['y'], label=args.labels[i])
    plt.xlabel("x")
    plt.ylabel("y")
    #plt.yscale("log")
    plt.legend(title="Superimposed plots")
    plt.savefig(args.output)

if __name__ == "__main__":
    main()
