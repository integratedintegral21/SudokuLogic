//
// Created by wojciech on 12/12/2021.
//

#ifndef SUDOKULOGICLIBRARY_CELL_H
#define SUDOKULOGICLIBRARY_CELL_H

#include "GameComponents.h"
#include "CellVerifiers/CellVerifiers.h"
#include "memory"
#include "vector"

class GameComponents::Cell {
private:
    // empty by default
    int number = 0;
    // observers
    std::vector<std::shared_ptr<CellVerifiers::CellGroupObserver>> groups;
public:
    Cell(int number);

/**
     * @return true if a cell object is empty
     */
    bool isEmpty() const;
    /**
     * Writes number in a cell object
     * @param number - a number to be set [1, 9]
     * @throws invalid_argument if number is not between 1 and 9
     */
    void setNumber(int number);
    /**
     * Makes a cell empty
     */
    void clearCell();
    /**
     * Adds a CellGroupObserver object to the list of observers
     * @param groupObserver a shared pointer to the observer
     */
    void addGroupObserver(const std::shared_ptr<CellVerifiers::CellGroupObserver>& groupObserver);
};


#endif //SUDOKULOGICLIBRARY_CELL_H
