//
// Created by wojciech on 28/07/2021.
//

#include "GameComponents/Cell.h"
#include "CellVerifiers/CellGroup.h"
#include <stdexcept>
#include <iostream>
#include <algorithm>

using namespace std;
using GameComponents::Cell;
using CellVerifiers::CellGroup;

Cell::Cell(int number)
try
{
    if(!isNumberValid(number)) {
        throw invalid_argument("Invalid number");
    }
    this->setNumber(number);
}
catch (const invalid_argument& e){
    throw e;
}

Cell::Cell() {

}

int Cell::getNumber() const {
    return number;
}

bool Cell::isEmpty() const {
    return this->number == -1;
}

//Cell::~Cell() {
//
//}

bool Cell::isNumberAllowed(int number) const {

}

void Cell::setNumber(int number)
try{
    if (!isNumberValid(number)){
        throw invalid_argument("Invalid number");
    }
    Cell::number = number;
    for (const auto &group: groups) {
        group->notifyAdd(number);
    }
}
catch (const invalid_argument& e){
    throw e;
}


bool Cell::isNumberValid(int number) const {
    return number >= 1 && number <= 9;
}

void Cell::clearCell() {
    this->number = -1;
}

void GameComponents::Cell::addGroup(CellGroup::SharedPtr cellGroup) {
    this->groups.push_back(cellGroup);
}

void GameComponents::Cell::removeGroup(CellGroup::SharedPtr cellGroup) {
    this->groups.erase(std::remove(this->groups.begin(), this->groups.end(), cellGroup), this->groups.end());
}

