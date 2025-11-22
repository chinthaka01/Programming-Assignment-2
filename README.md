# Banker's Algorithm Implementation

## Project Description
This program implements the Banker's Algorithm for deadlock avoidance in operating systems. It determines whether a system is in a safe state and finds a safe sequence of process execution if one exists.

## Project Structure

Programming-Assignment-2/
├── src/
│   └── bankers_algorithm.c
├── inputs/
│   └── safe_input.txt
├── README.md
├── Makefile
└── docs/
    └── algorithm_explanation.md
└── Sample Outputs/
    └── sample_outputs.png
├── .gitignore

## Files
- `src/bankers_algorithm.c` - Main implementation
- `input/safe_input.txt` - Safe state input data
- `Makefile` - Build configuration
- `README.md` - This file (Program description and Step-by-step guide to compile and run the program, including input file format and example command)
- `docs/algorithm_explanation.md` - Algorithm documentation
- `sample_outputs.png` - The sample outputs showing the safe state and sequence.

## Compilation and Execution

### Prerequisites
- GCC compiler
- Linux/Unix environment

### Compile and run the program
```bash
make run