from alignments import Alignment
from search_strategies.naive import NaiveSearch
from evaluators.parsimony import StandardParsimony


def main(alignment_file: str):
    alignment = Alignment(alignment_file)
    naive = NaiveSearch(alignment, StandardParsimony())

    naive.search()


if __name__ == "__main__":
    from sys import argv
    main(argv[1])
