from ete3 import Tree
from progressbar import ProgressBar
from parsimony import standard_parsimony
from alignments import Alignment
from gen import generate_all, tuples_to_newick
from utils import root_tree, max_trees


def main(alignment_file: str):
    min_evolution = float("inf")
    min_topologies = []

    alignment = Alignment(alignment_file)

    taxa_names = set(alignment.taxa.keys())
    bar = ProgressBar(max_value=max_trees(len(taxa_names)))
    for i, t in enumerate(generate_all(taxa_names)):
        tree = Tree(tuples_to_newick(t))
        root_tree(tree, alignment)

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

        bar.update(i+1)

    print("Min. number of steps:", min_evolution)
    print("Most parsimonious trees:", len(min_topologies))
    print("Trees:")
    for topology in min_topologies:
        root_tree(topology, alignment)
        topology.ladderize()
        print(topology)


if __name__ == "__main__":
    from sys import argv
    main(argv[1])
