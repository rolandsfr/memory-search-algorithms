# Development and building

Create a buld by executing makefile

```bash
make run
```

Execute the built binary in the root of the project

```bash
./main
```

# Project structure

## cli

`lib/cli.h` contains headers for command line interface functions to parse flags and their values

## algorithms

`lib/algorithms.h` contains function definitions for each of free memory search algorithms.

## Main

`main.c` serves as an entry file for benchmarking algorithms, parsing the cli input and outputting the results.
