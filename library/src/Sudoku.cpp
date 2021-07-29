//
// Created by wojciech on 28/07/2021.
//

#include "Sudoku.h"
#include "Cell.h"
#include <string>
#include <stdexcept>

using namespace std;

Sudoku::Sudoku(vector<NumPosition> initialBoard, vector<vector<CellPos>> constraints)
try{
    if(initialBoard.size() != 81){
        throw invalid_argument("Board size incorrect");
    }
    if(constraints.size() != 9){
        throw invalid_argument("Constraints size incorrect");
    }
    for(auto& cons: constraints){
        if(cons.size() != 9){
            throw invalid_argument("Constraints size incorrect");
        }
    }
    for (int i = 0 ; i < 9*9 ; i++){
        this->board.push_back(make_shared<Cell>());
    }
    for(auto& numPos: initialBoard){
        int row = get<0>(numPos);
        int col = get<1>(numPos);
        int num = get<2>(numPos);
        CellPtr cell = this->board[this->getFlattenedIndex(row, col)];
        cell->setNumber(num);
    }
    this->constraints = constraints;
}
catch (const invalid_argument& e){
    throw e;
}

std::string Sudoku::to_string() const {
    return string();
}

void Sudoku::fillWithPossibleNumbers() {

}

bool Sudoku::isNumAllowed(NumPosition numPosition) const{
    return false;
}

void Sudoku::solve(){

}

bool Sudoku::isSolved() const {
    return false;
}

int Sudoku::getFlattenedCoord(int row, int col) const {
    return (row - 1) * 9 + col;
}

int Sudoku::getFlattenedIndex(int row, int col) const {
    return this->getFlattenedCoord(row, col) - 1;
}

