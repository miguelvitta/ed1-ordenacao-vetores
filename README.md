# List1 – Simple List Operations in C

This program lets the user generate integer arrays (random, ascending, or descending) of any size and sort them using multiple classic algorithms (Selection, Insertion, Bubble, Merge, Quick, Heap). It measures and reports execution time, swaps, and comparisons for each algorithm, and can display both the original and sorted arrays.

## Requirements

- A C compiler such as `clang` or `gcc`.
- `make` installed (optional but recommended).

## Build and Run with `make`

1. Open a terminal in this folder.
2. Compile the program:

   ```bash
   make
   ```
This produces an executable named list1.

Run the program:

```bash
./list1
```

To clean up object files and the binary:

```bash
make clean
```

To build with debug flags (AddressSanitizer, symbols, no optimizations):

```bash
make debug
./sort_algorithms
```

## Build and Run Without make
If you prefer not to use make, compile manually:

```bash
clang -Wall -Wextra -Wshadow main.c functions.c -o sort_algorithms -lm
```

Then run:

```bash
./sort_algorithms
```

Replace clang with gcc if desired.

---