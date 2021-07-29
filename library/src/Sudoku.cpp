//
// Created by wojciech on 28/07/2021.
//

#include "Sudoku.h"
#include "Cell.h"
#include <stdexcept>
#include <string>

using namespace std;

Sudoku::Sudoku(vector<NumPosition> initialBoard, vector<vector<CellPos>> constraints)
try{
    if(initialBoard.size() > 81){
        throw invalid_argument("too many initial positions given");
    }
    for (int i = 0 ; i < 9*9 ; i++){
        this->board.push_back(make_shared<Cell>());
    }
    for(auto& numPos: initialBoard){
        if(!this->isNumPosValid(numPos)){
            throw invalid_argument("Incorrect initial state");
        }
        int row = get<0>(numPos);
        int col = get<1>(numPos);
        int num = get<2>(numPos);
        CellPtr cell = this->board[this->getFlattenedIndex(row, col)];
        cell->setNumber(num);
    }
    this->constraints = constraints;
    this->initializeBoarders();
}
catch (const invalid_argument& e){
    throw e;
}

string Sudoku::getBoardString() const {
    string boardString = "";
    for (int row = 1 ; row <= 9 ; row++){
        boardString += this->getUpperHorizontalLine() + "\n";
        string rowString = this->verticalSeparator;
        for (int col = 1 ; col <= 9 ; col++){
            int numIndex = this->getFlattenedIndex(row, col);
            CellPtr cell = this->board[numIndex];
            if(cell->isEmpty()){
                rowString += "   ";
            }
            else{
                rowString += " " + to_string(cell->getNumber()) + " ";
            }
            if(col != 9){
                rowString += this->verticalBoarders[row - 1][col - 1];
            }
        }
        rowString += this->verticalSeparator + "\n";
        boardString += rowString + this->getLowerHorizontalLine() + "\n";
    }
    return boardString;
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

void Sudoku::initializeBoarders() {
    for(int i = 0 ; i < 9 ; i++){
        vector<string> rowVerticalBoarders;
        for(int j = 0 ; j < 8 ; j++){
            rowVerticalBoarders.push_back(this->verticalSeparator);
        }
        this->verticalBoarders.push_back(rowVerticalBoarders);
    }
}

std::string Sudoku::getUpperHorizontalLine() const {
    string lineString = this->leftUpperCorner;
    for(int i = 0 ; i < 8 ; i++){
        lineString += this->horizontalBar + upperJunction;
    }
    lineString += this->horizontalBar + rightUpperCorner;
    return lineString;
}

std::string Sudoku::getLowerHorizontalLine() const {
    string lineString = this->leftLowerCorner;
    for(int i = 0 ; i < 8 ; i++){
        lineString += this->horizontalBar + this->lowerJunction;
    }
    lineString += this->horizontalBar + this->rightLowerCorner;
    return lineString;
}

bool Sudoku::isNumPosValid(NumPosition num) const {
    return get<0>(num) >= 1 && get<0>(num) <= 9 &&
            get<1>(num) >= 1 && get<1>(num) <= 9 &&
            get<2>(num) >= 1 && get<2>(num) <= 9;
}

