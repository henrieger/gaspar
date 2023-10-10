from evaluators.base import Evaluator
from alignments import Alignment


class SearchStrategy:
    def __init__(self, alignment: Alignment, evaluator: Evaluator):
        self.alignment = alignment
        self.evaluator = evaluator

    def search(self):
        pass
