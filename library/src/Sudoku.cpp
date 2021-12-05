//
// Created by wojciech on 28/07/2021.
//

#include "Sudoku.h"
#include "Cell.h"
#include <stdexcept>
#include <string>
#include <algorithm>
#include "utils.h"

using namespace std;

Sudoku::Sudoku(const vector<CellPtr>& initialBoard, const std::vector<CellVerifiers::CellGroup::SharedPtr> & cellGroups)
try{
    if(initialBoard.size() > 81){
        throw invalid_argument("Too many initial positions given");
    }
    for (const CellPtr& cell: initialBoard){
        this->board.push_back(cell);
    }
    this->initializeCellsConstraints(cellGroups);
    this->initializeBorders();
    this->longHorizontalBar = getHorizontalBar(true);
    this->shortHorizontalBar = getHorizontalBar(false);
}
catch (const invalid_argument& e){
    throw e;
}

void Sudoku::initializeCellsConstraints(const std::vector<CellVerifiers::CellGroup::SharedPtr>& groups){
    this->cellsConstraints = std::vector<std::vector<CellVerifiers::CellGroup::SharedPtr>>(81);
    for (shared_ptr<CellVerifiers::CellGroup> group: groups){
        std::vector<CellPtr> cellsInGroup = group->getCells();
        // if a cell is in this group, assign this group to the cell
        for (int cellNr = 0 ; cellNr < 81 ; cellNr++){
            for (const CellPtr& groupCell: cellsInGroup){
                if (groupCell == this->board[cellNr]){
                    this->cellsConstraints[cellNr].push_back(group);
                }
            }
        }
    }
}

// Sudoku::Sudoku(const std::vector<NumPosition>& initialBoard): Sudoku(initialBoard, Utils::getSimpleConstraints()) {}

string Sudoku::getBoardString(bool showAllowedNumbers) const {
    string boardString;
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
                rowString += this->verticalBorders[row - 1][col - 1];
            }
        }
        rowString += this->verticalSeparator + "\n";
        boardString += rowString + this->getLowerHorizontalLine(showAllowedNumbers) + "\n";
    }
    return boardString;
}

