//
// Created by wojciech on 28/07/2021.
//

#include <iostream>
#include <iomanip>
#include <unistd.h>
#include "Sudoku.h"
#include "utils.h"
#include "time.h"

using namespace std;

int main(){
    vector<vector<NumPosition>> simpleBoards = {
            {
                    make_tuple(1, 4, 2),
                    make_tuple(1, 5, 6),
                    make_tuple(1, 7, 7),
                    make_tuple(1, 9, 1),
                    make_tuple(2, 1, 6),
                    make_tuple(2, 2, 8),
                    make_tuple(2, 5, 7),
                    make_tuple(2, 8, 9),
                    make_tuple(3, 1, 1),
                    make_tuple(3 ,2, 9),
                    make_tuple(3 ,6, 4),
                    make_tuple(3 ,7 ,5),
                    make_tuple(4, 1, 8),
                    make_tuple(4, 2, 2),
                    make_tuple(4, 4, 1),
                    make_tuple(4, 8, 4),
                    make_tuple(5, 3, 4),
                    make_tuple(5, 4, 6),
                    make_tuple(5, 6, 2),
                    make_tuple(5, 7, 9),
                    make_tuple(6, 2, 5),
                    make_tuple(6, 6, 3),
                    make_tuple(6, 8, 2),
                    make_tuple(6, 9, 8),
                    make_tuple(7, 3, 9),
                    make_tuple(7, 4, 3),
                    make_tuple(7, 8, 7),
                    make_tuple(7, 9, 4),
                    make_tuple(8, 2, 4),
                    make_tuple(8, 5, 5),
                    make_tuple(8, 8, 3),
                    make_tuple(8, 9, 6),
                    make_tuple(9, 1, 7),
                    make_tuple(9, 3, 3),
                    make_tuple(9, 5, 1),
                    make_tuple(9, 6, 8),
            },

            {
                    make_tuple(1,7,2),
                    make_tuple(2,2,8),
                    make_tuple(2,6,7),
                    make_tuple(2,8,9),
                    make_tuple(3,1,6),
                    make_tuple(3,3,2),
                    make_tuple(3,7,5),
                    make_tuple(4,2,7),
                    make_tuple(4,5,6),
                    make_tuple(5,4,9),
                    make_tuple(5,6,1),
                    make_tuple(6,5,2),
                    make_tuple(6,8,4),
                    make_tuple(7,3,5),
                    make_tuple(7,7,6),
                    make_tuple(7,9,3),
                    make_tuple(8,2,9),
                    make_tuple(8,4,4),
                    make_tuple(8,8,7),
                    make_tuple(9,3,6),
            }
    };
    vector<vector<CellPos>> simpleConstraints = getSimpleConstraints();
    Sudoku sudoku(simpleBoards[0]);
    cout << sudoku.getBoardString() << endl;
    time_t start, end;
    time(&start);
    Sudoku solvedSudoku = solveSudoku(sudoku);
    time(&end);
    cout << solvedSudoku.getBoardString() << endl;
    cout << "Solved in " << fixed << double(end - start) << setprecision(5) << " sec" << endl;
    return 0;
}
