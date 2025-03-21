# Project description

This program takes input of files with list of numbers representing different sizes and sizes of chunks available in mock memory.
The goal of the poragm is to find a chunk for a each size using different algorithms:

- BestFit
- WorstFit
- FirstFit
- NextFit

# CLI

## Params

| Param | Description                                                                  |
| ----- | ---------------------------------------------------------------------------- |
| `-c`  | Name of the file containing chunks                                           |
| `-s`  | Name of the file containing sizes                                            |
| `-a`  | (optional) Name of the file where the algorithm to be benchmarked is defined |

## Example

```bash
./main -c chunks.txt -d sizes.txt -a best_fit
```

# Development and building

Create a buld by executing makefile

```bash
make run
```

Execute the built binary in the root of the project

```bash
./main
```

# Testing

In order to avoid running long command with different params, you can run:

```bash
make test
```

This will resolve the executable and run the following command with pre-defined params

```bash
./main -c chunks.txt -s sizes.txt
```

Make sure you have chunks.txt and sizes.txt files in the root dir

# Project structure

## Main

`main.c` serves as an entry file for benchmarking algorithms, parsing the cli input and outputting the results.

## cli

`lib/cli` contains headers for command line interface functions to parse flags and their values

## algorithms

`lib/algorithms` contains headers for each of free memory search algorithms.

## parsers

`lib/parsers` contains headers for file parsers, which construct dynamic list of integers from the files read
