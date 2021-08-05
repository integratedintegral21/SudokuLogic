//
// Created by wojciech on 01/08/2021.
//

#include <typedefs.h>
#include <vector>
#include <tuple>

using namespace std;

vector<vector<CellPos>> getSimpleConstraints(){
    vector<vector<CellPos>> simpleConstraints;
    for (int sqRow = 0 ; sqRow <= 2 ; sqRow++){
        for (int sqCol = 0 ; sqCol <= 2 ; sqCol++){
            vector<CellPos> square;
            for (int i = 0 ; i <= 2; i++){
                for (int j = 0 ; j <= 2; j++){
                    square.push_back(make_tuple(3 * sqRow + i + 1, 3 * sqCol + j + 1));
                }
            }
            simpleConstraints.push_back(square);
        }
    }
    return simpleConstraints;
}