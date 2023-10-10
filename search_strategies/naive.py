from search_strategies.base import SearchStrategy
from evaluators.base import Evaluator
from utils import tuples_to_newick, max_trees, root_tree
from alignments import Alignment
from ete3 import Tree
from progressbar import ProgressBar


class NaiveSearch(SearchStrategy):
    def insert_taxon(self, taxon, tree):
        if len(tree) != 3:
            raise Exception("a valid unrooted tree must have at least 3 branches")

        def insert_recursive(taxon, tree):
            yield (taxon, tree)
            if type(tree) == tuple and len(tree) == 2:
                for subtree in insert_recursive(taxon, tree[0]):
                    yield (subtree, tree[1])
                for subtree in insert_recursive(taxon, tree[1]):
                    yield (tree[0], subtree)

        for subtree in insert_recursive(taxon, tree[0]):
            yield (subtree, tree[1], tree[2])
        for subtree in insert_recursive(taxon, tree[1]):
            yield (tree[0], subtree, tree[2])
        for subtree in insert_recursive(taxon, tree[2]):
            yield (tree[0], tree[1], subtree)

    def generate_next(self, taxa: set):
        if len(taxa) < 3:
            raise Exception("taxon set must have at least 3 taxa")

        if len(taxa) == 3:
            yield tuple(taxa)
        else:
            taxon = taxa.pop()
            for tree in self.generate_next(taxa):
                yield from self.insert_taxon(taxon, tree)

    def search(self):
        max_score = float("-inf")
        max_topologies = []

        taxa_names = set(self.alignment.taxa.keys())
        bar = ProgressBar(max_value=max_trees(len(taxa_names)))
        for i, t in enumerate(self.generate_next(taxa_names)):
            tree = Tree(tuples_to_newick(t))
            root_tree(tree, self.alignment)

            for leaf in tree:
                for char, value in self.alignment.taxa[leaf.name].items():
                    leaf.add_feature(char, value)

            score = self.evaluator.evaluate(tree, self.alignment)

            if score == max_score:
                max_topologies.append(tree.copy())

            if score > max_score:
                max_score = score
                max_topologies.clear()
                max_topologies.append(tree.copy())

            bar.update(i + 1)

        print()
        print("Max score:", max_score)
        print("# Trees:", len(max_topologies))
        print("Trees:")
        for topology in max_topologies:
            topology.ladderize()
            print(topology)
