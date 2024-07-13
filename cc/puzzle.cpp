#include "puzzle.h"

#include <bitset>
#include <cstdint>
#include <iostream>
#include <stack>
#include <string>
#include <utility>
#include <vector>


namespace sudoku
{
    puzzle::puzzle(const char* puzzle_str)
    {
        missing_tot_ = 9 * 9;

        for (std::size_t i = 0; puzzle_str[i] != '\0'; i++) {
            if (puzzle_str[i] != '-') {
                digit_type digit = puzzle_str[i] - '0';
                coord_type row = i / 9;
                coord_type col = i % 9;

                set(row, col, digit);
            }
        }
    }


    void puzzle::set(const coord_type& row, const coord_type& col, const digit_type& digit)
    {
        if (puzzle_[row][col]) {
            throw std::runtime_error("Cell is already assigned.");
        }

        if (!digit_mask_.at(row, col, digit)) {
            std::cerr << row << ' ' << col << ' ' << digit << '\n';
            throw std::runtime_error("Can't assign digit to cell.");
        }

        puzzle_[row][col] = digit;

        digit_mask_.reset_cell(row, col);
        digit_mask_.reset_row(row, digit);
        digit_mask_.reset_col(col, digit);
        digit_mask_.reset_box(row, col, digit);

        missing_tot_--;
    }

    std::string puzzle::to_string()
    {
        std::string result(9 * 9, '-');

        for (coord_type row = 0; row < 9; row++) {
            for (coord_type col = 0; col < 9; col++) {
                if (puzzle_[row][col]) {
                    result[row * 9 + col] = static_cast<char>(puzzle_[row][col]) + '0';
                }
                else {
                    result[row * 9 + col] = '-';
                }
            }
        }

        return result;
    }


    void puzzle::fill_unique_insertions()
    {
        bool inserted_flag = true;

        while (inserted_flag) {
            inserted_flag = false;

            for (coord_type row_i = 0; row_i < 9; row_i++) {
                for (coord_type col_i = 0; col_i < 9; col_i++) {
                    if (digit_mask_.count_digits(row_i, col_i) == 1) {
                        digit_type digit_i = 0;
                        while (!digit_mask_.at(row_i, col_i, digit_i + 1))  digit_i++;
                        set(row_i, col_i, digit_i + 1);
                        inserted_flag = true;
                    }
                }
            }
        }
    }

    puzzle dfs_solve(puzzle p)
    {
        std::stack<puzzle> s;
        s.push(p);

        while (!s.empty()) {
            p = s.top();
            s.pop();

            p.fill_unique_insertions();

            if (p.is_solved())  return p;

            puzzle::coord_pair_type coords = p.digit_mask_.get_min_cell();

            for (puzzle::digit_type digit_i = 0; digit_i < 9; digit_i++) {
                if (p.digit_mask_.at(coords.first, coords.second, digit_i + 1)) {
                    puzzle np = p;
                    np.set(coords.first, coords.second, digit_i + 1);
                    s.push(np);
                }
            }
        }

        throw std::runtime_error("Could not find a solution.");
    }

    puzzle& puzzle::operator=(const puzzle& other)
    {
        missing_tot_ = other.missing_tot_;
        digit_mask_ = other.digit_mask_;

        for (coord_type row_i = 0; row_i < 9; row_i++) {
            for (coord_type col_i = 0; col_i < 9; col_i++) {
                puzzle_[row_i][col_i] = other.puzzle_[row_i][col_i];
            }
        }

        return *this;
    }
}
