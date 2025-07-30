# GASPAR

## Genetic Algorithm for Searches under Parsimony

GASPAR is a phylogenetic inference software powered by a genetic algorithm aimed at analysis using morphological data, inspired by [GARLI](https://code.google.com/archive/p/garli/). Its main use case is for research in paleontology.

GASPAR is currently under development, as well as its documentation. It is only available as a self-compiled project in Linux via Makefile. Official releases are soon to come.

This was my undergrad final project, and a paper describing the software can be found [here](https://www.inf.ufpr.br/bcc/tcc/2024/2024%20Algoritmo%20Gen%C3%A9tico%20para%20Busca%20de%20Filogenias%20com%20Dados%20Morfol%C3%B3gicos.pdf) (in Portuguese).

> **Important:** everything in the following sections is subject to change. GASPAR is still very early in its development and all syntax and steps described here are provisional for basic usage of the software.

### Compiling

Compilation of the software is done simply by typing `make` in the root directory of the project. A more optimized version can be compiled using `make optimize` (this will be the default in the future). After that, a file named `gaspar` should be generated on the root directory.

### Quick Start

GASPAR works by either passing a file as input or reading from standard input, as follows:

```bash
# From input file
./gaspar [YOURFILE].gas

# From stdin (passing a file via redirection):
./gaspar < [YOURFILE].gas
```

You can test whether the software is working correctly by typing in the terminal:

```bash
./gaspar src/test-inputs/dicynodonds.gas
```

If everything is working as intended, you should get an analysis for 16 taxa and 44 characters with parsimony score of 111 (or at least close to this), and 100 bootstrap replicates.

### Usage

GASPAR gets as input a [script file](#the-scripting-file) with `.gas` extension and outputs two files: an `intree` file and a `dat` file. In case the analysis is named (see [below](#named-analyses)), these files become `[NAME].intree` and `[NAME].dat`.

The `intree` file contains the collection of best trees from all bootstrap replicates in Newick format followed by their "weights" (how much they should contribute to the Majority Rule Consensus - MRC - of all trees). This file is intended to be used as input to the command `consense` of the [PHYLIP](https://phylipweb.github.io/phylip/) package to calculate the consensus - be it MRC or Strict/Nelsen.

The `dat` file is always generated but as of now it is only useful for assessing the convergence of genetic algorithm searches. The first line contains the final parsimony score and the second the number of times the score of a tree was calculated (number of calls to the function `fitchParsimony()`). The remainder contain the best score obtained in each generation of the genetic algorithm.

### The scripting file

The file read by GASPAR has the following base syntax:

```gaspar
taxa: [NUMBER OF TAXA]
characters: [NUMBER OF CHARACTERS]

[MATRIX]

# From here on, everything is optional

seed [SEED]

analyses:

[NAME OF ANALYSIS] {
  [PARAMTERS...]
}
...
```

`taxa` and `characters` specify, respectively, how many taxa and characters are present in the matrix. They can be specified in any order.

`[MATRIX]` is a matrix in a format similar to Hennig88 and TNT's matrices. For example:

```gaspar
taxa: 3
characters: 8

Taxon_A 01234567
Taxon_B 2?63??72
Taxon_C 143366[127]4
```

Each line of the matrix has an identifier (the taxon name) and its sequence. Each sequence must be 8 characters long, with each text character corresponding to a sequence character. Characters can be digits from `0` to `7` or a question mark (`?`) for missing data. The exception are multistate characters, for each possible states are known but none is certain - more restrictive than simple missing data. These characters are denoted by square brackets (`[]`) and anything inside these brackets is a possible state of a single character.

#### Seeding of random number generation

Many algorithms in GASPAR require pseudo-random number generation, such as the genetic algorithm and hill climbing searches, which can result in different runs of GASPAR outputting different results for the same input. Although this is a somewhat desired consequence of using these search methods, one may wish to get repeatable results for a script.

This can be achieved by providing a fixed seed for the number generator. The command `seed` in GASPAR allows the user to get consistent results throughout the execution of the entire script. It may be provided after the character matrix and before any named analysis is defined. The syntax is `seed [NUMBER]`, where `number` can be any non-negative integer.

#### Named analyses

The example above is enough to start an analysis, and will output an `intree` and a `dat` file. However, you may want to give these files more appropriate names, or may wish to better configure the parameters of your analysis, or even run multiple different analyses with different parameters using the same matrix. For this purpose, the GASPAR language has an optional section called `analyses`, in which multiple different parameters can be tweaked with the same data to generate different pipelines. This step in necessary in order to use non-standard parameters, e.g. a branch-and-bound search or disabling bootstrap replicates. An example for this procedure can be found below:

```gaspar
analyses:

branchAndBoundSearch {
  searchMethod branchAndBound
  bsParams 0
}

hillClimbingSearch {
  searchMethod hillClimbing
  hcParams SPR 20% 8
}
```

Each analysis definition is composed by its name, followed by a block (`{ }`). The name defines the prefix attached to all output files relevant to that analysis. For example, an analysis named `gaNoBootstrap` will generate a `gaNoBootstrap.intree` and a `gaNoBootstrap.dat` file.

Inside the block, you can set the parameters of the analysis. Each line in the block corresponds to a different set of parameters that can be configured, dictated by a keyword and the values. Any number of configurations can be defined by block, but in case any of these conflict with each other (for example, setting `searchMethod` twice), only the **last** change takes effect.

#### List of parameters

Below is a list of all possible parameter keywords, their expected values and their defaults. Parameters which should be substituted will be indicated by `()`. If the parameter only accepts certain keywords, they will be highlighted by `[]` The default value of a parameter will be indicated by `{}`

##### `searchMethod`

Usage:

```gaspar
searchMethod [branchAndBound|hillClimbing|{geneticAlgorithm}]
```

Used to select the search method used by the software. Can be one of `branchAndBound` (exact search - very slow), `hillClimbing` (classic - usually slow but relatively precise) or `geneticAlgorithm` (default - fast but less reliable).

##### `gaParams`

Usage:

```gaspar
gaParams [{SPR}|NNI|hybrid] (selection strength)% (pop. size) (max. generations) (generation cutoff)
```

Configures the specific parameters of the genetic algorithm-driven search. The parameters are:

- **The branch swapping algorithm:** either `SPR` (default - most intensive), `NNI` (least intensive) or `hybrid` (user-defined mixture of the two).
- **Selection strength:** how strong should the parsimony score influence selection for the next generation. Default is 50% (0.5). Despite percentage, the value can be greater than 100%.
- **Population size:** the amount of individuals in the population. Default is 8.
- **Maximum number of generations:** the maximum amount of iterations the algorithm will run. Default is 1,000,000.
- **Maximum generation cutoff:** the amount of generations after which the algorithm will stop if score is not improved. Default is 20,000.

##### `hcParams`

Usage:

```gaspar
hcParams [{NNI}|SPR] (replicates)
```

Configures the specific parameters of the hill climbing algorithm-driven search. The parameters are:

- **The branch swapping algorithm:** either `NNI` (default - faster but less precise) or `SPR` (slower but more precise).
- **The number of replicates:** How many times the search will be performed. Essential to avoid getting trapped in local optima of the search space. Default value is 8.

##### `bsParams`

Usage:

```gaspar
bsParams (replicates)
```

Configures how many bootstrap replicates will be performed for that analysis. For n replicates, the software always performs 1 replicate with the matrix untouched + (n-1) replicates with resampled characters. Default is 100. To disable bootstrapping, set `replicates` to 0 or 1.

##### `sprParams`

Usage:

```gaspar
sprParams (strength)%
```

Sets how localized is SPR branch swapping in the genetic algorithm. If 100%, swapping always occur at the same branch. If 0%, branches are never swapped. Default is 5%.

##### `hybridParams`

Usage:

```gaspar
hybridParams (NNI)%
```

Sets the proportion of branch swaps in the genetic algorithm that should be NNIs when using the hybrid branch swapping strategy. Default is 80%.

##### `maxTrees`

Usage:

```gaspar
maxTrees (trees)
```

Sets the maximum amount of trees that should be allocated for the final answer of the algorithm. Similar to TNT's `hold` command. Default is 10,000.
