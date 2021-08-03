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
        throw invalid_argument("Too many initial positions given");
    }
    for (int i = 0 ; i < 9*9 ; i++){
        this->board.push_back(make_shared<Cell>());
    }
    for(auto& numPos: initialBoard){
        if(!this->isNumPosValid(numPos)){
            throw invalid_argument("NumPosition invalid");
        }
        int row = get<0>(numPos);
        int col = get<1>(numPos);
        int num = get<2>(numPos);
        CellPtr cell = this->board[this->getFlattenedIndex(row, col)];
        cell->setNumber(num);
    }
    this->initializeBoarders();
    this->longHorizontalBar = this->getHorizontalBar(true);
    this->shortHorizontalBar = this->getHorizontalBar(false);
    this->initializeConstraintsMap(constraints);
    this->fillWithAllowedNumbers();
}
catch (const invalid_argument& e){
    throw e;
}

string Sudoku::getBoardString(bool showAllowedNumbers) const {
    string boardString = "";
    for (int row = 1 ; row <= 9 ; row++){
        boardString += this->getUpperHorizontalLine(showAllowedNumbers) + "\n";
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
            if(showAllowedNumbers){
                rowString += ": ";
                for (int num = 1 ; num <= 9 ; num++){
                    if(cell->isNumberAllowed(num)){
                        rowString += to_string(num);
                    }
                    else{
                        rowString += " ";
                    }
                    rowString += ",";
                }
            }
            if(col != 9){
                rowString += this->verticalBoarders[row - 1][col - 1];
            }
        }
        rowString += this->verticalSeparator + "\n";
        boardString += rowString + this->getLowerHorizontalLine(showAllowedNumbers) + "\n";
    }
    return boardString;
}

void Sudoku::fillWithAllowedNumbers() {
    for (CellPtr cell: this->board){
        for(int num = 1; num <= 9 ; num++){
            if(cell->getNumber() != num)
                cell->setNumberNotAllowed(num);
        }
    }
    for (int row = 1 ; row <= 9 ; row++){
        for (int col = 1 ; col <= 9 ; col++){
            CellPtr cell = this->board[this->getFlattenedIndex(row, col)];
            if(!cell->isEmpty())
                continue;
            for(int num = 1; num <= 9 ; num++){
                NumPosition numPosition = make_tuple(row, col, num);
                if(this->isNumAllowed(numPosition)){
                    cell->setNumberAllowed(num);
                }
            }
        }
    }
}

bool Sudoku::isNumAllowed(NumPosition numPosition){
    int row = get<0>(numPosition);
    int col = get<1>(numPosition);
    int num = get<2>(numPosition);
    CellPtr thisCell = this->board[this->getFlattenedIndex(row, col)];
    CellPos cellPos = make_tuple(row, col);
    vector<CellPtr> columnCells = this->getCellsFromColumn(cellPos);
    vector<CellPtr> rowCells = this->getCellsFromRow(cellPos);
    vector<CellPtr> constrainedCells = this->constraintsMap[thisCell];
    for (const CellPtr& cell : constrainedCells){
        if(cell->getNumber() == num){
            return false;
        }
    }
    for (const CellPtr& cell : rowCells){
        if(cell->getNumber() == num){
            return false;
        }
    }
    for (const CellPtr& cell : columnCells){
        if(cell->getNumber() == num){
            return false;
        }
    }
    return true;
}

void Sudoku::solve(){
    this->solveByPruning(1);
}

