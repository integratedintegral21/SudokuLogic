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
    string boardString = "";
    for (int row = 1 ; row <= 9 ; row++){
        boardString += this->getUpperHorizontalLine(true) + "\n";
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
        boardString += rowString + this->getLowerHorizontalLine(row == 9) + "\n";
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

std::string Sudoku::getUpperHorizontalLine(bool isHighlighted) const {
    string lineString = "\u250C";
    for(int i = 0 ; i < 8 ; i++){
        if(isHighlighted)
            lineString += "\u2500\u252C";
        else
            lineString += "\u2500\u252C";
    }
    lineString += "\u2500\u2510";
    return lineString;
}

std::string Sudoku::getLowerHorizontalLine(bool isHighlighted) const {
    string lineString = "\u2514";
    for(int i = 0 ; i < 8 ; i++){
        if(isHighlighted)
            lineString += "\u2500\u2534";
        else
            lineString += "\u2500\u2534";
    }
    lineString += "\u2500\u2518";
    return lineString;
}

