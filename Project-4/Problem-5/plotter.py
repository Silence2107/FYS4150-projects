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
    parser.add_argument("--lstyle", nargs="+", help="Linestyle. Default to solid line'", default="-")
    parser.add_argument("--lcolor", nargs="+", help="Linestyle. Default to blue line'", default="b")

    args = parser.parse_args()

    if args.labels is None:
        args.labels = args.files

    for i, f in enumerate(args.files):
        data = pd.read_csv(f, header=None, sep=args.sep, names=['x', 'y'])
        plt.plot(data['x'], data['y'],color=args.lcolor[i],label=args.labels[i],linestyle=args.lstyle[i])
    
    plt.xscale("log")
    plt.xlabel("n MC cycles")
    plt.ylabel(r"$\langle \varepsilon \rangle (J)$")
    plt.legend()
    plt.savefig(args.output)

if __name__ == "__main__":
    main()
