class Alignment:
    def __init__(self, file: str):
        with open(file) as f:
            lines = f.readlines()

        split_lines = [line.split() for line in lines]
        self.taxa = {
            sl[0].strip(): {f"char_{i}": sl[1][i] for i in range(len(sl[1].strip()))}
            for sl in split_lines
        }

        self.char_list = list(next(iter(self.taxa.values())).keys())
        self.outgroup_taxa = [t for t in self.taxa.keys() if "*" in t]

    def __str__(self):
        return f"""Outgroup Taxa: {self.outgroup_taxa}
Character List: {self.char_list}
Taxa: {self.taxa}"""


if __name__ == "__main__":
    print(Alignment("test_alignments/dicynodonts.txt"))
