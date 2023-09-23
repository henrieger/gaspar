from ete3 import Tree
from parsimony import standard_parsimony
from alignments import Alignment
from utils import root_tree


def main():
    min_evolution = float("inf")
    min_topologies = []

    alignment = Alignment("test_alignments/dicynodonts.txt")

    for _ in range(10000):
        tree = Tree()
        tree.populate(len(alignment.taxa), alignment.taxa.keys())
        for leaf in tree:
            for char, value in alignment.taxa[leaf.name].items():
                leaf.add_feature(char, value)

        parsimony = standard_parsimony(tree, alignment)

        if parsimony == min_evolution:
            min_topologies.append(tree.copy())

        if parsimony < min_evolution:
            min_evolution = parsimony
            min_topologies.clear()
            min_topologies.append(tree.copy())

    print("Min. numeber of steps:", min_evolution)
    print("Most parsimonious trees:", len(min_topologies))
    print("Trees:")
    for topology in min_topologies:
        root_tree(topology, alignment)
        print(topology)


if __name__ == "__main__":
    main()