void Sudoku::fillWithAllowedNumbers() {
    for (const CellPtr& cell: this->board){
        for(int num = 1; num <= 9 ; num++){
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

// after clearing a cell
void Sudoku::fillWithAllowedNumbers(CellPos & cellPos){
    int row = get<0>(cellPos);
    int col = get<1>(cellPos);
    int currentCellIndex = this->getFlattenedIndex(row, col);
    for (int rowNr = 1 ; rowNr <= 9 ; rowNr++){
        int cellIndex = this->getFlattenedIndex(rowNr, col);
        CellPtr cell = this->board[cellIndex];
        for(int num = 1; num <= 9 ; num++){
            if (this->isNumAllowed(make_tuple(rowNr, col, num)))
                cell->setNumberAllowed(num);
        }
    }
    for (int colNr = 1 ; colNr <= 9 ; colNr++){
        int cellIndex = this->getFlattenedIndex(row, colNr);
        CellPtr cell = this->board[cellIndex];
        for(int num = 1; num <= 9 ; num++){
            if (this->isNumAllowed(make_tuple(row, colNr, num)))
                cell->setNumberAllowed(num);
        }
    }
    vector<int> constraints = this->constraintsList[currentCellIndex];
    for (int cellIndex: constraints){
        CellPtr cell = this->board[cellIndex];
        int rowNr = cellIndex / 9 + 1;
        int colNr = cellIndex % 9 + 1;
        for(int num = 1; num <= 9 ; num++){
            if (this->isNumAllowed(make_tuple(rowNr, colNr, num)))
                cell->setNumberAllowed(num);
        }
    }
}

bool Sudoku::isNumAllowed(NumPosition numPosition){
    int row = get<0>(numPosition);
    int col = get<1>(numPosition);
    int num = get<2>(numPosition);
    int index = this->getFlattenedIndex(row, col);
    CellPtr thisCell = this->board[this->getFlattenedIndex(row, col)];
    CellPos cellPos = make_tuple(row, col);
    vector<int> columnCellsIndexes = this->getCellsFromColumn(cellPos);
    vector<int> rowCellsIndexes = this->getCellsFromRow(cellPos);
    vector<int> constrainedCellsIndexes = this->constraintsList[index];
    return this->uniqueInPositions(columnCellsIndexes, num) && this->uniqueInPositions(rowCellsIndexes, num) &&
            this->uniqueInPositions(constrainedCellsIndexes, num);
}

void Sudoku::solve(){
    this->solveByPruning(1);
}

bool Sudoku::isSolved() const {
    return all_of(this->board.begin(), this->board.end(), [](CellPtr cell){
        return !cell->isEmpty();
    });
}

int Sudoku::getFlattenedCoord(int row, int col) {
    return (row - 1) * 9 + col;
}

int Sudoku::getFlattenedIndex(int row, int col) const {
    return this->getFlattenedCoord(row, col) - 1;
}

void Sudoku::initializeBorders() {
    for(int i = 0 ; i < 9 ; i++){
        vector<string> verticalBorders;
        for(int j = 0 ; j < 8 ; j++){
            verticalBorders.push_back(this->verticalSeparator);
        }
        this->verticalBorders.push_back(verticalBorders);
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

bool Sudoku::isNumPosValid(NumPosition num) {
    return get<0>(num) >= 1 && get<0>(num) <= 9 &&
            get<1>(num) >= 1 && get<1>(num) <= 9 &&
            get<2>(num) >= 1 && get<2>(num) <= 9;
}

std::vector<int> Sudoku::getCellIndexesFromConstraints(CellPos cellPos, const vector<vector<CellPos>>& constraints) const{
    vector<int> constrainedCells;
    vector<vector<CellPos>> cellConstraints;
    for(vector<tuple<int, int>> con: constraints){
        if (any_of(con.begin(), con.end(), [cellPos](CellPos pos){return pos==cellPos;})){
            cellConstraints.push_back(con);
        }
    }
    for(const vector<CellPos>& constraint : cellConstraints){
        for(const CellPos& cellPos: constraint){
            int row = get<0>(cellPos);
            int col = get<1>(cellPos);
            int index = this->getFlattenedIndex(row, col);
            constrainedCells.push_back(index);
        }
    }
    return constrainedCells;
}

std::vector<int> Sudoku::getCellsFromColumn(CellPos cellPos) const {
    vector<int> cells;
    int row = get<0>(cellPos);
    int col = get<1>(cellPos);
    for (int rowNr = 1 ; rowNr <= 9 ; rowNr++){
        if(rowNr == row){
            continue;
        }
        int cellIndex = this->getFlattenedIndex(rowNr, col);
        cells.push_back(cellIndex);
    }
    return cells;
}

std::vector<int> Sudoku::getCellsFromRow(CellPos cellPos) const {
    vector<int> cells;
    int row = get<0>(cellPos);
    int col = get<1>(cellPos);
    for (int colNr = 1 ; colNr <= 9 ; colNr++){
        if(colNr == col){
            continue;
        }
        int cellIndex = this->getFlattenedIndex(row, colNr);
        cells.push_back(cellIndex);
    }
    return cells;
}

int Sudoku::getCellValue(CellPos cellPos) const
try{
    if(!isCellPosValid(cellPos)){
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
    CellPtr cellPtr = this->board[cellIndex];
    if(!cellPtr->isEmpty()){
        return false;
    }
    // is allowed in all of cell's groups
    return all_of(this->cellsConstraints[cellIndex].begin(), this->cellsConstraints[cellIndex].end(),
                  [num](const CellVerifiers::CellGroup::SharedPtr & cellGroup){
                      return cellGroup->isNumberAllowed(num);
    });
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
        for (int i = 1 ; i <= 9 ; i++){
            this->board[cellIndex]->setNumberNotAllowed(i);
        }
        this->pruneNumber(numPosition);
    }
}
catch(const invalid_argument& e){
    throw e;
}
void Sudoku::unsetCell(CellPos cellPos)
try{
    if(!isCellPosValid(cellPos)){
        throw invalid_argument("CellPos invalid");
    }
    int row = get<0>(cellPos);
    int col = get<1>(cellPos);
    int cellIndex = this->getFlattenedIndex(row, col);
    this->board[cellIndex]->unset();
    this->fillWithAllowedNumbers(cellPos);
}
catch (const invalid_argument& e){
    throw e;
}

Sudoku::~Sudoku() = default;

std::string Sudoku::getHorizontalBar(bool isLong) {
    string horizontalBar;
    int length = (isLong) ? 23 : 3;
    for (int i = 0 ; i < length ; i++){
        horizontalBar += "\u2500";
    }
    return horizontalBar;
}

bool Sudoku::isCellPosValid(CellPos cellPos) {
    return get<0>(cellPos) >= 1 && get<0>(cellPos) <= 9 &&
            get<1>(cellPos) >= 1 && get<1>(cellPos) <=9;
}

NumPosition Sudoku::buildNumPos(int flattenedCoord, int num) {
    return make_tuple(flattenedCoord / 9, flattenedCoord % 9, num);
}

void Sudoku::solveByPruning(int entryFlattenedCoord) {
    if(entryFlattenedCoord > 81){
        return;
    }
    CellPtr cell = this->board[entryFlattenedCoord - 1];
    int row = (entryFlattenedCoord - 1) / 9 + 1;
    int col = (entryFlattenedCoord - 1) % 9 + 1;
    if(cell->isEmpty()){
        vector<int> allowedNumbers = this->getAllowedNumbers(entryFlattenedCoord);
        if (allowedNumbers.empty()){
            return;
        }
        for(int number: allowedNumbers){
            // cell->setNumber(number);
            // this->fillWithAllowedNumbers();
            this->setNumber(make_tuple(row, col, number));
            this->solveByPruning(entryFlattenedCoord + 1);
            // success
            if(this->isSolvedFrom(entryFlattenedCoord)){
                return;
            }
            // no solution for this number
            this->unsetCell(make_tuple(row, col));
        }
    }
    else {
        this->solveByPruning(entryFlattenedCoord + 1);
    }
}

vector<int> Sudoku::getAllowedNumbers(int flattenedCoord) const {
    return this->board[flattenedCoord - 1]->getAllowedNumbers();
}

bool Sudoku::isSolvedFrom(int entryFlattenedCoord) {
    for(int index = entryFlattenedCoord ; index < 81 ; index++){
        CellPtr cell = this->board[index];
        if(cell->isEmpty())
            return false;
    }
    return true;
}

void Sudoku::pruneNumber(NumPosition numPosition) {
    int row = get<0>(numPosition);
    int col = get<1>(numPosition);
    int num = get<2>(numPosition);
    int index = this->getFlattenedIndex(row, col);
    for (int colNr = 1 ; colNr <= 9 ; colNr++){
        this->board[this->getFlattenedIndex(row, colNr)]->setNumberNotAllowed(num);
    }
    for (int rowNr = 1 ; rowNr <= 9 ; rowNr++){
        this->board[this->getFlattenedIndex(rowNr, col)]->setNumberNotAllowed(num);
    }
    vector<int> constrainedCells = this->constraintsList[index];
    for (int index: constrainedCells){
        this->board[index]->setNumberNotAllowed(num);
    }
}

bool Sudoku::uniqueInPositions(const vector<int> &indexes, int num) const {
    if(!all_of(indexes.begin(), indexes.end(), [this, num](int cellIndex){
        CellPtr cell = this->board[cellIndex];
        return cell->getNumber() != num;
    })){
        return false;
    }
    return true;
}

Sudoku::Sudoku(const Sudoku &sudoku) {
    for(CellPtr cell: sudoku.board){
        CellPtr newCell;
        if(cell->isEmpty()){
            newCell = make_shared<Cell>();
        }
        else{
            newCell = make_shared<Cell>(cell->getNumber());
        }
        vector<int> allowedNumbers = cell->getAllowedNumbers();
        for(int num: allowedNumbers){
            newCell->setNumberAllowed(num);
        }
        this->board.push_back(newCell);
    }
    for(const vector<int>& constraint: sudoku.constraintsList){
        vector<int> newConstraint;
        // copy(constraint.begin(), constraint.end(), newConstraint.begin());
        for(int cellIndex: constraint){
            newConstraint.push_back(cellIndex);
        }
        this->constraintsList.push_back(newConstraint);
    }
    for(const vector<string>& verticalBorder: sudoku.verticalBorders){
        vector<string> newBorder;
        // copy(verticalBorder.begin(), verticalBorder.end(), newBorder.begin());
        for (string border: verticalBorder){
            newBorder.push_back(border);
        }
        this->verticalBorders.push_back(newBorder);
    }
    this->longHorizontalBar = sudoku.longHorizontalBar;
    this->shortHorizontalBar = sudoku.shortHorizontalBar;
}


