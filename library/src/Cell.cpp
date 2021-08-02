//
// Created by wojciech on 28/07/2021.
//

#include "Cell.h"
#include <stdexcept>
#include <iostream>

using namespace std;

Cell::Cell(int number)
try
{
    if(!isNumberValid(number)) {
        throw invalid_argument("Invalid number");
    }
    this->number = number;
    this->initStates();
    this->setNumberAllowed(number);
}
catch (const invalid_argument& e){
    throw e;
}

Cell::Cell() {
    this->initStates();
}

int Cell::getNumber() const {
    return number;
}

bool Cell::isEmpty() const {
    return this->number == -1;
}

Cell::~Cell() {

}

bool Cell::isNumberAllowed(int number) const
try{
    if(!isNumberValid(number))
        throw invalid_argument("Invalid number");
    return this->allowedNumbers[number - 1];
}
catch (const invalid_argument& e){
    throw e;
}


void Cell::initStates() {
    for (bool& state: this->allowedNumbers){
        state = false;
    }
}

void Cell::setNumberAllowed(int number)
try{
    if(!isNumberValid(number))
        throw invalid_argument("Invalid number");
    this->allowedNumbers[number - 1] = true;
}
catch (const invalid_argument& e){
    throw e;
}

void Cell::setNumberNotAllowed(int number)
try{
    if(!isNumberValid(number))
        throw invalid_argument("Invalid number");
    this->allowedNumbers[number - 1] = false;
}
catch (const invalid_argument& e){
    throw e;
}

void Cell::setNumber(int number)
try{
    if (!isNumberValid(number)){
        throw invalid_argument("Invalid number");
    }
    Cell::number = number;
    this->setNumberAllowed(number);
}
catch (const invalid_argument& e){
    throw e;
}


bool Cell::isNumberValid(int number) const {
    return number >= 1 && number <= 9;
}

