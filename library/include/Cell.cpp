//
// Created by wojciech on 28/07/2021.
//

#include "Cell.h"

int Cell::getNumber() const {
    return number;
}

bool Cell::isEmpty() const {
    return this->number == -1;
}

Cell::~Cell() {

}

Cell::Cell(int number) : number(number) {
    this->initStates();
}

bool Cell::isNumberPossible(int number) const {
    if(!isNumberValid(number))
        return false;
    return this->possibleNumbers[number - 1];
}

Cell::Cell() {
    this->initStates();
}

void Cell::initStates() {
    for (bool& state: this->possibleNumbers){
        state = false;
    }
}

void Cell::setNumberPossible(int number){
    if(!isNumberValid(number))
        return;
    this->possibleNumbers[number - 1] = true;
}

void Cell::setNumberNotPossible(int number) {
    if(!isNumberValid(number))
        return;
    this->possibleNumbers[number - 1] = false;
}

void Cell::setNumber(int number) {
    if (!isNumberValid(number)){
        return;
    }
    Cell::number = number;
}

bool Cell::isNumberValid(int number) const {
    return number >= 1 && number <= 9;
}

