import matplotlib.pyplot as plt
import os
import numpy

data_path = "../data/trevosim_16_256/"


def main():
    data = dict()

    for dir in os.listdir(data_path):
        for file in os.listdir(data_path + dir):
            if file.endswith(".dat") and file.startswith("geneticAlgorithm"):
                algorithm = file.split(".")[0]

                with open(data_path + dir + "/" + file) as f:
                    lines = f.readlines()

                scores = [int(line) for line in lines[2:-15000]]

                if data.get(algorithm):
                    data[algorithm].append(scores)
                else:
                    data[algorithm] = [scores]

    for key in data:
        maximum = 0
        for value in data[key]:
            maximum = max(maximum, len(value))

    for key in data:
        for i in range(len(data[key])):
            data[key][i] = numpy.pad(
                data[key][i], (0, maximum - len(data[key][i])), mode="edge"
            )

    averages = dict()

    for key, value in data.items():
        averages[key] = numpy.average(value, axis=0)

    colors = {"geneticAlgorithmNni": "green", "geneticAlgorithmSpr": "blue"}

    plt.figure()
    for key in data:
        for value in data[key]:
            plt.plot(numpy.arange(len(value)), value, color=colors[key], alpha=0.1)
        plt.plot(
            numpy.arange(len(value)),
            averages[key],
            color=colors[key],
            linewidth=3,
            label=key.replace("geneticAlgorithm", "").upper(),
        )
    # plt.yscale("log")
    plt.xlabel("Gerações")
    plt.ylabel("Parcimônia")
    plt.legend()
    plt.savefig(f"{data_path.split('/')[-2]}.pdf", format="pdf")


if __name__ == "__main__":
    main()
