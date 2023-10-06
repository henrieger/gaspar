class Alignment:
    def __init__(self, file: str):
        with open(file) as f:
            lines = f.readlines()

        split_lines = [line.split() for line in lines]
        self.taxa = {
            sl[0].strip(): {
                f"char_{i}": char
                for i, char in enumerate(self._extract_characters(sl[1:]))
            }
            for sl in split_lines
        }

        self.char_list = list(next(iter(self.taxa.values())).keys())
        self.outgroup_taxa = [t for t in self.taxa.keys() if "*" in t]

    def __str__(self):
        return f"""Outgroup Taxa: {self.outgroup_taxa}
Character List: {self.char_list}
Taxa: {self.taxa}"""

    def _extract_characters(self, line_split: list):
        for split in line_split:
            if "/" in split:
                yield split.replace("/", "")
            else:
                for char in split:
                    if is_uncertain_character(char):
                        yield ""
                    else:
                        yield char


def is_uncertain_character(char: str):
    return (char == '?') or (char == '-')


if __name__ == "__main__":
    print(Alignment("test_alignments/dicynodonts.txt"))
