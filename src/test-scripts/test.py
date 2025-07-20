from sys import argv
from subprocess import run
from resource import getrusage, RUSAGE_CHILDREN
from re import findall, MULTILINE


def generate_species_dict(num_species: int) -> dict[str, str]:
    return {
        f"Spec_{i}": f"{format(1 << i, f'0{num_species}b')}" for i in range(num_species)
    }


def generate_input_file(num_species: int) -> None:
    input = f"text/x-gaspar\n\ncharacters: {num_species}\ntaxa: {num_species}"

    input += "\n".join(
        f"{species} {sequence}"
        for species, sequence in generate_species_dict(num_species).items()
    )

    input += "\nanalyses:\n\ntest {\nbsParams 1\n}"

    with open("test.gas", "w") as file:
        file.write(input)


def main() -> None:
    num_species = int(argv[1])

    for i in range(5, num_species + 1):
        print(f"{i} taxa/chars:", end=" ")

        generate_input_file(i)

        process = run(["./gaspar", "test.gas"], capture_output=True)
        rusage = getrusage(RUSAGE_CHILDREN)
        elapsed_time = rusage.ru_utime + rusage.ru_stime

        length = int(
            findall(r"Min score: ([0-9]+)", process.stdout.decode(), flags=MULTILINE)[0]
        )
        if length == i:
            print("✓", f"{elapsed_time}s")
        else:
            print("✗", f"{elapsed_time}s")
            break


if __name__ == "__main__":
    main()
