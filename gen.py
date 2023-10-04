from ete3 import Tree


def tuples_to_newick(tree) -> str:
    return str(tree) + ";"


def insert_taxon(taxon, tree):
    if len(tree) != 3:
        raise Exception('a valid unrooted tree must have exactly 3 branches')

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


def generate_all(taxa: set):
    if len(taxa) < 3:
        raise Exception('taxon set must have at least 3 taxa')

    if len(taxa) == 3:
        yield tuple(taxa)
    else:
        taxon = taxa.pop()
        for tree in generate_all(taxa):
            yield from insert_taxon(taxon, tree)


if __name__ == "__main__":
    from sys import argv

    trees = list(generate_all(set(range(int(argv[1])))))
    print(len(trees))
    for tree in trees:
        newick = tuples_to_newick(tree)
        tree_structure = Tree(newick)
        tree_structure.set_outgroup('0')
        print(tree_structure)
