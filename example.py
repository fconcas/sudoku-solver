#!/usr/bin/env python3

"""Implements a python interface for the backend sudoku solver."""

import argparse
import ctypes

sudoku = ctypes.CDLL("./cc/sudoku.so")
sudoku.sudoku_solve.argtypes = [ctypes.c_char_p]
sudoku.sudoku_solve.restype = ctypes.c_char_p


def _parse_arguments():
    parser = argparse.ArgumentParser()
    parser.add_argument("puzzle", help="The file containing the puzzle.")
    args = parser.parse_args()

    return args


def _main():
    args = _parse_arguments()

    with open(args.puzzle, encoding="utf-8") as f:
        puzzle_str = str.encode(f.read().strip().replace("\n", ""))
        solved_str = sudoku.sudoku_solve(puzzle_str).decode("utf-8")

        for i in range(9):
            curr_str = solved_str[(9 * i) : (9 * (i + 1))]
            print(" ".join(curr_str))


if __name__ == "__main__":
    _main()
