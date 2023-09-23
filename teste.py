from ete3 import Tree, TreeNode


def standard_parsimony(tree: Tree, character_names: list, outgroup: set) -> int:
    parsimony = 0
    for character in character_names:
        for node in tree.traverse("postorder"):
            if not node.is_leaf():
                char_value = ""
                children = [set(child.__dict__[character]) for child in node.children]
                intersection = set.intersection(*children)
                if not intersection:
                    char_value = set.union(*children)
                    if node.name not in outgroup:
                        parsimony += 1
                else:
                    char_value = intersection
                node.add_feature(character, char_value)

    return parsimony


def main():
    min_evolution = float("inf")
    min_topologies = []

    with open("dicynodonts.txt") as f:
        taxa = f.readlines()
    taxa = [t.split() for t in taxa]
    taxa = {t[0].strip(): t[1].strip() for t in taxa}

    outgroup = ["Dicynodon", "Lystrosaurus"]

    for _ in range(10000):
        tree = Tree()
        tree.populate(len(taxa), taxa.keys())
        character_names = [f"char_{i}" for i in range(len(list(taxa.values())[0]))]
        for node in tree:
            characters = dict(zip(character_names, taxa[node.name]))
            for char, value in characters.items():
                node.add_feature(char, value)

        parsimony = standard_parsimony(tree, character_names, outgroup)

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
        dicynodon = topology.get_leaves_by_name("Dicynodon")[0]
        lystrosaurus = topology.get_leaves_by_name("Lystrosaurus")[0]
        outgroup = dicynodon.get_common_ancestor(lystrosaurus)
        topology.set_outgroup(outgroup)
        print(topology)


if __name__ == "__main__":
    main()
