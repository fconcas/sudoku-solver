#ifndef _SUDOKU_H
#define _SUDOKU_H

#include <bitset>
#include <cstdint>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "digit_mask.h"


namespace sudoku
{
    //! A class for representing puzzles.
    class puzzle
    {
    public:
        //! Unsigned integer type.
        using size_type = std::size_t;

        //! Digit type.
        using digit_type = unsigned short;

        //! Coordinate type.
        using coord_type = unsigned short;

        //! Pair of coordinates type.
        using coord_pair_type = std::pair<coord_type, coord_type>;

    private:
        digit_type puzzle_[9][9]{};
        digit_mask digit_mask_;
        size_type missing_tot_;

    public:
        //! Constructs the puzzle.
        puzzle() :
            missing_tot_(9 * 9)
        {}

        //! Constructs the puzzle.
        /*!
            \param puzzle_str A string representation of the puzzle. The puzzle should be flattened to a single row and missing values should be passed as `-`.
        */
        puzzle(const char* puzzle_str);

        //! Assigns a digit to a cell.
        /*!
            \param row Row of the cell.
            \param col Column of the cell.
            \param digit Digit to be assigned to the cell.
        */
        void set(const coord_type& row, const coord_type& col, const digit_type& digit);

        //! Returns the digit assigned to a cell.
        /*!
            \param row Row of the cell.
            \param col Column of the cell.
            \return The digit assigned to the cell.
        */
        digit_type get(const coord_type& row, const coord_type& col) const
        {
            return puzzle_[row][col];
        }

        //! Checks whether the puzzle is solved.
        /*!
            \return `true` if the puzzle is solved, `false` otherwise.
        */
        bool is_solved() const { return missing_tot_ == 0; }

        //! Returns a string representation of the puzzle.
        /*!
            \return The string representation of the puzzle.
        */
        std::string to_string();

        //! Fills the unique insertions of the puzzle (if any are present).
        void fill_unique_insertions();

        //! Assigns values to the puzzle.
        /*!
            \param other Another puzzle to be used as data source.
            \return `*this`
        */
        puzzle& operator=(const puzzle& other);
        
        friend puzzle dfs_solve(puzzle p);
    };

    //! Solves the puzzle by filling the unique insertions and using depth-first search if it's not possible to proceed by logic.
    /*!
        \param p The puzzle to be solved.
        \return The solved puzzle.
    */
    puzzle dfs_solve(puzzle p);
}

#endif
