from ete3 import Tree, TreeNode
from Levenshtein import distance as levenshtein_distance


def distance(n: TreeNode, m: TreeNode):
    return levenshtein_distance(
        n.get_ascii(attributes=["seq"]), m.get_ascii(attributes=["seq"])
    )


def tree_parsimony(tree: Tree):
    for node in tree.traverse("postorder"):
        if node.is_leaf():
            node.dist = 0
        else:
            node.dist = distance(node.children[0], node.children[1])


def main():
    min_evolution = float("inf")
    min_topology = None

    with open("apes.txt") as f:
        taxa = f.readlines()
    taxa = [t.split() for t in taxa]
    taxa = {t[0].strip(): t[1].strip() for t in taxa}

    for _ in range(100):
        tree = Tree()
        tree.populate(len(taxa), taxa.keys())
        for leaf in tree:
            leaf.add_feature("seq", taxa[leaf.name])

        tree_parsimony(tree)

        if tree.dist < min_evolution:
            min_evolution = tree.dist
            min_topology = tree.copy()

    min_topology.set_outgroup(
        min_topology.search_nodes(name="orangutan")[0]
    )
    print(min_evolution)
    print(min_topology)


if __name__ == "__main__":
    main()
