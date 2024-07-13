# Sudoku Solver

A C++ library for efficiently solving Sudoku puzzles.

## Usage

You have two different options for using the library: using the raw sources, or using the objects generated by using CMake. A Python script is provided to test the libraries once compiled.

### Using the raw sources

This library uses the C++ STL only, so it can be easily included in any project.

### Compiling to a shared library

You need a working installation of [gcc](https://gcc.gnu.org/) if you're on Linux, or a properly configured [Msys2](https://www.msys2.org/) on Windows.

If using Msys2 on windows, search for "Edit the system environment variables" and select "Environment Variables". Under "System Variables", double click on "Path" to open it. Make sure that both values `C:\msys64\ucrt64\bin` and `C:\msys64\usr\bin` are present, add them otherwise.

To compile the library, just run `make` in the root directory of the project.

## Running the example

To run the example, you need a working installation of [Python 3](https://www.python.org/downloads/), as the frontend is written in Python.

To run the `example.py` script once the library is compiled, you need to run the main command followed by the file containing the puzzle to be solved.

For example, if using the Python script to solve the provided puzzle contained in the `./samples/Inkala.txt` file and you're in the root of the project, you need to run the command:

```bash
python ./example.py ./samples/Inkala.txt
```

### Puzzle format for example.py

The puzzle in the file must be formatted this way:

```text
8--------
--36-----
-7--9-2--
-5---7---
----457--
---1---3-
--1----68
--85---1-
-9----4--
```

using the character `-` for empty squares and regular digits for fixed values. Additional lines before or after the puzzle will be automatically stripped. However, make sure that all lines of the puzzle are properly formatted and that no empty lines separate them.

## Example C++ code

This is a code snippet that you can use as a reference for using this library directly in C++:

```cpp
sudoku::puzzle p("8----------36------7--9-2---5---7-------457-----1---3---1----68--85---1--9----4--");

std::cout << "Unsolved puzzle:\n\n";

for (sudoku::puzzle::coord_type row_i = 0; row_i < 9; row_i++) {
    for (sudoku::puzzle::coord_type col_i = 0; col_i < 9; col_i++) {
        std::cout << p.get(row_i, col_i) << ' ';
    }
    std::cout << '\n';
}

sudoku::puzzle ps = sudoku::dfs_solve(p);

std::cout << "\nSolved puzzle:\n\n";

for (sudoku::puzzle::coord_type row_i = 0; row_i < 9; row_i++) {
    for (sudoku::puzzle::coord_type col_i = 0; col_i < 9; col_i++) {
        std::cout << ps.get(row_i, col_i) << ' ';
    }
    std::cout << '\n';
}


```
