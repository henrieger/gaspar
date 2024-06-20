import ete3


def main():
    result = ete3.Tree("result.tre")
    correct = ete3.Tree("correct.tre")
    consensus = ete3.Tree("cfi.tre")

    result_internal_nodes = 0
    for n in result.traverse():
        result_internal_nodes += 0 if n.is_leaf() else 1

    cfi_internal_nodes = 0
    for n in consensus.traverse():
        cfi_internal_nodes += 0 if n.is_leaf() else 1

    tests = result.compare(correct, unrooted=True)
    cfi = (
        (cfi_internal_nodes - 1) / (result_internal_nodes - 1)
        if result_internal_nodes != 1
        else 0
    )

    print(1 - tests["norm_rf"], cfi)


if __name__ == "__main__":
    main()
