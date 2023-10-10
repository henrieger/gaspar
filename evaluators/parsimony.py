from search_strategies.base import Evaluator
from alignments import Alignment
from ete3 import Tree


class StandardParsimony(Evaluator):
    def __init__(self):
        pass

    def has_empty_set(self, children):
        for child in children:
            if len(child) == 0:
                return True
        return False

    def evaluate(self, tree: Tree, alignment: Alignment):
        parsimony = 0
        for character in alignment.char_list:
            for node in tree.traverse("postorder"):
                if node.is_leaf():
                    continue

                char_value = ""
                children = [set(child.__dict__[character]) for child in node.children]

                intersection = set.intersection(*children)
                if not intersection:
                    char_value = set.union(*children)
                    if (
                        node.name not in alignment.outgroup_taxa
                        and not self.has_empty_set(children)
                    ):
                        parsimony -= 1
                else:
                    char_value = intersection

                node.add_feature(character, char_value)

        return parsimony
