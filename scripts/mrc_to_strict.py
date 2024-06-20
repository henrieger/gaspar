from sys import argv
from math import ceil


def main():
    if len(argv) != 2:
        quit(1)

    with open(argv[1]) as f:
        intree = f.readlines()

    weight = float(intree[0].split("[")[1].split("]")[0])
    num_trees = ceil(1/weight)

    print("".join(intree[:num_trees]))


if __name__ == "__main__":
    main()