bool Sudoku::isSolved() const {
    for(CellPtr cell: this->board){
        if(cell->isEmpty())
            return false;
    }
    return true;
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

std::string Sudoku::getUpperHorizontalLine(bool isLong) const {
    string lineString = this->leftUpperCorner;
    string horizontalBar = (isLong) ? this->longHorizontalBar : this->shortHorizontalBar;
    for(int i = 0 ; i < 8 ; i++){
        lineString += horizontalBar + upperJunction;
    }
    lineString += horizontalBar + rightUpperCorner;
    return lineString;
}

std::string Sudoku::getLowerHorizontalLine(bool isLong) const {
    string lineString = this->leftLowerCorner;
    string horizontalBar = (isLong) ? this->longHorizontalBar : this->shortHorizontalBar;
    for(int i = 0 ; i < 8 ; i++){
        lineString += horizontalBar + this->lowerJunction;
    }
    lineString += horizontalBar + this->rightLowerCorner;
    return lineString;
}

bool Sudoku::isNumPosValid(NumPosition num) const {
    return get<0>(num) >= 1 && get<0>(num) <= 9 &&
            get<1>(num) >= 1 && get<1>(num) <= 9 &&
            get<2>(num) >= 1 && get<2>(num) <= 9;
}

std::vector<CellPtr> Sudoku::getCellsFromConstraints(CellPos cellPos, vector<vector<CellPos>>& constraints) const{
    vector<CellPtr> constrainedCells;
    vector<vector<CellPos>> cellConstraints;
    for(vector<CellPos> con: constraints){
        for(CellPos pos: con){
            if(pos == cellPos)
                cellConstraints.push_back(con);
        }
    }
    for(const vector<CellPos>& constraint : cellConstraints){
        for(CellPos cellPos: constraint){
            int row = get<0>(cellPos);
            int col = get<1>(cellPos);
            int index = this->getFlattenedIndex(row, col);
            CellPtr cell = this->board[index];
            constrainedCells.push_back(cell);
        }
    }
    return constrainedCells;
}

std::vector<CellPtr> Sudoku::getCellsFromColumn(CellPos cellPos) const {
    vector<CellPtr> cells;
    int row = get<0>(cellPos);
    int col = get<1>(cellPos);
    for (int rowNr = 1 ; rowNr <= 9 ; rowNr++){
        if(rowNr == row){
            continue;
        }
        int cellIndex = this->getFlattenedIndex(rowNr, col);
        CellPtr cell = this->board[cellIndex];
        cells.push_back(cell);
    }
    return cells;
}

std::vector<CellPtr> Sudoku::getCellsFromRow(CellPos cellPos) const {
    vector<CellPtr> cells;
    int row = get<0>(cellPos);
    int col = get<1>(cellPos);
    for (int colNr = 1 ; colNr <= 9 ; colNr++){
        if(colNr == col){
            continue;
        }
        int cellIndex = this->getFlattenedIndex(row, colNr);
        CellPtr cell = this->board[cellIndex];
        cells.push_back(cell);
    }
    return cells;
}

int Sudoku::getCellValue(CellPos cellPos) const
try{
    if(!this->isCellPosValid(cellPos)){
        throw invalid_argument("CellPos invalid");
    }
    return this->board[this->getFlattenedIndex(get<0>(cellPos), get<1>(cellPos))]->getNumber();
}
catch(const invalid_argument& e){
    throw e;
}

bool Sudoku::isNumberAllowed(NumPosition numPosition) const
try{
    if(!this->isNumPosValid(numPosition)){
        throw invalid_argument("NumPosition invalid");
    }
    int row = get<0>(numPosition);
    int col = get<1>(numPosition);
    int num = get<2>(numPosition);
    int cellIndex = this->getFlattenedIndex(row, col);
    return this->board[cellIndex]->isNumberAllowed(num);
}
catch(const invalid_argument& e){
    throw e;
}

void Sudoku::setNumber(NumPosition numPosition)
try{
    if(!this->isNumPosValid(numPosition))
        throw invalid_argument("NumPosition invalid");
    int row = get<0>(numPosition);
    int col = get<1>(numPosition);
    int num = get<2>(numPosition);
    int cellIndex = this->getFlattenedIndex(row, col);
    if (isNumberAllowed(numPosition)){
        this->board[cellIndex]->setNumber(num);
        this->fillWithAllowedNumbers();
    }
}
catch(const invalid_argument& e){
    throw e;
}
void Sudoku::unsetCell(CellPos cellPos)
try{
    if(!this->isCellPosValid(cellPos)){
        throw("CellPos invalid");
    }
    int row = get<0>(cellPos);
    int col = get<1>(cellPos);
    int cellIndex = this->getFlattenedIndex(row, col);
    this->board[cellIndex]->unset();
    this->fillWithAllowedNumbers();
}
catch (const invalid_argument& e){
    throw e;
}

Sudoku::~Sudoku() {

}

std::string Sudoku::getHorizontalBar(bool isLong) const {
    string horizontalBar = "";
    int length = (isLong) ? 23 : 3;
    for (int i = 0 ; i < length ; i++){
        horizontalBar += "\u2500";
    }
    return horizontalBar;
}

void Sudoku::initializeConstraintsMap(std::vector<std::vector<CellPos>> constraints) {
    for (int row = 1 ; row <= 9 ; row++){
        for (int col = 1; col <= 9 ; col++){
            CellPtr cell = this->board[this->getFlattenedIndex(row, col)];
            vector<CellPtr> constrainedCells = this->getCellsFromConstraints(make_pair(row, col), constraints);
            this->constraintsMap.insert(make_pair(cell, constrainedCells));
        }
    }
}

bool Sudoku::isCellPosValid(CellPos cellPos) const {
    return get<0>(cellPos) >= 1 && get<0>(cellPos) <= 9 &&
            get<1>(cellPos) >= 1 && get<1>(cellPos) <=9;
}

NumPosition Sudoku::buildNumPos(int flattenedCoord, int num) const {
    return make_tuple(flattenedCoord / 9, flattenedCoord % 9, num);
}

void Sudoku::solveByPruning(int entryFlattenedCoord) {
    if(entryFlattenedCoord > 81){
        return;
    }
    CellPtr cell = this->board[entryFlattenedCoord - 1];
    if(cell->isEmpty()){
        vector<int> allowedNumbers = this->getAllowedNumbers(entryFlattenedCoord);
        if (allowedNumbers.size() == 0){
            return;
        }
        for(int number: allowedNumbers){
            cell->setNumber(number);
            this->fillWithAllowedNumbers();
            this->solveByPruning(entryFlattenedCoord + 1);
            // success
            if(this->isSolvedFrom(entryFlattenedCoord)){
                return;
            }
            // no solution for this number
            cell->unset();
        }
    }
    else {
        this->solveByPruning(entryFlattenedCoord + 1);
    }
}

vector<int> Sudoku::getAllowedNumbers(int flattenedCoord) const {
    vector<int> allowedNumbers;
    for(int num = 1 ; num <= 9 ; num++){
        if(this->board[flattenedCoord - 1]->isNumberAllowed(num)){
            allowedNumbers.push_back(num);
        }
    }
    return allowedNumbers;
}

bool Sudoku::isSolvedFrom(int entryFlattenedCoord) {
    for(int index = entryFlattenedCoord ; index < 81 ; index++){
        CellPtr cell = this->board[index];
        if(cell->isEmpty())
            return false;
    }
    return true;
}
