//
// Created by wojciech on 28/07/2021.
//

#include "Sudoku.h"
#include "Cell.h"
#include <string>

using namespace std;

Sudoku::Sudoku(vector<NumPosition> initialBoard, vector<vector<CellPos>> constraints) {
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

std::string Sudoku::to_string() const {
    return string();
}

// sets all numbers possible and prunes impossible numbers in each empty cell
void Sudoku::fillWithPossibleNumbers() {
    // set all numbers possible in empty cells
    for(CellPtr cell: this->board){
        if(!cell->isEmpty())
            continue;
        for (int i = 1; i <= 9 ; i++){
            cell->setNumberPossible(i);
        }
    }
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

