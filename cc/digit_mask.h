#ifndef _DIGIT_MASK_H
#define _DIGIT_MASK_H

#include <bitset>


namespace sudoku
{
    //! A class for representing digit masks.
    /*!
        This library uses a so-called "digit mask" to keep track of the possible digits which are possible to be added to each cell. This is used when searching for a solution logically. To represent the digit mask, a bitset that represents the possibility for each digit to be added to a cell is used as a container.
    */
    class digit_mask
    {
    public:
        //! Bitset containing the boolean values for every digit in a cell type.
        using container_type = std::bitset<9>;

        //! Coordinate type.
        using coord_type = unsigned short;

        //! Pair of coordinates type.
        using coord_pair_type = std::pair<coord_type, coord_type>;

        //! Digit type.
        using digit_type = unsigned short;

        //! Unsigned integer type.
        using size_type = std::size_t;

    private:
        container_type digit_mask_[9][9];

    public:
        //! Constructs the digit mask.
        digit_mask();

        //! Resets all digits in a cell.
        /*!
            \param row Row of the cell to be reset.
            \param col Column of the cell to be reset.
        */
        void reset_cell(const coord_type& row, const coord_type& col)
        {
            digit_mask_[row][col].reset();
        }

        //! Resets a digit in a row.
        /*!
            \param row Row to be reset.
            \param digit Digit to be reset.
        */
        void reset_row(const coord_type& row, const digit_type& digit);

        //! Resets a digit in a column.
        /*!
            \param col Column to be reset.
            \param digit Digit to be reset.
        */
        void reset_col(const coord_type& col, const digit_type& digit);

        //! Resets a digit in a box.
        /*!
            \param row Row from which to derive the box to reset.
            \param col Column from which to derive the box to reset.
            \param digit Digit to be reset.
        */
        void reset_box(const coord_type& row, const coord_type& col, const digit_type& digit);

        //! Gets the coordinates of the cell with the least number of possible digits.
        /*!
            \return The pair of coordinates.
        */
        coord_pair_type get_min_cell();

        //! Counts the number of possible digits in a cell.
        /*!
            \param row Row of the cell to count.
            \param col Column of the cell to count.
            \return The number of possible digits.
        */
        size_type count_digits(const coord_type& row, const coord_type& col);

        //! Tests whether a digit can be added to a cell.
        /*!
            \param row Row of the cell.
            \param col Column of the cell.
            \param digit The digit.
            \return `true` if the digit can be added to the cell, `false` otherwise.
        */
        bool at(const coord_type& row, const coord_type& col, const digit_type& digit) const
        {
            return digit_mask_[row][col][digit - 1];
        }

        //! Assigns values to the digit mask.
        /*!
            \param other Another digit mask to be used as data source.
            \return `*this`
        */
        digit_mask& operator=(const digit_mask& other);
    };
}

#endif
