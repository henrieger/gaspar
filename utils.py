from ete3 import Tree
from alignments import Alignment


def tuples_to_newick(tree) -> str:
    return str(tree).replace("'", "") + ";"


def max_trees(n: int):
    base = 2 * n - 5
    mult = 1
    for i in range(base, 1, -2):
        mult *= i

    return mult


def get_unique_leaf_by_name(tree: Tree, name: str):
    return tree.get_leaves_by_name(name)[0]


def root_tree(tree: Tree, alignment: Alignment):
    if len(alignment.outgroup_taxa) == 0:
        return

    first = get_unique_leaf_by_name(tree, alignment.outgroup_taxa[0])
    if len(alignment.outgroup_taxa) < 2:
        tree.set_outgroup(first)
        return

    rest = (get_unique_leaf_by_name(tree, t) for t in alignment.outgroup_taxa[1:])

    common_ancestor = first.get_common_ancestor(*rest)
    if common_ancestor != tree:
        tree.set_outgroup(common_ancestor)
