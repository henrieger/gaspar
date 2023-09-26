from ete3 import Tree, TreeNode
from itertools import combinations


def generate_all(taxons: set) -> list:
    if len(taxons) < 4:
        return

    if len(taxons) == 4:
        taxon_pairs = [f"({c[0]},{c[1]})" for c in combinations(taxons, 2)]

        first_half = taxon_pairs[:3]
        second_half = taxon_pairs[3:]
        second_half.reverse()

        newick_trees = []
        for i in range(3):
            newick_trees.append(f"({first_half[i]},{second_half[i]});")

        return [Tree(n) for n in newick_trees]

    new_trees = []
    for taxon in taxons:
        new_node = TreeNode(name=taxon)
        curr_trees = generate_all(taxons - set([taxon]))
        for tree in curr_trees:
            for node in tree.iter_descendants():
                parent = node.up
                node.detach()
                substitute = parent.add_child()
                substitute.add_child(node)
                substitute.add_child(new_node)
                new_trees.append(tree.copy())
                node.detach()
                new_node.detach()
                substitute.delete()
                parent.add_child(node)

    return new_trees


if __name__ == "__main__":
    trees = generate_all(set(range(5)))
    print(len(trees))
    for tree in trees:
        print(tree)
