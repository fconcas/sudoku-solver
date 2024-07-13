#include "digit_mask.h"

namespace sudoku
{
    digit_mask::digit_mask()
    {
        for (coord_type row = 0; row < 9; row++) {
            for (coord_type col = 0; col < 9; col++) {
                digit_mask_[row][col].set();
            }
        }
    }

    void digit_mask::reset_row(const coord_type& row, const digit_type& digit)
    {
        for (coord_type col_i = 0; col_i < 9; col_i++) {
            digit_mask_[row][col_i][digit - 1] = false;
        }
    }

    void digit_mask::reset_col(const coord_type& col, const digit_type& digit)
    {
        for (coord_type row_i = 0; row_i < 9; row_i++) {
            digit_mask_[row_i][col][digit - 1] = false;
        }
    }

    void digit_mask::reset_box(const coord_type& row, const coord_type& col, const digit_type& digit)
    {
        const coord_type row_start = (row / 3) * 3;
        const coord_type row_end = row_start + 3;
        const coord_type col_start = (col / 3) * 3;
        const coord_type col_end = col_start + 3;

        for (coord_type row_i = row_start; row_i < row_end; row_i++) {
            for (coord_type col_i = col_start; col_i < col_end; col_i++) {
                digit_mask_[row_i][col_i][digit - 1] = false;
            }
        }
    }

    digit_mask::coord_pair_type digit_mask::get_min_cell()
    {
        coord_type min_row_i = 0;
        coord_type min_col_i = 0;
        size_type min_amount = SIZE_MAX;

        for (coord_type row_i = 0; row_i < 9; row_i++) {
            for (coord_type col_i = 0; col_i < 9; col_i++) {
                size_type amount = digit_mask_[row_i][col_i].count();

                if (amount > 0 && amount < min_amount) {
                    min_row_i = row_i;
                    min_col_i = col_i;
                    min_amount = amount;
                }
            }
        }

        return coord_pair_type(min_row_i, min_col_i);
    }

    digit_mask::size_type digit_mask::count_digits(const coord_type& row, const coord_type& col)
    {
        return digit_mask_[row][col].count();
    }

    digit_mask& digit_mask::operator=(const digit_mask& other)
    {
        for (coord_type row_i = 0; row_i < 9; row_i++) {
            for (coord_type col_i = 0; col_i < 9; col_i++) {
                digit_mask_[row_i][col_i] = other.digit_mask_[row_i][col_i];
            }
        }

        return *this;
    }
}
