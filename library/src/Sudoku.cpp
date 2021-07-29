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
    this->initializeBoarders();
}
catch (const invalid_argument& e){
    throw e;
}

string Sudoku::getBoardString() const {
    string boardString = this->getHorizontalLine(true) + "\n";
    for (int row = 1 ; row <= 9 ; row++){
        string rowString = this->verticalHighlightSeparator;
        for (int col = 1 ; col <= 9 ; col++){
            int numIndex = this->getFlattenedIndex(row, col);
            CellPtr cell = this->board[numIndex];
            if(cell->isEmpty()){
                rowString += " ";
            }
            else{
                rowString += to_string(cell->getNumber());
            }
            if(col != 9){
                rowString += this->verticalBoarders[row - 1][col - 1];
            }
        }
        rowString += this->verticalHighlightSeparator + "\n";
        boardString += rowString + this->getHorizontalLine(row == 9) + "\n";
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
    for(int i = 0 ; i < 8 ; i ++){
        vector<string> rowHorizontalBoarders;
        for(int j = 0 ; j < 8 ; j++){
            rowHorizontalBoarders.push_back(this->horizontalSeparator);
        }
        this->horizontalBoarders.push_back(rowHorizontalBoarders);
    }
}

std::string Sudoku::getHorizontalLine(bool isHighlighted) const {
    string lineString = "";
    for(int i = 0 ; i < 9 ; i++){
        if(isHighlighted)
            lineString += this->horizontalHighlightSeparator;
        else
            lineString += this->horizontalSeparator;
    }
    return lineString;
}

