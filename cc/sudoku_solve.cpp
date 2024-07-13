#include "puzzle.h"

#include <cstring>
#include <string>

extern "C"
{
    //! Solves a Sudoku puzzle.
    /*!
        \param p_str A string representation of the puzzle. The puzzle should be flattened to a single row and missing values should be passed as `-`.
        \return A string representation of the solved puzzle.
    */
    const char* sudoku_solve(const char* p_str)
    {
        sudoku::puzzle p(p_str);

        sudoku::puzzle p_sol = dfs_solve(p);
        std::string p_sol_string = p_sol.to_string();

        std::size_t str_size = 9 * 9 + 1;
        char* p_sol_str = new char[str_size];
        strncpy(p_sol_str, p_sol_string.c_str(), str_size);

        return p_sol_str;
    }
}
