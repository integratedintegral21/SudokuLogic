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
    vector<NumPosition> board0 = {
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
    Sudoku sudoku(board0, simpleConstraints);
    cout << sudoku.getBoardString() << endl;
    time_t start, end;
    time(&start);
    sudoku.solve();
    time(&end);
    cout << sudoku.getBoardString() << endl;
    cout << "Solved in " << fixed << double(end - start) << setprecision(5) << " sec" << endl;
    return 0;
}
