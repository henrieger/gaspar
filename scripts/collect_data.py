import os
import numpy
import scipy

data_path = "../data/trevosim_32_1024/"


class DataCollection:
    def __init__(self, mrc_acc, mrc_prec, strict_acc, strict_prec, score, exec):
        self.mrc_acc = mrc_acc
        self.mrc_prec = mrc_prec
        self.strict_acc = strict_acc
        self.strict_prec = strict_prec
        self.score = score
        self.exec = exec

    def __repr__(self):
        return f"""[
            mrc_acc={self.mrc_acc}, mrc_prec={self.mrc_prec},
            strict_acc={self.strict_acc}, strict_prec={self.strict_prec},
            score={self.score}, exec={self.exec}
        ]"""

    def to_dir(self):
        return {
            "mrc_acc": self.mrc_acc,
            "mrc_prec": self.mrc_prec,
            "strict_acc": self.strict_acc,
            "strict_prec": self.strict_prec,
            "score": self.score,
            "exec": self.exec,
        }


def divide_chunks(data: list, n: int):
    for i in range(0, len(data), n):
        yield data[i : i + n]


def main():
    data_group = dict()
    for replicate in os.listdir(data_path):
        with open(data_path + replicate + "/final.dat") as data_file:
            data = [line.strip() for line in data_file.readlines()]

        data_chunks = divide_chunks(data, 5)

        for chunk in data_chunks:

            key = chunk[0]
            mrc_acc, mrc_prec = [float(datum) for datum in chunk[1].split(" ", 1)]
            strict_acc, strict_prec = [float(datum) for datum in chunk[2].split(" ", 1)]
            score = int(chunk[3])
            exec = int(chunk[4])

            data_collection = DataCollection(
                mrc_acc, mrc_prec, strict_acc, strict_prec, score, exec
            )
            if data_group.get(key) is None:
                data_group[key] = [data_collection]
            else:
                data_group[key].append(data_collection)

    for k, v in data_group.items():
        mrc_acc = numpy.average([dc.mrc_acc for dc in v])
        mrc_prec = numpy.average([dc.mrc_prec for dc in v])
        strict_acc = numpy.average([dc.strict_acc for dc in v])
        strict_prec = numpy.average([dc.strict_prec for dc in v])
        scores = numpy.average([dc.score for dc in v])
        execs = numpy.average([dc.exec for dc in v])

        print(
            k, DataCollection(mrc_acc, mrc_prec, strict_acc, strict_prec, scores, execs)
        )

    print("\nT-tests:\n")

    t_sample_ga = data_group["geneticAlgorithmSpr"]
    t_sample_hc = data_group["hillClimbingSpr"]

    for key in t_sample_ga[0].to_dir():
        print(f"{key}:")
        value_hc = [v.to_dir()[key] for v in t_sample_hc]
        value_ag = [v.to_dir()[key] for v in t_sample_ga]
        for alternative in ['less', 'greater']:
            t_test = scipy.stats.ttest_rel(
                value_hc,
                value_ag,
                alternative=alternative,
            )
            print(f"\t{alternative}: {float(t_test.pvalue)}")


if __name__ == "__main__":
    main()
