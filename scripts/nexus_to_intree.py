from nexus import NexusReader
from sys import argv
import re

n = NexusReader.from_file(argv[1])
n.trees.detranslate()

print(1)

t = n.trees.trees[0].newick_string
t = re.sub(r":\d+", "", t)
print(t.replace("_", ""))
